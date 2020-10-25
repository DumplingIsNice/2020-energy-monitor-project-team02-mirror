#!./env/bin/python
# The Above She-Bang ensures we are using the virtualenv

# This file deals with the actual values for Power, Current etc.

import db

Timestep = 1 # the number of seconds between each record in the list
Records = db.load_records()

def refresh():
	Records = db.load_records()

# Returns a list of all the vlaues of a certain quantity
#	quantity can be one of:
#		- power
#		- rms_voltage
#		- pk_current
#		- energy
def get_all_values(quantity):
	result = []
	for record in Records:
		result.append(record[quantity])
	return result

# take a string or float for each of the values and return a record dictionary out of it
def format(power, rms_voltage, pk_current, energy):
	return {'power': float(power), 'rms_voltage': float(rms_voltage), 'pk_current': pk_current, 'energy': energy}

# Delete all records (including stored database!)
def wipe():
	db.wipe_records()
	refresh()

