import { parseArgs } from 'node:util'
import fs from 'node:fs'

// TODO escaping?
const json_path = (path) => '.' + path.join('.')

function report(rep)
{
    if (rep.length === 0) return ''

    let reps = []
    for (const [message, path] of rep)
        reps.push(`${json_path(path)}: ${message}`)

    return ' (' + reps.join('; ') + ')'
}

export default function main(checker)
{
    const options = {
      'verbose': { type: 'boolean', short: 'v' },
      // 'times': { type: 'string', short: 'T' },
      'report': { type: 'boolean', short: 'r' },
    }

    const args = parseArgs({options, allowPositionals: true})

    // args.hasOwnProperty('verbose')
    // args.verbose === undefined

    for (const fname of args.positionals)
    { 
        try {
            fs.readFile(fname, (err, data) => {
                if (err) throw err
                const value = JSON.parse(data)
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
