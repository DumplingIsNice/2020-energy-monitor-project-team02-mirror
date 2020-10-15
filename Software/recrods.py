#!./env/bin/python
# The Above She-Bang ensures we are using the virtualenv

# This file deals with the actual values for Power, Current etc.

import db

Timestep = 1 # the number of seconds between each record in the list
Records = db.load_records()

def refresh_records():
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
