import puppeteer from "puppeteer"

const main = async (text) => {

	const browser = await puppeteer.launch({
		browser: "firefox",
		headless: true,
		userDataDir: "/home/adi/.mozilla/firefox/uqt3lbms.default-release",
	});

	const page = (await browser.pages()).at(0);

	await page.goto("https://rclyricsband.com/");

	await page.waitForSelector('input[type="text"][name="search"]')
	await page.type('input[type="text"][name="search"]', text)

	await page.waitForSelector('button[type="submit"][class="search-button"]')
	await page.click('button[type="submit"][class="search-button"]')

	await page.waitForSelector('a.song_search')
	await page.click('a.song_search')

	await page.waitForSelector('button[id="lrc"]')
	await page.click('button[id="lrc"]')

	await browser.close()

}

main("sound of muzak");
