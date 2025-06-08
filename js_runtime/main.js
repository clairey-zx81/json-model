import { parseArgs } from 'node:util'
import fs from 'node:fs'

// TODO escaping?
const json_path = (path) => '.' + path.join('.')

function report(rep)
{
    if (rep === null || rep.length === 0) return ''

    let reps = []
    for (const [message, path] of rep)
        reps.push(`${json_path(path)}: ${message}`)

    return ' (' + reps.join('; ') + ')'
}

export default function main(checker)
{
    const options = {
      'verbose': { type: 'boolean', short: 'v' },
      'times': { type: 'string', short: 'T' },
      'report': { type: 'boolean', short: 'r' },
    }

    const args = parseArgs({options, allowPositionals: true})

    // args.hasOwnProperty('verbose')
    // args.verbose === undefined
    let times = args.values.times !== undefined ? Number(args.values.times) : 1

    if (isNaN(times))
    {
        console.log(`Unexpected --times: ${args.values.times}`)
        process.exit(1);
    }

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
            fs.readFile(fname, (err, data) => {
                if (err) throw err
                const value = JSON.parse(data)

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
                        let rep = args.values.report ? [] : null
                        const valid = checker(value, '', rep)
                        rep && (rep.length = 0)
                        let delay = (1000.0 * (performance.now() - start)) - empty  // µs
                        sum += delay
                        sum2 += delay * delay
                    }
                    const avg = sum / times
                    const stdev = Math.sqrt(sum2 / times - avg * avg)
                    console.log(`${fname}: ${args.values.report ? 'rep' : 'nop'}`,
                                `${avg.toFixed(3)} ± ${stdev.toFixed(3)} µs (${empty.toFixed(3)})`)
                }

                // do it anyway for the result
                let rep = args.values.report ? [] : null
                const valid = checker(value, '', rep)
                console.log(`${fname}: ${valid ? 'PASS' : 'FAIL'}${report(rep)}`)
            })
        }
        catch (e) {
            console.log(`${fname}: ERROR (${e})`)
        }
    }
}
