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

    pyautogui.click(682, 102)
    time.sleep(0.1)
    pyautogui.click(441, 109)
    time.sleep(0.1)
    pyautogui.click(469, 175)
    time.sleep(0.1)
    pyautogui.hotkey("ctrl", "a")
    pyautogui.press("backspace")

    pyautogui.write(prompt)
    time.sleep(1)

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

    if 'content guidelines' in text:
        with open(sys.argv[1], 'r') as f:
            temp = f.readlines()
        with open(sys.argv[1], 'w') as f:
            for line in temp:
                if line != prompt:
                    f.write(line)
                elif line == prompt:
                    print("line removed!")
        print("Prompt didn't meet content guidelines: ", prompt)
        return;


    while(True):
        text = ""
        if(platform.system() == "Linux"):
            os.system("scrot -o /tmp/screen.png")
            screenshot = Image.open("/tmp/screen.png")
            text = pytesseract.image_to_string(screenshot)
        elif(platform.system() == "Windows"):
            screenshot = pyautogui.screenshot()
            text = pytesseract.image_to_string(screenshot)

        if 'Generating' in text:
            time.sleep(5)
        else:
            break;

    time.sleep(0.5)
    pyautogui.click(1445, 327)
    time.sleep(0.5)
    pyautogui.click(1260, 751)
    time.sleep(0.5)
    pyautogui.click(1472, 749)

    time.sleep(0.5)
    pyautogui.click(1438, 445)
    time.sleep(0.5)
    pyautogui.click(1252, 872)
    time.sleep(0.5)
    pyautogui.click(1477, 870)

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
