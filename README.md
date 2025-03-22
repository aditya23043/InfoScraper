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

<details>
<summary>Simple Note</summary>

- This script utilizes the Firefox browser and will automatically download the binary and required files into cache (Linux: /home/<username>/.cache)
- I am assuming that you are already logged into https://suno.com or https://riffusion.com and hence we need to maintain the cookies in the puppeteer instance of firefox as well
- Since puppeteer always opens a new temporary profile, we have to pass the User data directory that firefox generates into `src/main.js`
- I have provided the sample directory name for your reference.
- Do make sure that you change that to your directory before running the program
- Furthermore, In order to prevent file locking, close all other firefox instances
</details>

## Basic Setup

- Add Puppeteer and download suitable firefox binary

```
make
```

- OR

```
yarn add puppeteer
npx puppeteer browsers install firefox
```

- Put your user data directory for Firefox in `src/main.js` at line 59: `userDataDir: <path>`

  - For Windows: `userDataDir: "C:\Users\<username>\AppData\Roaming\Mozilla\Firefox\Profiles\*.default-release"`
  - For Linux: `userDataDir: "/home/<username>/.mozilla/firefox/*.default-release"`
  - If you are not able to find your directory, just type `about:profiles` in Firefox's search bar and see the path given as Root Directory

- Ensure you are logged in to the respective AI song generator in Firefox
- Ensure that you have unchecked this option in firefox's settings `Always ask you where to save files` so that firefox doesn't prompt you everytime the script downloads the song
- Close all other instances of firefox

### Dependencies

- `npm` (package name: nodejs)
- `yarn`
- `make` (optional)

## Run The Program

`node src/main.js </path/to/prompts>`

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

### Update 2:

- I would have really preferred writing the script in C but that would mean I will have to use some library to manipulate HID like Xlib. But the problem with that approach is that Xlib only works for X11 display manager obviously but 2 people in our group run Windows as their primary Operating system and since Windows does not run X11 as its display manager, my script won't work for them
- So unfortunately, I will have to move to a language which I don't even consider a programming language, Python

https://github.com/user-attachments/assets/2f7f1db7-16e5-4250-9065-c668ea8a89af

- I am able to hit the download button and go back to the text prompt in order to generate more songs but the actual download time is quite high (about ~100s)

## 2025-03-22 19:30

- https://suno.com was giving captcha with puppeteer and hardcoding mouse positions with python (and pyautogui) was fine but would not work on everyone's system out of the box without any configuration
- Hence, we shifted to https://riffusion.com which currently has no limits and does not give a captcha even with Puppeteer
- And as always, I am writing the development log after the event had occurred, so, the JS script is ready

## 2025-03-22 23:06

- The JS script is working as intended and as required, it is picking up the prompts from a separate file which contains newline separated prompts
- Problem: riffusion sometimes blocks the request due to high traffic and since my script does not account for that, it continues to download the top 2 prompts (which in this case would already have been downloaded since no new songs could be generated) and proceeds to the next prompt
  - To solve this issue, I must keep track of the songs downloaded and retry generating the prompt until the song is downloaded and until we reach a threshold amount of tries (to prevent infinite loop of trying to generate from prompts which cant generate a song)
