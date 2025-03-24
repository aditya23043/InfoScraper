import fs from "fs"

const line = "Create an english song inspired by the song 'Crazy for You', in the style of Jazz."
var data = fs.readFileSync("prompt", 'utf-8').replace(line, "")
fs.writeFileSync("prompt", data)
