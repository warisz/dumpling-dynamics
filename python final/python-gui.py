import serial

ser = serial.Serial('/dev/cu.usbmodem11101', baudrate = 9600, timeout= 0.25)

ser.write('b'.encode())

print(ser.read())
