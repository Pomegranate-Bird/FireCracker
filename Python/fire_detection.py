import serial 
import matplotlib as plt

# Creating a serial object
ser = serial.Serial(port="/dev/ttyUSB0", baudrate=115200)

# Loop to continously read data from base node via serial port 
while True:
    # Value needs to be decoded
    value = ser.readline() # Grab all the data up until newline 
    value_str = str(value, 'UTF-8')
    print(value_str)


# Get data from the MCU 

# Keep most of the logic, fire detection logic on Python

# Connect to the receiver, get data from MCU via Serial then test bluetooth capabilities

# Utilizing that data from the MCU, estimate whether we have a fire. Utilize thresholds to determine if the readings near a node are too high. 

# Get the data from each node. I want to pass in data from each node object, if the data is abnormal for that node send it a signal. Flash an LED there is a fire there 

