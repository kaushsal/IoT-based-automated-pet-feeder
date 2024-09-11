import gspread
from oauth2client.service_account import ServiceAccountCredentials

# Define the scope and credentials
scope = ['https://spreadsheets.google.com/feeds', 'https://www.googleapis.com/auth/drive']
credentials = ServiceAccountCredentials.from_json_keyfile_name('petfeederkey.json', scope)

# Authorize the client
client = gspread.authorize(credentials)

# Open the Google Sheet by its title
sheet = client.open('petfeeder').sheet1


import serial

from datetime import datetime

# Open serial connection with Arduino
ser = serial.Serial('COM5', 9600)  # Change '/dev/ttyUSB0' to the appropriate serial port

try:
    while True:
        # Read data from serial
        data = ser.readline().decode().strip()  # Decode bytes to string and remove trailing newline
        c=datetime.now()
        c=str(c)
        d,t=c.split()
        # Print received data
        print("Feeding time : ", c)
        sheet.append_row([d,t])

except KeyboardInterrupt:
    # Close serial connection on keyboard interrupt
    ser.close()
    print("Serial connection closed.")
