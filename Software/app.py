#!./env/bin/python
# The Above She-Bang ensures we are using the virtualenv

import records
import flask
from flask import Flask, render_template, url_for

# Create our Flask (web app) instance
app = Flask(__name__)


# Decorator syntax to set / to index.html (Home / Main Page)
@app.route("/")
def index():
	records.refresh()
	print(records.Records)
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
	return flask.Response(status=200) 

@app.route("/delete/records", methods=['POST'])
def delete_records():
	pass

