import serial
import pyttsx3
engine = pyttsx3.init()
serial_port = 'COM4' 
# baud rate of HC-05 is configured to be 9600
baud_rate = 9600 
ser = serial.Serial(serial_port, baud_rate, timeout=1)
print("Listening for incoming data...")
try:
    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()
            if data:
                print(f"Received: {data}")
                engine.say(data)
                engine.runAndWait()
except KeyboardInterrupt:
    print("Program terminated by user.")
finally:
    ser.close()
    print("Serial port closed.")