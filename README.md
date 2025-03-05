> I am being forced to use python (which is not even a real programming language) since it provides a good abstraction layer over HID control /s

# Dev Log

## 2025-02-12 19:08

- Main Objective: Automating extracting data from websites
- Note that for this automation, you need a dedicated system since I will be using this program on websites which have a paid API

- Most websites have a limit on the requests we can send per day per account so I will be using https://temp-mail.org for making new accounts
- They have a free API called RapidAPI which lets us send 100 reqs per day which is more than enough for our use case
- So, I will be using temp-mail to generate new accounts once limit has been reached on the current account

- For now, I am targeting www.udio.com

## 2025-03-04 14:52

- udio has added a captcha in order to prevent automation and guess what? its working. I am not able to bypass it
- Hence, I am changing my target from udio to suno ai for now
