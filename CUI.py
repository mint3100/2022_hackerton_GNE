from re import T
import serial
import serial.tools.list_ports
import time
import os

# Create Date : 2022/10/16 (SAT)
# Creater : Jung Ju Hyeon (mint2792@mintserver.kr)
ports = serial.tools.list_ports.comports()

available_ports = []

for p in ports:
    available_ports.append(p.device)

count = len(available_ports)

print("현재 이용가능한 시리얼 포트 주소 :")
for i in range(count):
    print(i)
    print(available_ports[i])

print("시리얼 포트 주소 번호를 입력해주세요 :")
inp = int(input())
inp2 = available_ports[inp]
arduino = serial.Serial(port = inp2, baudrate = 9600)

time.sleep(5)

print(arduino.readable())
while True:
    
    r = arduino.readline()

    if r[:len(r)-1].decode() == "Detected!":
        os.system('clear')
        print("물기 감지!")
    else:
        os.system('clear')
        print("현재 온도/현재 습도 :");
        print(r[:len(r)-1].decode())