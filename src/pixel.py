import mouse
import time
import os

pos = []
index = 0

def get_pos(text):
    print(text)
    mouse.wait()
    return mouse.get_position()

text_box = get_pos("Click on the prompt text box on riffusion")
print("Text Box", text_box, "\n")
pos.append(text_box)

time.sleep(0.5)

prompt_button = get_pos("Click on the 'PROMPT' button")
print("Prompt Button", prompt_button, "\n")
pos.append(prompt_button)

time.sleep(0.5)

text_input = get_pos("Click on the prompt input box")
print("Text Input", text_input, "\n")
pos.append(text_input)

time.sleep(0.5)

three_dots_1 = get_pos("Click on the top three dots")
print("1st three dots", three_dots_1, "\n")
pos.append(three_dots_1)

time.sleep(0.5)

download_button_1 = get_pos("Click on the 1st download button")
print("1st three dots", download_button_1, "\n")
pos.append(download_button_1 )

time.sleep(0.5)

mp3_1 = get_pos("Click on the 1st MP3 button")
print("1st MP3 button", mp3_1, "\n")
pos.append(mp3_1)

time.sleep(0.5)

three_dots_2 = get_pos("Click on the next three dots")
print("2nd three dots", three_dots_2, "\n")
pos.append(three_dots_2)

time.sleep(0.5)

download_button_2 = get_pos("Click on the 2nd download button")
print("2nd three dots", download_button_1, "\n")
pos.append(download_button_2)

time.sleep(0.5)

mp3_2 = get_pos("Click on the 2nd MP3 button")
print("2nd MP3 button", mp3_1, "\n")
pos.append(mp3_2)

with open("riffusion.py", "r+") as f:
    lines = f.readlines()
    f.seek(0)
    for line in lines:
        if "pyautogui.click" in line:
            f.write("    pyautogui.click(" + str(pos[index][0]) + ", " + str(pos[index][1]) + ")\n")
            index += 1
        else:
            f.write(line)
