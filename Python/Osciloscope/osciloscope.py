from tkinter import *
from pymata4 import pymata4
import threading as thread
from time import sleep

board = pymata4.Pymata4()
bgc = '#201d1d'

ENCODER = 5
FirstInit = True


board.set_pin_mode_analog_input(ENCODER)

root = Tk()

root.geometry('500x500')
root.config(bg='#201d1d')

osciloscopeLine = Canvas(root,bg=bgc)
u = Label(
    root,
    text = "0.0 V",
    font=('Arial',30,'bold'),
    fg='#9a9ce7',
    bg=bgc
)
title = Label(
    root,
    pady=30,
    fg='#3a4c5a',
    bg=bgc,
    text='OSCILOPY',
    font=('Arial',40,'bold'),
    
)
divisions = Label(root,
                  text="-0V",
                  font=("Arial",8),
                  bg= bgc,
                  fg='white'                 
)

title.pack()

osciloscopeLine.pack()


osciloscope = osciloscopeLine.create_rectangle(250,250,250,250,width=2,fill='red')
u.place(x=200,y=400)

def MoveDots():
    while True:
        sleep(0.002)
        osciloscopeLine.move('all',-1,0)
def UpdateValue():
    global FirstInit
    if(FirstInit):
        sleep(1)
        FirstInit = False
    while True:
        encoder_value = board.analog_read(ENCODER)[0]
        encoder_value = (encoder_value*50)/1023
        osciloscope = osciloscopeLine.create_rectangle(440,125,440,125,width=1.5,fill='blue')
        osciloscopeLine.moveto(osciloscope,375,125-encoder_value*2)
        temp = str(round(encoder_value/10,1))+" V"
        u.config(text=temp)
        print(encoder_value)

divisions.place(x=443,y=241)

thr1 = thread.Thread(target=MoveDots,daemon=True)
thr1.start()
thr = thread.Thread(target=UpdateValue, daemon=True)
thr.start()
root.mainloop()
