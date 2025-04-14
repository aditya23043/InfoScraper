import puppeteer from "puppeteer";

const main = async () => {
  const browser = await puppeteer.launch({
    browser: "firefox",
    userDataDir: "/home/adi/.mozilla/firefox/8d4q8916.riffusion",
    headless: false,
  });

  const page = (await browser.pages()).at(0);
  await page.goto("https://suno.com");

  await page.waitForSelector('xpath//span[contains(text(), "Create")]');
  await page.click('xpath//span[contains(text(), "Create")]');


};

main();
