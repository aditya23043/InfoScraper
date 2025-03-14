import puppeteer from "puppeteer";

const url = "https://suno.com/create";
const browser = puppeteer.launch();

const main = async () => {
	const browser = await puppeteer.launch();
	await browser.close();
}
