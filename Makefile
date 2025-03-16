target: something

something:
	yarn add puppeteer
	npx puppeteer browsers install firefox

run: src/index.js
	node src/index.js
