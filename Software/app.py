#!./env/bin/python
# The Above She-Bang ensures we are using the virtualenv

import db
from flask import Flask, render_template, url_for

# Create our Flask (web app) instance
app = Flask(__name__)


# Decorator syntax to set / to index.html (Home / Main Page)
@app.route("/")
def index():
	return render_template('index.html')
