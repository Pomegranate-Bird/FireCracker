import matplotlib.pyplot as plt
import numpy as np
import re

def plotData(data: list):

    # Convert lists into a numpy arrays
    data = np.array(data)
    hours = np.array(list(range(1,25))) # Creating a list of numbers 1-24 

    # Getting an average of the harvestable energy 
    averageDni = getAverage(data)
    plt.plot(hours, data)
    plt.xlabel("Hours")
    plt.ylabel("Solar Irradiance w/m^2")
    plt.title("Total Energy")
    plt.show()

def getData(path: str, year: int, month: int, day: int = None):

    # Read the file as a string
    with open(path, "r") as f:
        text = f.read()

    if day is None:
        # Pattern for extracting 2025 Janurary data 
                                # Year,Month,Day,Hour,Minute,Clearsky DNI
        pattern = f"{year},{month},([0-9]+),([0-9]+),([0-9]+),([0-9]+)"
        newPattern = re.compile(pattern) # Regex pattern
        data = re.findall(newPattern, text) # Returns a list of all matches 

        # Dni values list
        dniValues = []

        # Extracing data from the file
        for dni in data:
            dniValues.append(float(dni[-1]))
        return dniValues
    else:
        # Pattern for extracting 2025 Janurary data 
                                        # Year,Month,Day,Hour,Minute,Clearsky DNI
        pattern = f"{year},{month},{day},([0-9]+),([0-9]+),([0-9]+)"
        newPattern = re.compile(pattern) # Regex pattern
        data = re.findall(newPattern, text) # Returns a list of all matches 
        
        # Dni values list
        dniValues = []
        
        # Extracing data from the file
        for dni in data:
            dniValues.append(float(dni[-1]))
        return dniValues
   
def getAverage(data):

    # Convert list into a numpy array
    data = np.array(data)
    tSum = 0
    for vals in data:
        tSum += vals
    return tSum/len(data)

def main():
    path = "/home/marvin/Desktop/FireCracker/Python/data/oneyear.csv"
    # Getting data for August 8th 2025
    data = getData(path, 2025, 1, 1)
    print(data)
    plotData(data)
    

if __name__ == "__main__":
    main()
