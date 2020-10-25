#!./env/bin/python
# The Above She-Bang ensures we are using the virtualenv

# This file uploads the data to the server from Bluetooth / UART / other sources

import os
import signal
import requests # For talking to the webserver
import serial # For uart


run_input_loop = True
# URL to upload data to
#	http://127.0.0.1:5000/add/records (for testing)
#	https://ee209t02.herokuapp.com/add/records
request_url = "http://127.0.0.1:5000/add/records"

def sigint_handle():
	global run_input_loop
	run_input_loop = False

def run():
	if os.name == "posix":
		port_name = input("Enter device to open (e.g. /dev/ttyUSB0): ")
	elif os.name == "nt":
		port_name = input("Enter device to open (e.g. 'COM0'): ")
	else:
		port_name = input("Enter device to open: ")

	try:
		# Open named port at ?9600 baud,8N1?, one second timeout:
		port = serial.Serial(port_name, 9600, timeout=1)
	except:
		print("Failed to open port " + port_name)
		exit()

	data = []
	print("Capturing Data from UART... Press CTRL + C To stop capture")

	signal.signal(signal.SIGINT, sigint_handle)
	while run_input_loop:
		# This is the expected output order of uart
		voltage = None
		current = None
		power = None
		energy = None

		try:
			line = port.readline().strip()
		except serial.SerialTimeoutException:
			print("Reading Line From UART Timed Out. Trying Again...")
			continue

		if "V(RMS)" in line:
			voltage = float(line.split(' ')[0])
		elif "A(PK)" in line:
			current = float(line.split(' ')[0])
		elif "W" in line:
			power = float(line.split(' ')[0])
		elif "J" in line:
			energy = float(line.split(' ')[0])
		else:
			print("Error found unknown line in UART: " + line)

		if not voltage or not current or not power or not energy:
			print("Error failed to get voltage, current, power or energy")
			print("\tPicked Up: V: " + str(voltage) + " I: " + str(current) + "P: " + str(power) + "E: " + str(energy))
		else:
			data.append([voltage, current, power, energy])

		print("Finished Collecting Data - Uploading Now ... ")

		post_data = {}
		for i in range(0, len(data)):
			post_data[i] = data[i]
		requests.post(request_url, data)

		print("Data Upload Complete")
		port.close()

if __name__ == "__main__":
	run()


