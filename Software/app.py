#!./env/bin/python
# The Above She-Bang ensures we are using the virtualenv

import records
import flask
from flask import Flask, render_template, url_for
import json

# Create our Flask (web app) instance
app = Flask(__name__)
# Force reload and no caching
app.config['SEND_FILE_MAX_AGE_DEFAULT'] = 0

# Decorator syntax to set / to index.html (Home / Main Page)
@app.route("/")
def index():
	records.refresh()
	return render_template('index.html', data=records.Records)

@app.route("/add/record", methods=['POST'])
def add_record(record=None):
	# record (or request) is a list of form RMS Voltage, Pk Current, Power, Energy
	if record:
		record_fmt = records.format(record[2], record[0], record[1], record[3])
	else:
		data = flask.request.get_json()
		record_fmt = records.format(data[2], data[0], data[1], data[3])
	
	records.add_record(record_fmt)
	return flask.Response(status=200)

@app.route("/add/records", methods=['POST'])
def add_records():
	data = flask.request.get_json()
	for d in data:
		add_record(d)
	records.refresh()
	return flask.Response(status=200) 

@app.route("/delete/records", methods=['POST'])
def delete_records():
	records.wipe()
	records.refresh()
	return flask.Response(status=200)


# Return the Json data for rms_voltage, pk_current, power or energy
# value must be one of the types accepted by records.get_all_values()
@app.route("/get/json/<string:value>", methods=['POST'])
def get_json(value):
	return json.dumps(records.get_all_values(flask.escape(value)))

# Return the Json data for rms_voltage, pk_current, power or energy
# value must be one of the types accepted by records.get_all_values()
@app.route("/record.txt", methods=['GET'])
def get_record_file():
	file = open(records.db.filepath, "r")
	content = file.read()
	file.close()
	return '<span style="white-space: pre-line">' + content + '</span>';

