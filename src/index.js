import puppeteer from "puppeteer";

const url = "https://suno.com/create";

async function waitForGenerationCompletion(page) {
  await page.waitForFunction(
    () => {
      return (
        document.querySelector("svg.animate-spin.text-white\\/75.w-8.h-8") ===
        null
      );
    },
    { timeout: 60000 }
  );
}

const main = async () => {
  const browser = await puppeteer.launch({
    headless: false,
    browser: "firefox",
    userDataDir: '/home/adi/.mozilla/firefox/lyh5xzgn.default-release' // asus v241 aio
    // userDataDir: '/home/adi/.mozilla/firefox/uqt3lbms.default-release' // asus tuf a15
  });

  const page = (await browser.pages()).at(0);
  await page.goto(url);

  await page.waitForSelector("textarea.custom-textarea");
  await page.type(
    "textarea.custom-textarea",
    "write a song about mechanical keyboards and lenovo Thinkpads"
  );

  await page.waitForSelector('button[aria-label="Create"]');
  await page.click('button[aria-label="Create"]');


  await new Promise((resolve) => setTimeout(resolve, 30000));
  await waitForGenerationCompletion(page);

  console.log("Generated!");

  await browser.close();
};

main();

// <svg xmlns="http://www.w3.org/2000/svg" fill="currentColor" viewBox="0 0 24 24" class="animate-spin text-white/75 w-8 h-8"><path d="M12 2c5.52 0 10 4.48 10 10s-4.48 10-10 10-10-4.48-10-10c0-.41.34-.75.75-.75s.75.34.75.75c0 4.41 3.59 8 8 8s8-3.59 8-8-3.59-8-8-8c-.41 0-.75-.34-.75-.75S11.59 2 12 2z"></path></svg>
