import puppeteer from "puppeteer";

const url = "https://suno.com/create";

const main = async () => {
  const browser = await puppeteer.launch({
    headless: false,
    browser: "firefox",
    // userDataDir: '/home/adi/.mozilla/firefox/lyh5xzgn.default-release'
    userDataDir: '/home/adi/.mozilla/firefox/uqt3lbms.default-release'
  });

  const page = (await browser.pages()).at(0);
  await page.goto(url);

  await page.waitForSelector('textarea.custom-textarea');
  await page.type('textarea.custom-textarea', "write a song about mechanical keyboards and lenovo Thinkpads");

  await page.waitForSelector('button[aria-label="Create"]');
  await page.click('button[aria-label="Create"]');

  await new Promise(resolve => setTimeout(resolve, 5000));

  await browser.close();
};

main();
