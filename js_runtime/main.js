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
function processing(fname, index, value, checker, name, expected, report, times, empty)
{
    let error = 0

    // show performance
    // NOTE: jit, calls may take a lot of time at the beginning
    // NOTE: gc, may be irregular…
    if (times > 1)
    {
        let sum = 0.0
        let sum2 = 0.0
        let n = times
        while (n--) {
            const start = performance.now()
            let rep = report ? [] : null
            const valid = checker(value, '', rep)
            rep && (rep.length = 0)
            let delay = (1000.0 * (performance.now() - start)) - empty  // µs
            sum += delay
            sum2 += delay * delay
        }
        const avg = sum / times
        const stdev = Math.sqrt(sum2 / times - avg * avg)
        console.log(`${fname}: ${report ? 'rep' : 'nop'}`,
                    `${avg.toFixed(3)} ± ${stdev.toFixed(3)} µs (${empty.toFixed(3)})`)
    }

    // do it anyway for the result
    let rep = report ? [] : null
    const valid = checker(value, name, rep)

    // display validation result
    let source = index === null ? fname : `${fname}[${index}]`

    if (expected === null || valid === expected)
        console.log(`${source}: ${valid ? 'PASS' : 'FAIL'}${reporting(rep)}`)
    else
        console.log(`${source}: ERROR unexpected ${valid ? 'PASS' : 'FAIL'}${reporting(rep)}`)

    return error
}

export default async function main(checker_init, checker, checker_free)
{
    checker_init()

    const options = {
      'verbose': { type: 'boolean', short: 'v' },
      'times': { type: 'string', short: 'T' },
      'report': { type: 'boolean', short: 'r' },
      'test': { type: 'boolean', short: 't' },
      're2': { type: 'boolean' },
      'regexp': { type: 'boolean' },
      // TODO 'jsonl': { type: 'boolean' },
    }

    const args = parseArgs({options, allowPositionals: true})

    let errors = 0
    let times = args.values.times !== undefined ? Number(args.values.times) : 1

    if (isNaN(times))
    {
        console.log(`Unexpected --times: ${args.values.times}`)
        process.exit(1);
    }

    // reset regular expression engine
    if (args.values.regexp)
        jm_set_rx(RegExp)
    if (args.values.re2)
        jm_set_rx(require('re2'))

    // overhead estimation
    let empty = 0.0
    if (times > 1)
    {
        let n = times
        while (n--)
        {
            const start = performance.now()
            empty += 1000.0 * (performance.now() - start)
        }
        empty /= times
    }

    for (const fname of args.positionals)
    {
        try {
            const data = await fs.readFile(fname, { encoding: 'UTF-8'})
            const value = JSON.parse(data)

            if (args.values.test) {
                if (!Array.isArray(value)) {
                    errors++
                    console.log(`${fname}: ERROR expecting an array`)
                }
                for (let index = 0; index < value.length; index++)
                {
                    let item = value[index]

                    if (typeof item === 'string' || item instanceof String)  // skip comments
                        continue
                    if (!Array.isArray(item) || (item.length < 2 || item.length > 3)) {
                        errors++
                        console.log(`${fname}[${index}]: ERROR expecting a 2-tuple or 3-tuple`)
                        continue
                    }

                    let expect, name, val
                    if (item.length == 3)
                        [expect, name, val] = item
                    else
                        [expect, val] = item, name = ''

                    if (typeof expect !== 'boolean' && ! expect instanceof Boolean) {
                        errors++
                        console.log(`${fname}[${index}]: ERROR expecting a boolean first item`)
                        continue
                    }
                    if (typeof name !== 'string' && ! name instanceof String) {
                        errors++
                        console.log(`${fname}[${index}]: ERROR expecting a string for name`)
                        continue
                    }

                    errors += processing(fname, index, val, checker, name,
                                         expect, args.values.report, times, empty)
                }
            }
            else
                errors += processing(fname, null, value, checker, '',
                                     null, args.values.report, times, empty)
        }
        catch (e) {
            errors++
            console.log(`${fname}: ERROR (${String(e).replace('\n', '\\n')})`)
        }
    }

    checker_free()
    process.exit(errors ? 4 : 0)
}
