import pyautogui
import time
import os

def hover(duration, item):
    os.system("notify-send 'Hover over the {item}' -t {time}".format(item=item, time=duration*1000))
    for i in range(duration, 0, -1):
        os.system("notify-send "+ str(i) + " -t 1000");
        time.sleep(1)

os.system("firefox --new-window https://suno.com/create &")

time.sleep(15)

hover(5, "Text Box")

textbox = pyautogui.position()
print("Textbox: ", textbox)
