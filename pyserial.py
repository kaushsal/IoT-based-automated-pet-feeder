import serial

from datetime import datetime

# Open serial connection with Arduino
ser = serial.Serial('COM5', 9600)  # Change '/dev/ttyUSB0' to the appropriate serial port

try:
    while True:
        # Read data from serial
        data = ser.readline().decode().strip()  # Decode bytes to string and remove trailing newline
        c=datetime.now()
        # Print received data
        print("Feeding time : ", c)

except KeyboardInterrupt:
    # Close serial connection on keyboard interrupt
    ser.close()
    print("Serial connection closed.")
