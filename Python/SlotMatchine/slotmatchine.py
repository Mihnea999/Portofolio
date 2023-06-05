from tkinter import *
from PIL import ImageTk, Image  
import random

money = 1_000
wining_percentage = 75
winning_ammount = 0
lose_amount = 0
bet_amount = 0.5


#color palette  
c_bg = '#4C4C6D'
c_fg = '#1B9C85'
b_bg = '#E8F6EF'
m_fg = '#FFE194'


root = Tk()

betID = IntVar()


raw_icons = ['ICONS/apple.png','ICONS/strawberry.png','ICONS/money.png','ICONS/book.png','ICONS/slot.png']
icons = list(map(lambda x: ImageTk.PhotoImage(Image.open(x).resize((80,80),Image.LANCZOS)), raw_icons))

root.geometry('500x600')
root.config(bg=c_bg)

root.columnconfigure(0,weight=1)
title = Label(
    root,
    text='PYSLOT',
    bg=c_bg,
    fg=b_bg,
    font=('Arial',40)
)
title.grid(row=0,column=0,sticky=N,columnspan=5)
moneytxt = Label(
    root,
    fg = m_fg,
    bg = c_bg,
    font=('Arial', 15),
    text=money
)
moneytxt.grid(row=0,column=1,sticky=E,pady=30,padx=20)
root.columnconfigure(1,weight=0)
Slot = Frame(
    root,
    bg = '#000000',
    height=400,
    width=500
)
Slot.grid(row=1,column=0,pady=100,columnspan=5)

Slot.columnconfigure(0,weight=6)
Slot.rowconfigure(0,weight=1)
Slot.rowconfigure(1,weight=1)
Slot.rowconfigure(2,weight=1)
image1 = Label(
    Slot,
    bg=c_bg,
    image=icons[3]
)
image1.grid(row=0,column=0)

image2 = Label(
    Slot,
    bg=c_bg,
    image=icons[3]
)
image2.grid(row=0,column=1)

image3 = Label(
    Slot,
    bg=c_bg,
    image=icons[4]
)
image3.grid(row=0,column=4)





def UpdateSlot(iconID: list()):
    global icons
    global money
    print(iconID)
    print(bet_amount)
    moneytxt.config(text=money)
    image1.config(image=icons[iconID[0]])
    image2.config(image=icons[iconID[1]])
    image3.config(image=icons[iconID[2]])


winnings = [
    [[0,0,0],1.3],     #apple         0
    [[1,1,1],1.6],     #strawberry    1
    [[2,2,2],2.0],     #MONEY         2
    [[3,3,3],2.6],     #BOOK          3
    [[4,4,4],5.0]      #Jackpot       4
]
winning_bait = [
    [3,3,random.randint(0,2)],
    [4,4,random.randint(0,3)],
    [2,2,random.randint(3,4)]
]

def SetBetAmmount():
    global bet_amount
    if(betID.get() == 4):
        bet_amount = 0.5
    elif(betID.get() == 3):
        bet_amount = 1
    elif(betID.get() == 2):
        bet_amount = 2
    else:
        bet_amount = 5
        
def CalculateWinings(winingId: int):
    global winnings
    global money
    global winning_ammount
    money += bet_amount * winnings[winingId][1]
    winning_ammount += bet_amount * winnings[winingId][1]
    money = round(money,2)
    UpdateSlot(winnings[winingId][0])

    
def create_random_slot():
    slot = []
    if(random.choice([True,False])):
        UpdateSlot(winning_bait[random.randint(0,2)])
        return
    else:
        for i in range(3):
            slot.append(random.randint(0,3))
        if (slot[0] == slot[1] == slot[2]):
            if(slot[2] > 1):
                slot[2] -= 1
            else:
                slot[2] += 1
    UpdateSlot(slot)  

def create_a_slot():
    global money
    global wining_percentage
    global winning_ammount
    global bet_amount
    
    money -= bet_amount
    
    if(winning_ammount <= 40 and random.randint(0,100) <= wining_percentage):
        wining = random.randint(0,100)
        if(wining <= 5/bet_amount):
            CalculateWinings(2)
        elif(wining > 5/bet_amount and wining < 15/bet_amount):
            CalculateWinings(1)
        elif(wining >= 15/bet_amount and wining <= 80/bet_amount):
            CalculateWinings(0)
        else:
            create_random_slot()
    elif(winning_ammount > 40 and random.randint(0,100) <= wining_percentage):
        wining = random.randint(0,200)
        if(wining <= 0.2/bet_amount):
            CalculateWinings(4)
        elif(wining > 0.2/bet_amount and wining < 5/bet_amount):
            CalculateWinings(3)
        elif(wining >= 5/bet_amount and wining <= 20/bet_amount):
            CalculateWinings(2)
        elif(wining >= 20/bet_amount and wining <= 40/bet_amount):
            CalculateWinings(1)
        elif(wining >= 40/bet_amount and wining <= 80/bet_amount):
            CalculateWinings(0)
        else:
            create_random_slot()
    elif(lose_amount > bet_amount * 4.9 and random.randint(0,200) < wining_percentage):
        create_a_slot(4)
    else:
        create_random_slot()
            
    




spin_button = Button(
    root,
    height=1,
    width=20,
    text='SPIN',
    bg = b_bg,
    fg='#000000',
    font=('Arial',15,'bold'),
    command=create_a_slot
)
spin_button.grid(row=2,column=0,sticky=N,columnspan=5)

bet_button = Radiobutton(
    root,
    height=1,
    width=5,
    activeforeground=c_fg,
    activebackground=c_bg,
    highlightcolor=c_fg,
    border=False,
    relief=SUNKEN,
    bg = c_bg,
    fg=c_fg,
    text='5  ',
    value=1,
    font=('Arial',14),
    state=ACTIVE,
    variable=betID,
    command=SetBetAmmount
)
bet_button.grid(row=3,column=0,columnspan=4)
bet_button1 = Radiobutton(
    root,
    height=1,
    width=5,
    activeforeground=c_fg,
    activebackground=c_bg,
    highlightcolor=c_fg,
    border=False,
    relief=SUNKEN,
    bg = c_bg,
    fg=c_fg,
    text='2  ',
    value=2,
    font=('Arial',14),
    state=ACTIVE,
    variable=betID,
    command=SetBetAmmount
)
bet_button1.grid(row=4,column=0,columnspan=4)
bet_button2 = Radiobutton(
    root,
    height=1,
    width=5,
    activeforeground=c_fg,
    activebackground=c_bg,
    highlightcolor=c_fg,
    border=False,
    relief=FLAT,
    bg = c_bg,
    fg=c_fg,
    text='1  ',
    value=3,
    font=('Arial',14),
    state=ACTIVE,
    variable=betID,
    command=SetBetAmmount
)
bet_button2.grid(row=5,column=0,columnspan=4)
bet_button3 = Radiobutton(
    root,
    height=1,
    width=5,
    activeforeground=c_fg,
    activebackground=c_bg,
    highlightcolor=c_fg,
    border=False,
    relief=SUNKEN,
    bg = c_bg,
    fg=c_fg,
    text='0.5',
    value=4,
    font=('Arial',14),
    state=ACTIVE,
    variable=betID,
    command=SetBetAmmount
)
bet_button3.grid(row=6,column=0,columnspan=4)


bet_button3.select()

#for i in range(10000):
#    create_a_slot()

root.mainloop()



