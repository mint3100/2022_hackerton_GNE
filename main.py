import tkinter
import serial
import serial.tools.list_ports
import time


window = tkinter.Tk()
listbox = tkinter.Listbox(window, selectmode='extended', height=0)
window.title("LAMA")
window.geometry("640x400+100+100")
window.resizable(True, True)
entry = tkinter.Entry(window)
entry.pack()

ports = serial.tools.list_ports.comports()
lists = []
available_ports = []
for p in ports:
    available_ports.append(p.device)
for p in lists:
    listbox.insert(p,available_ports)

def connect():
    arduino = serial.Serial(port = entry.get(), baudrate = 9600)
    time.sleep(3)
    arduino.write(b'TEMP')
    time.sleep(2)
    data = arduino.readline().decode("utf-8")
    message = tkinter.Message(window, text=data, width=100, relief="solid")
    message.pack()

listbox.pack()
button = tkinter.Button(window, text="아두이노 연결", overrelief="solid", width=15, command=connect, repeatdelay=1000, repeatinterval=100)
button.pack()

window.mainloop()
