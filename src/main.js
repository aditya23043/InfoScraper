import puppeteer from "puppeteer";
import fs from "fs"

const main = async (page, text) => {

  await page.waitForSelector('div.flex.h-12.w-full.min-w-0.cursor-pointer.items-center.gap-1');
  await page.click('div.flex.h-12.w-full.min-w-0.cursor-pointer.items-center.gap-1');

  await page.waitForSelector('textarea[aria-label="Prompt for a song"]')
  // clear textarea
  await page.focus('textarea[aria-label="Prompt for a song"]')
  await page.keyboard.down("Control")
  await page.keyboard.down("A")
  await page.keyboard.up("A")
  await page.keyboard.up("Control")
  await page.keyboard.press("Backspace")

  await page.type('textarea[aria-label="Prompt for a song"]', text)

  await page.waitForSelector('button[data-sentry-element="Button"]')
  await page.click('button[data-sentry-element="Button"]')

  // wait for the songs to generate
  await page.waitForFunction(() => {
    const h4Elements = Array.from(document.querySelectorAll('h4'));
    return h4Elements.every(h4 => !h4.textContent.trim().startsWith('Generating'));
  }, {timeout: 100000});

  // wait for atleast one "three dots" button to load
  await page.waitForSelector('button[aria-label^="More options for"]')
  
  console.log("done generating")
  
  // write log
  const h4_arr = await page.evaluate(() => {
    return Array.from(document.querySelectorAll('h4.text-primary.truncate.transition-colors')).map(h4 => h4.textContent)
  })
  console.log(h4_arr.at(0), h4_arr.at(1))
  console.log(h4_arr.length, song_names.length)

  if (h4_arr === song_names) {
    console.log("no new songs!")
    return;
  }

  const datetime = new Date(Date.now());
  fs.appendFile("src/output", `Prompt: ${text}\t(${datetime.getDate()}/${datetime.getUTCMonth()+1}/${datetime.getFullYear()} | ${datetime.getHours()}:${datetime.getMinutes()}:${datetime.getSeconds()})\n  Song 1: ${h4_arr.at(0)}\n  Song 2: ${h4_arr.at(1)}\n\n`, (err) => {
    if (err) {
      throw err;
    }
  })

  // download
  const buttons = await page.$$('button[aria-label^="More options for"]')

  buttons[0].click();

  await page.waitForSelector('svg[aria-hidden="true"][data-icon="cloud-arrow-down"]');
  await page.hover('svg[aria-hidden="true"][data-icon="cloud-arrow-down"]');

  await page.waitForSelector('svg[aria-hidden="true"][data-icon="file-music"]');
  await page.click('svg[aria-hidden="true"][data-icon="file-music"]');

  await new Promise((resolve) => setTimeout(resolve, 100))

  buttons[1].click();

  await page.waitForSelector('svg[aria-hidden="true"][data-icon="cloud-arrow-down"]');
  await page.hover('svg[aria-hidden="true"][data-icon="cloud-arrow-down"]');

  await page.waitForSelector('svg[aria-hidden="true"][data-icon="file-music"]');
  await page.click('svg[aria-hidden="true"][data-icon="file-music"]');

  // remove the prompt from the prompts file
  const fileContents = fs.readFileSync(process.argv[2], "utf-8").replace(text+"\n", "")
  console.log(fileContents)
  fs.writeFileSync(process.argv[2], fileContents)

}

const init = async (prompts) => {

  const browser = await puppeteer.launch({
    browser: "firefox",
    headless: false,
    userDataDir: "/home/adi/.mozilla/firefox/uqt3lbms.default-release",
  });

  const page = (await browser.pages()).at(0);
  await page.goto("https://riffusion.com");

  song_names = song_names.concat(await page.evaluate(() => {
    return Array.from(document.querySelectorAll('h4[class="text-primary truncate transition-colors hover:underline max-w-full"]')).map(h4 => h4.textContent)
  }))

  for (const line in prompts) {
    await main(page, prompts.at(line));
    console.log(`Downloaded: ${prompts.at(line)}`)
  }

  console.log("Successfully generated songs corresponding to all the prompts!")

  await browser.close();
}

// checking args
if (process.argv.length != 3) {
  console.error("ERROR!\nUsage: node src/main.js <path/to/prompts>")
  process.exit(1)
}

// parsing through the prompts file
fs.readFile(process.argv[2], 'utf-8', (err, data) => {
  if (err) {
    console.log(err);
  } else {
    init(data.trim().split("\n"))
  }
});

let song_names = []
