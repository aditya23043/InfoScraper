import puppeteer from "puppeteer";

if(process.argv.length != 3 && process.argv.length != 2){
  console.log("USAGE:\n  If you want to give prompts: node udio.js <prompts_file>\n  If you want it to randomly generate prompts: node udio.js");
  process.exit(-1);
}

const browser = await puppeteer.launch({
  browser: "firefox",
  userDataDir: "/home/adi/.mozilla/firefox/8d4q8916.riffusion",
  headless: false,
})

const page = (await browser.pages()).at(0);


await page.goto("https://udio.com/create");

// if prompt given
if(process.argv.length == 3){
  await page.waitForSelector('textarea')
  await page.focus('textarea');
  await page.type('textarea', "bruh idk what to type here lmao");
} else {
  // random prompt
  await page.waitForSelector('svg.lucide.lucide-dices');
  await page.click('svg.lucide.lucide-dices');
}

await page.click('button[title="Create"]');
