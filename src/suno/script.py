import pyautogui
import os
import time

os.system("firefox --new-window https://suno.com/create &")

time.sleep(15)
os.system("notify-send 'browser open!'")

# focus the textbox
for i in range(22):
    pyautogui.press("tab")

pyautogui.write("rap battle between nothing and oneplus")

# focus create button
for i in range(4):
    pyautogui.press("tab")
pyautogui.press("enter")

time.sleep(30)
os.system("notify-send 'songs generated!'")

time.sleep(2)

pyautogui.moveTo(1887,233)
time.sleep(0.2)
pyautogui.click();
time.sleep(0.2)
os.system("notify-send 'in position!'")

# downloads button
pyautogui.moveTo(1687,426) # 458
# for i in range(7):
#     pyautogui.press("down")

pyautogui.press("enter")

time.sleep(1)
pyautogui.press("enter")


pyautogui.press("esc")
for i in range(10):
    pyautogui.hotkey("shift","tab")
