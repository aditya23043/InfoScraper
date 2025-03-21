import puppeteer from "puppeteer";
// import puppeteer from "puppeteer-extra";
// import StealthPlugin from "puppeteer-extra-plugin-stealth";

// puppeteer.use(StealthPlugin());

const url = "https://suno.com/create";

const main = async () => {
  const browser = await puppeteer.launch({
    headless: false,
    browser: "firefox",
    // executablePath: "/usr/lib/chromium/chromium",
    // userDataDir: '/home/adi/.mozilla/firefox/lyh5xzgn.default-release' // asus v241 aio
    userDataDir: '/home/adi/.mozilla/firefox/uqt3lbms.default-release' // asus tuf a15
    // userDataDir: '/home/adi/.config/chromium/',
  });

  const page = (await browser.pages()).at(0);
  // const page = await browser.newPage();
  await page.goto(url);

  const text = "write a song about mechanical keyboards and lenovo Thinkpads"
  await page.waitForSelector("textarea.custom-textarea");
  for (const char of text) {
    await page.type("textarea.custom-textarea", char);
    await new Promise((resolve) => setTimeout(resolve, 50));
  }

  await page.waitForSelector('button[aria-label="Create"]');
  await new Promise((resolve) => setTimeout(resolve, 500));
  await page.click('button[aria-label="Create"]');

  try {

    await page.waitForFunction(() => {
      return document.querySelector('iframe[title="Main content of the hCaptcha challenge"]') !== null;
    }, {timeout: 5000});

    await new Promise((resolve) => setTimeout(resolve, 2000));
    console.log("Captcha found!");

  } catch (error) {

    console.log("Captcha not found withing time limit!");
    await page.waitForFunction(
      () => {
        return (
          document.querySelector("svg.animate-spin.text-white\\/75.w-8.h-8") ===
          null
        );
      },
      { timeout: 60000 }
    );

    console.log("Generated!");
  }

  await browser.close();

};

main();

// <svg xmlns="http://www.w3.org/2000/svg" fill="currentColor" viewBox="0 0 24 24" class="animate-spin text-white/75 w-8 h-8"><path d="M12 2c5.52 0 10 4.48 10 10s-4.48 10-10 10-10-4.48-10-10c0-.41.34-.75.75-.75s.75.34.75.75c0 4.41 3.59 8 8 8s8-3.59 8-8-3.59-8-8-8c-.41 0-.75-.34-.75-.75S11.59 2 12 2z"></path></svg>
// challenge-container : captcha
// iframe title=Main content of the hCaptcha challenge
