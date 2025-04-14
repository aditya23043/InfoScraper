import pyautogui
import os
import time
import sys
import pytesseract
from PIL import Image

def foo(prompt):

    temp = []

    pyautogui.click(500, 100)
    time.sleep(0.1)
    pyautogui.hotkey("ctrl", "a")
    pyautogui.press("backspace")

    pyautogui.write(prompt)
    time.sleep(2)

    while(True):
        os.system("scrot -o /tmp/screen.png")
        screenshot = Image.open("/tmp/screen.png")
        text = pytesseract.image_to_string(screenshot)

        if 'content guidelines' in text:
            with open(sys.argv[1], 'r') as f:
                temp = f.readlines()
            with open(sys.argv[1], 'w') as f:
                for line in temp:
                    if line != prompt:
                        f.write(line)
                        print(line, prompt)
                    elif line == prompt:
                        print("line removed!")
            print("Prompt didn't meet content guidelines: ", prompt)
        elif 'Generating' in text:
            time.sleep(1)
        else:
            print()
            break;

    time.sleep(0.5)
    pyautogui.click(1441, 327)
    time.sleep(0.5)
    pyautogui.click(1265, 748)
    time.sleep(0.5)
    pyautogui.click(1481, 748)

    time.sleep(0.5)
    pyautogui.click(1441, 446)
    time.sleep(0.5)
    pyautogui.click(1265, 864)
    time.sleep(0.5)
    pyautogui.click(1483, 864)

    with open(sys.argv[1], 'r') as f:
        temp = f.readlines()
    with open(sys.argv[1], 'w') as f:
        for line in temp:
            if line != prompt:
                f.write(line)


if (len(sys.argv) != 2):
    print("Usage: python riffusion.py <prompts file>")
    exit(-1)

prompts = []
with open(sys.argv[1], 'r') as f:
    prompts = f.readlines()

os.system("firefox --new-window https://riffusion.com/library/my-songs");

while(True):
    os.system("scrot -o /tmp/screen.png")
    screenshot = Image.open("/tmp/screen.png")
    text = pytesseract.image_to_string(screenshot)

    time.sleep(1)
    if 'Riffusion' in text:
        break;

for prompt in prompts:
    foo(prompt)
    time.sleep(1)
