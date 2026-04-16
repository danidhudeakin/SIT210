import tkinter as tk
import RPi.GPIO as GPIO

# Setup GPIO
GPIO.setmode(GPIO.BCM)

LIVING = 17
BATHROOM = 27
CLOSET = 22

GPIO.setup(LIVING, GPIO.OUT)
GPIO.setup(BATHROOM, GPIO.OUT)
GPIO.setup(CLOSET, GPIO.OUT)

# Turn all OFF initially
GPIO.output(LIVING, 0)
GPIO.output(BATHROOM, 0)
GPIO.output(CLOSET, 0)

# Function to control LEDs
def select_room():
    choice = room.get()

    # turn all OFF first
    GPIO.output(LIVING, 0)
    GPIO.output(BATHROOM, 0)
    GPIO.output(CLOSET, 0)

    if choice == "living":
        GPIO.output(LIVING, 1)
    elif choice == "bathroom":
        GPIO.output(BATHROOM, 1)
    elif choice == "closet":
        GPIO.output(CLOSET, 1)

# Exit function
def exit_app():
    GPIO.cleanup()
    window.destroy()

# GUI
window = tk.Tk()
window.title("Light Control")

room = tk.StringVar()

tk.Label(window, text="Choose a Room").pack()

tk.Radiobutton(window, text="Living Room", variable=room, value="living", command=select_room).pack()
tk.Radiobutton(window, text="Bathroom", variable=room, value="bathroom", command=select_room).pack()
tk.Radiobutton(window, text="Closet", variable=room, value="closet", command=select_room).pack()

tk.Button(window, text="Exit", command=exit_app).pack()

window.mainloop()
