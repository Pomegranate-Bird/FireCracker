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

        # Flags to detect a fire 
        self.low_humidity = False
        self.high_temperature = False
        self.high_pm25 = False
        self.fire = False

    def add_data(self, timestamp, temp, humidity, pm25):
        # Tuple that contains sensor infromation
        self.samples.append((timestamp, temp, humidity, pm25))
    
    # Averaging the temperature 
    def avg_all_data(self):
        # In case None is returned 
        if not self.samples:
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
ser = serial.Serial(port="/dev/ttyACM0", baudrate=115200)

# Creating sensor objeccts 
Sensor1 = FireCracker(1, buffer_size=1000)
Sensor2 = FireCracker(2, buffer_size=1000)




# Creating a csv file and writing to it ("a": Append mode
with open("f2_dataset2.csv", "a", newline="") as f: 
    
    writer = csv.writer(f)
    # Loop to continously read data from base node via serial port 
    while True:
        # Data aquisition from serial 
        value = ser.readline() # Grab all the data up until newline 
        
        # Data Processin: Decode data, place data into an array, type cast
        value_str = value.decode("utf-8").strip() # Value needs to be decoded 

        if not value_str:
            continue

        data = value_str.split(",") # Seperating the data and placing them in an array
        print("Raw Data:",data)

        # Skip the malformed data
        if len(data) != 4:
            continue

        # Collecting data from sensors 
        timestamp = time.time()
        node_id = int(data[0]) # Grab the id array identifier (FireCracker ID Tag)
        temperature = float(data[1])
        humidity = float(data[2])
        air_quality_pm25 = float(data[3]) # Turn the data value into a float and remove the newline character 



        # Distinguish between FireCrackers
        if node_id == 1:
          Sensor1.add_data(timestamp, temperature, humidity, air_quality_pm25)
          Sensor1.avg_temp, Sensor1.avg_humidity, Sensor1.avg_pm25 = Sensor1.avg_all_data()
        else:
          Sensor2.add_data(timestamp, temperature, humidity, air_quality_pm25)
          avg_temperature2, avg_humidity2, avg_pm252 = Sensor2.avg_all_data()
          Sensor2.avg_temp, Sensor2.avg_humidity, Sensor2.avg_pm25 = Sensor2.avg_all_data()
        
        print(Sensor2.avg_temp, Sensor2.avg_humidity, Sensor2.avg_pm25)
        if Sensor2.avg_temp > 25.0 and Sensor2.avg_humidity < 50 and Sensor2.avg_pm25 > 30:
            print(f"Warning Potential Fire at Node:{node_id}")
        
        # Storing everything in CSV file
        writer.writerow([timestamp, node_id, temperature, humidity, air_quality_pm25])
        f.flush() # Sending data from RAM to Disk for permamenet sotrage
    