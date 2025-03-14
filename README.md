# How to use?

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
