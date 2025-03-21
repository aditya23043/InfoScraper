# How to use?

<details>

<summary>Old Instructions for C</summary>


- Build it yourself
- Go in the root directory of the repo and run either of these commands

```
make
```

- OR

```
gcc -Wall src/main.c -o bin/main -lX11 -lXtst
```

- Then run the binary

```
./bin/main <song prompt>
```

</details>

## Basic Setup
  - I have a `makefile` setup such that automatically installs puppeteer and the required firefox binary in your $CACHE directory (~/.cache for Linux) whenever you run this cmd...

```
make
```

## Important NOTE
- This script utilizes the Firefox browser and will automatically download the binary and required files into cache
- I am assuming that you are already logged into https://suno.com and hence we need to maintain the cookies in the puppeteer instance of firefox as well
- In order to do that, we have to pass the User data directory that firefox generates into `src/index.js` on line 9.
- I have provided the sample directory name for your reference.
- Do make sure that you change that to your directory before running the program
- In order to prevent file locking, close all other firefox instances

## Run The Program
  - This cmd runs `node src/index.js`

```
make run
```

- OR 

```
yarn run main
```

# Dev Log

## 2025-02-12 19:08

> I am being forced to use python (which is not even a real programming language) since it provides a good abstraction layer over HID control /s

- Main Objective: Automating extracting data from websites
- Note that for this automation, you need a dedicated system since I will be using this program on websites which have a paid API
- Most websites have a limit on the requests we can send per day per account so I will be using https://temp-mail.org for making new accounts
- They have a free API called RapidAPI which lets us send 100 reqs per day which is more than enough for our use case
- So, I will be using temp-mail to generate new accounts once limit has been reached on the current account
- For now, I am targeting www.udio.com

## 2025-03-04 14:52

- udio has added a captcha in order to prevent automation and guess what? its working. I am not able to bypass it
- Hence, I am changing my target from udio to suno ai for now

## 2025-03-05 15:03

- completed the script for automating downloading ai generated songs from suno ai
- optionally, you could install `dunst` on your system to see the timer countdowns

> NOTE: disable "Always ask you where to save files" in your browser so that the browser wont prompt you to provide download path every time it downloads the songs

## 2025-03-14 18:43

- Difficulties faced with using C with XLib for browser automation
  - hard-coded values for time countdowns are either way too long for good performing machines (time wastage) or way too short (completely breaks down the script) for low performing machines
  - On some systems, I just cant seem to bring focus on the buttons which needs focus due to unknown reasons
  - The script is very performant but not at all flexible to work on "all" systems
- I might be switching over to the dreadful language of all time, JavaScript (with Puppeteer framework) because of its great abstraction over web utilities which aid immensely for web automation

## 2025-03-16 23:00

- While trying to figure out how to detect when generated audio is ready for download, I have noticed that https://suno.com is now asking for captcha when trying to generate the song
- So, suno.com is also now out of the options along with udio.com
- A major advancement made was shifting from C to JS (with puppeteer) since it makes the program very flexible and easy for web automation

## 2025-03-21 17:57

- I was able to do the following with the Puppeteer JS framework with ease...
  - Open up firefox/chrome/chromium browser
  - Wait till it has properly opened
  - Go to a specific website (suno.com) in our case and again, wait only the required time to load the webpage
  - Detect the textbox and enter text into it and then click the submit button without the need to hardcode any values
  - Detect when the loader spin document element goes out of the DOM so that we can download the songs
  - Detect any Captcha popups
- But the problem I faced with this method was that even though I was initially able to generate the songs, after some tries, the website might have put a stronger bot tracker on my IP or something because of which I started getting a captcha every single time
- To conquer this, I tried to load the Stealth plugin of the Puppeteer framework alongside adding a little bit of delay when typing each character and clicking the generate button to try to deceive the bot tracker but even that did not work
- I even tried to run the script through a headless browser but that method failed as well
- However, I was able to generate the song without any captcha if I did all the steps manually
- So, I concluded that the website must be able to track that I am running a script somehow
- To try to solve this issue, I will be going back with the previous method and try to manipulate HID (keyboard and mouse) to get the final result using C
