import fs from "fs"

const datetime = new Date();
const string = `${datetime.getDate()}/${datetime.getUTCMonth()}/${datetime.getFullYear()} | ${datetime.getHours()}:${datetime.getMinutes()}:${datetime.getSeconds()}`

const line = "Create an english song inspired by the song 'Crazy for You', in the style of Jazz."
var data = fs.readFileSync("prompt", 'utf-8').replace(line, string)
fs.writeFileSync("prompt", data)
