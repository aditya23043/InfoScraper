import puppeteer from "puppeteer";

const main = async (text) => {

  const browser = await puppeteer.launch({
    browser: "firefox",
    headless: false,
    userDataDir: "/home/adi/.mozilla/firefox/uqt3lbms.default-release",
  });

  const page = (await browser.pages()).at(0);
  await page.goto("https://riffusion.com");

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
  }, {timeout: 60000});

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

main("generate a song about the expensive PayTM stocks");

