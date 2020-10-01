#!./env/bin/python
# The Above She-Bang ensures we are using the virtualenv

## This module is going to impliment a sort of database to store and laod values
##	for the Voltage, Current, Power etc. that we get from the microcontroller

### The database format is described in ./README.md

import os

class db:
	def __int__(self, filepath=None):
		# We have been given a file path, load the database in
		if filepath:
			# Stuff to do with the actual file
			self.load_database(filepath)
		else:
			self.filename = None
			self.filesize = None

		# Stuff to do with database elements
		# First row of database file, the actual data fields (i.e. Voltage, Current etc.)
		self.fields = []
		# Dictionary of form: {'field_name':[field_values]}
		self.fieldValues = {}

	def add_field(self, fieldName):
		pass;

	def remove_field(self, fieldName):
		pass;

	def add_value(self, fieldName):
		pass;

	def remove_value(self, fieldName):
		pass;

	# Load a database from a given filepath
	# File path can be with or without extention (i.e.: 'one.db' is the same as 'one')
	def load_database(self, filepath):
		pass # TODO: Impliment
