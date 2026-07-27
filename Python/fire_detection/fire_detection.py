
import serial # Enables serial communications with base node SS
from collections import deque # Utilizing Python's Circular List 
import time
import csv # For data storage 

class FireCracker():
    def __init__(self, node_id, buffer_size = 200) -> None:
        self.id = node_id
        self.samples = deque(maxlen= buffer_size) # Stores data as one reading 

        # Average Metrics for each node
        self.avg_temp = 0.0
        self.avg_pm25 = 0.0
        self.avg_humidity = 0.0

    def add_data(self, timestamp, temp, humidity, pm25):
        # Tuple that contains sensor infromation
        self.samples.append((timestamp, temp, humidity, pm25))
    
    # Averaging the temperature 
    def avg_all_data(self):
        # In case the samples list is empty
        if len(self.samples ) == 0:
            return 0.0, 0.0, 0.0
        
        total_temp = 0.0
        total_humidity = 0.0
        total_pm25 = 0.0

        for sample in self.samples:
            total_temp += sample[1]
            total_humidity += sample[2]
            total_pm25 += sample[3]
        return (total_temp / len(self.samples)), (total_humidity / len(self.samples)), (total_pm25 / len(self.samples))
    
# Creating a serial object
try:
    ser = serial.Serial(port="/dev/ttyACM1", baudrate=115200)
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    exit(1)

# Creating sensor objeccts 
Sensor1 = FireCracker(1, buffer_size=200)
Sensor2 = FireCracker(2, buffer_size=200)

try: 
    # Creating a csv file and writing to it ("a": Append mode
    with open("f_dataset3.csv", "a", newline="") as f: 
        
        writer = csv.writer(f) # Writing to CSV file 
        # Loop to continously read data from base node via serial port 
        while True:
            try:
                # Data aquisition from serial 
                value = ser.readline() # Grab all the data up until newline 
            except serial.SerialException as e:
                print(f"Error reading from serial port: {e}")
                continue

            # Data processing: decode the data and store it in a array
            value_str = value.decode("utf-8").strip() # Value needs to be decoded, leading and training white spaces removed 
            # If value_str is empty continue 
            if value_str == "":
                continue
            data = value_str.split(",") # Seperating the data and obtaining a list 
            print("Raw Data:",data)
            # Skip the malformed data
            if len(data) != 4:
                continue

            # Try collecting data from sensors 
            try:
                timestamp = time.time()
                node_id = int(data[0]) # Grab FireCracker ID (FireCracker ID Tag)
                temperature = float(data[1])
                humidity = float(data[2])
                air_quality_pm25 = float(data[3]) # Turn the data value into a float and remove the newline character 
            except ValueError as e: 
                print(f"Error parsing data: {e}")
                continue

            current = None # Placeholder for the current sensor object

            # Distinguish between FireCrackers
            if node_id == 1:
                Sensor1.add_data(timestamp, temperature, humidity, air_quality_pm25)
                Sensor1.avg_temp, Sensor1.avg_humidity, Sensor1.avg_pm25 = Sensor1.avg_all_data()
                current = Sensor1 # Giving sensor 1 an Alias for easier access
            elif node_id == 2:
                Sensor2.add_data(timestamp, temperature, humidity, air_quality_pm25)
                Sensor2.avg_temp, Sensor2.avg_humidity, Sensor2.avg_pm25 = Sensor2.avg_all_data()
                current = Sensor2 # Giving sensor 2 an Alias for easier access
                
            else:
                print(f"Unknown Node ID: {node_id}")
                continue
        
            if current.avg_temp > 25.0 and current.avg_humidity < 50 and current.avg_pm25 > 30:
                print(f"Warning Potential Fire at Node:{node_id}")
            
            # Storing everything in CSV file
            writer.writerow([timestamp, node_id, temperature, humidity, air_quality_pm25])
            f.flush() # Sending data from RAM to Disk for permamenet sotrage

except KeyboardInterrupt:
    print("Program terminated by user.")
finally:
    ser.close() # Closing the serial port

"""
Power Consumption Calculations:
PM2.5 Particle Matter Sensor AVG PWR: (3.3v*70ma) = 0.231 Watts
DHT22 Temperature and Humidity Sensor AVG PWR: (3.3v*1.5ma) = 0.00495 Watts
Total Power Consumption Sensors: 0.23595 Watts/Second
Sensors + Microcontroller (ESP32) AVG PWR: 0.23595 + (3.3v*379ma) = 1.5 Watts/Second

"""