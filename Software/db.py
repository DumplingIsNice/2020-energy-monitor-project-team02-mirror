#!./env/bin/python
# The Above She-Bang ensures we are using the virtualenv

## This module is going to impliment a sort of database to store and laod values
##	for the Voltage, Current, Power etc. that we get from the microcontroller

### The database format is described below
# Records are stored in the following order, in the following format:
#
# power peak_current rms_voltage energy
#
# Each vlaue is space-deliminated
# Each line represents the next point in time, a time

import os


filepath = "record.txt"

# Store a single record
# (dictionary with 'power' 'pk_current' 'rms_voltage' and 'energy' keys)
def store_record(record):
	file = open(filepath, "a")
	write_string = str(record['power']) + ' ' + str(record['pk_current']) + ' ' + str(record['rms_voltage']) + ' ' + str(record['energy'])
	file.write(write_string + '\n')
	file.close()

# Store a list of records
# (list of dictionaries with each dictionary having 'power' 'pk_current' 'rms_voltage' and 'energy' keys)
def store_records(records):
	file = open(filepath, "a")
	for record in records:
		write_string = str(record['power']) + ' ' + str(record['pk_current']) + ' ' + str(record['rms_voltage']) + ' ' + str(record['energy'])
		file.write(write_string + '\n')
	file.close()

# reutrns a list of dictionaries with the keys 'power' 'pk_current' 'rms_voltage' and 'energy'
def load_records():
	records = [{}]
	file = open(filepath, "r")
	for line in file:
		tokenised = line.split(' ')
		records.append({'power': float(tokenised[0]), 'pk_current': float(tokenised[1]), 'rms_voltage': float(tokenised[2]), 'energy': float(tokenised[3])})
	file.close()
	return records;

def wipe_records():
	file = open(filepath, "w")
	file.close()
