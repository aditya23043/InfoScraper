import pyautogui
import os
import time
import sys
import pytesseract
from PIL import Image
import platform
from datetime import datetime

now = datetime.now()

def foo(prompt):

    temp = []

    pyautogui.click(707, 88)
    time.sleep(0.1)
    pyautogui.click(617, 94)
    time.sleep(0.1)
    pyautogui.click(617, 133)
    time.sleep(0.1)
    pyautogui.hotkey("ctrl", "a")
    pyautogui.press("backspace")

    pyautogui.write(prompt)
    time.sleep(1)

    while(True):
        text = ""
        if(platform.system() == "Linux"):
            os.system("scrot -o /tmp/screen.png")
            screenshot = Image.open("/tmp/screen.png")
            text = pytesseract.image_to_string(screenshot)
        elif(platform.system() == "Windows"):
            screenshot = pyautogui.screenshot()
            text = pytesseract.image_to_string(screenshot)

        if 'heavy traffic' in text:
            time.sleep(60*5)
            return;
        elif 'content guidelines' in text:
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
            return;

        if 'Generating' in text:
            time.sleep(1)
        else:
            os.system("notify-send -t 0 something")
            break;

    time.sleep(0.5)
    pyautogui.click(1285, 238)
    time.sleep(0.5)
    pyautogui.click(1174, 523)
    time.sleep(0.5)
    pyautogui.click(1315, 523)

    time.sleep(0.5)
    pyautogui.click(1285, 319)
    time.sleep(0.5)
    pyautogui.click(1164, 601)
    time.sleep(0.5)
    pyautogui.click(1318, 601)

    with open(sys.argv[1], 'r') as f:
        temp = f.readlines()
    with open(sys.argv[1], 'w') as f:
        for line in temp:
            if line != prompt:
                f.write(line)

    with open(sys.argv[2], 'a') as f:
        f.write("Prompt: " + prompt + "\t(" + str(now.day) + "/" + str(now.month) + "/" + str(now.year) + " | " + str(now.hour) + ":" + str(now.minute) + ":" + str(now.second) + ")\n")


if (len(sys.argv) != 3):
    print("Usage: python riffusion.py <prompts file> <output log file>")
    exit(-1)

prompts = []
with open(sys.argv[1], 'r') as f:
    prompts = f.readlines()

os.system("firefox --new-window https://riffusion.com/library/my-songs &");

while(True):
    text = ""
    if(platform.system() == "Linux"):
        os.system("scrot -o /tmp/screen.png")
        screenshot = Image.open("/tmp/screen.png")
        text = pytesseract.image_to_string(screenshot)
    elif(platform.system() == "Windows"):
        pyautogui.screenshot()
        text = pytesseract.image_to_string(screenshot)

    time.sleep(1)
    if 'Riffusion' in text:
        break;

for prompt in prompts:
    foo(prompt)
    time.sleep(1)
