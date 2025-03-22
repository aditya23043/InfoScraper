target: something

something:
	yarn add puppeteer
	npx puppeteer browsers install firefox

run: src/main.js
	node src/main.js
