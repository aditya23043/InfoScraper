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

}

const init = async (prompts) => {

  const browser = await puppeteer.launch({
    browser: "firefox",
    headless: false,
    userDataDir: "/home/adi/.mozilla/firefox/uqt3lbms.default-release",
  });

  const page = (await browser.pages()).at(0);
  await page.goto("https://riffusion.com");

  for (const line in prompts) {
    await main(page, prompts.at(line));
    console.log(`Downloaded: ${prompts.at(line)}`)
  }
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
