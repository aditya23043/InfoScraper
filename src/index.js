import puppeteer from "puppeteer";

const url = "https://suno.com/create";

const main = async () => {
  const browser = await puppeteer.launch({
    headless: false,
    browser: "firefox",
    args: [
      // "--disable-notifications",
      // "--disable-features=BlockThirdPartyCookies",
      // "--profile ~/.mozilla/firefox/uqt3lbms.default-release/"
    ],
  });

  const page = (await browser.pages()).at(0);
  await page.goto(url);

  await page.waitForSelector('textarea.custom-textarea');
  await page.type('textarea.custom-textarea', "something");

  await new Promise(resolve => setTimeout(resolve, 5000));

  await browser.close();
};

main();
