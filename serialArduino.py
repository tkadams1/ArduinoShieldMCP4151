# Importing Libraries
import serial  #pip install pyserial
import time

#This defines the serial port or arduino ID to use for serial communication
arduinoID = '/dev/cu.usbmodem14101'

#sets up the serial connection
arduino = serial.Serial(port= arduinoID, baudrate=9600, timeout=.1)

def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data

def main():
    while True:
        num = input("Enter a number: ") # Taking input from user
        value = write_read(num + '\n') # Sending the input to the arduino
        print(value) # printing the value returned from the arduino
        
main()