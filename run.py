from pynput.keyboard import Key, Controller
from time import sleep
from os import system, chdir
import subprocess

def main():
    keyboard = Controller_d()

    system('clear')
    chdir('./pca10056/s140/armgcc')
    
    make = subprocess.Popen('make')
    make.wait()

    if (subprocess.check_call('make') != 0):
        exit(0)

    system('gnome-terminal')
    sleep(0.2)

    commands = ('JLinkExe',
                'device NRF52840_XXAA',
                'si SWD',
                'speed 4000',
                'connect',
                'loadfile ./_build/nrf52840_xxaa.hex',
                'r',
                'g',
                'q',
                'exit')

    for cmd in commands:
        keyboard.type_and_enter(cmd)

class Controller_d(Controller):
    def __init__(self):
        Controller.__init__(self)

    def press_and_release(self, key):
        self.press(key)
        self.release(key)
    
    def type_and_enter(self, msg):
        self.type(msg)
        self.press_and_release(Key.enter)
        sleep(0.05)
    
if __name__ == '__main__':
    main()