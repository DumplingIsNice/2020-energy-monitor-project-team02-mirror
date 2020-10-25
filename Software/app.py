#!./env/bin/python
# The Above She-Bang ensures we are using the virtualenv

import records
from flask import Flask, render_template, url_for

# Create our Flask (web app) instance
app = Flask(__name__)


# Decorator syntax to set / to index.html (Home / Main Page)
@app.route("/")
def index():
	return render_template('index.html')

@app.route("/add/record", methods=['POST'])
def add_record():
	pass

@app.route("/add/records", methods=['POST'])
def add_records():
	pass

@app.route("/delete/records", methods=['POST'])
def delete_records():
	pass

