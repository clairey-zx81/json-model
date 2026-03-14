import { parseArgs } from 'node:util'
import fs from 'node:fs/promises'

import { jm_set_rx } from 'json_model_runtime'
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);

// TODO escaping?
const json_path = (path) => '.' + path.join('.')

function reporting(rep)
{
    if (rep === null || rep.length === 0) return ''

    let reps = []
    for (const [message, path] of rep)
        reps.unshift(`${json_path(path)}: ${message}`)

    return ' (' + reps.join('; ') + ')'
}

// process one value
function processing(source, value, checker, name, expected, report, times, overhead)
{
    // do it once for the result
    let rep = report ? [] : null
    const valid = checker(value, name, rep)
    const error = (expected === null || valid === expected) ? 0 : 1

    if (error)
        console.log(`${source}: ERROR unexpected ${valid ? 'PASS' : 'FAIL'}${reporting(rep)}`)
    else
        console.log(`${source}: ${valid ? 'PASS' : 'FAIL'}${reporting(rep)}`)

    // show performance
    // NOTE: jit, calls may take a lot of time at the beginning
    // NOTE: gc, may be irregular…
    if (times > 1)
    {
        let sum = 0.0
        let sum2 = 0.0
        let n = times
        let v = overhead.value
        while (n--) {
            let rep = report ? [] : null
            const start = performance.now()
            v = (3.141592653589793 * v + 2.718281828459045) % 1.0
            checker(value, '', rep)
            rep && (rep.length = 0)
            let delay = (1000.0 * (performance.now() - start)) - overhead.empty  // µs
            sum += delay
            sum2 += delay * delay
        }
        overhead.value = v
        const avg = sum / times
        const stdev = Math.sqrt(sum2 / times - avg * avg)
        console.warn(`${source}: ${report ? 'rep' : 'nop'} ${valid ? 'PASS' : 'FAIL'}`,
                     `${avg.toFixed(3)} ± ${stdev.toFixed(3)} µs (${overhead.empty.toFixed(3)})`)
    }

    return error
}

// evaluate measure overhead in µs
function eval_empty(times, value)
{
    let empty = 0.0
    if (times >= 1)
    {
        let n = times
        while (n--)
        {
            const start = performance.now()
            value = (3.141592653589793 * value + 2.718281828459045) % 1.0
            empty += 1000.0 * (performance.now() - start)
        }
        empty /= times
    }
    return { empty, value }
}

export default async function main(checker_init, checker, checker_free)
{
    checker_init()

    const options = {
      // TODO --help --list
      'verbose': { type: 'boolean', short: 'v' },
      'time': { type: 'string', short: 'T' },
      'report': { type: 'boolean', short: 'r' },
      'no-report': { type: 'boolean' },
      'test': { type: 'boolean', short: 't' },
      'jsonl': { type: 'boolean', short: 'L' },
      're2': { type: 'boolean' },
      'regexp': { type: 'boolean' },
    }

    const args = parseArgs({options, allowPositionals: true})

    if (args.values.jsonl)
        args.values.test = true
    if (args.values.no_report)
        args.values.report = false

    let errors = 0
    const times = args.values.time !== undefined ? Number(args.values.time) : 1

    if (isNaN(times))
    {
        console.log(`Unexpected --time: ${args.values.time}`)
        process.exit(1);
    }

    // reset regular expression engine
    if (args.values.regexp)
        jm_set_rx(RegExp)
    if (args.values.re2)
        jm_set_rx(require('re2'))

    // minimal average overhead estimation: we need the jit to kick in…
    let value = times / 13.0 % 1.0
    let overhead = eval_empty(times, value)
    for (let n = 100; n; n--)
    {
        const o = eval_empty(times, overhead.value)
        if (o.empty < overhead.empty)
            overhead = o
        else
            overhead.value = o.value
    }

    for (const fname of args.positionals)
    {
        try {
            const data = await fs.readFile(fname, {encoding: 'UTF-8'})
            const value = (
                args.values.jsonl ?
                    args.values.test ?
                        data.split("\n").slice(0, -1).map(s => [null, JSON.parse(s)])
                      : data.split("\n").slice(0, -1).map(s => JSON.parse(s))
                  : JSON.parse(data)
            )

            if (args.values.test) {
                if (!Array.isArray(value)) {
                    errors++
                    console.log(`${fname}: ERROR expecting an array`)
                }

                let index = 0
                for (const item of value)
                {
                    const display = `${fname}[${args.values.jsonl ? index+1 : index}]`

                    if (typeof item === 'string' || item instanceof String)  // skip comments
                        continue
                    if (!Array.isArray(item) || (item.length < 2 || item.length > 3)) {
                        errors++
                        console.log(`${display}: ERROR expecting a 2-tuple or 3-tuple`)
                        continue
                    }

                    let expect, name, val
                    if (item.length == 3)
                        [expect, name, val] = item
                    else
                        [expect, val] = item, name = ''

                    if (typeof expect !== 'boolean' && ! expect instanceof Boolean) {
                        errors++
                        console.log(`${display}: ERROR expecting a boolean first item`)
                        continue
                    }
                    if (typeof name !== 'string' && ! name instanceof String) {
                        errors++
                        console.log(`${display}: ERROR expecting a string for name`)
                        continue
                    }

                    errors += processing(display, val, checker, name,
                                         expect, args.values.report, times, overhead)

                    index += 1
                }
            }
            else
                errors += processing(fname, value, checker, '',
                                     null, args.values.report, times, overhead)
        }
        catch (e) {
            errors++
            console.log(`${fname}: ERROR (${String(e).replace('\n', '\\n')})`)
        }
    }

    checker_free()
    process.exit(errors ? 4 : 0)
}
