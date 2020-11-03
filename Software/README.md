<img src="https://github.com/ee209-2020class/ee209-2020class.github.io/blob/master/ExtraInfo/logo.png">

# Software for Smart Energy Monitor

## General Info:

- Web server built using Python as backend
- Using Flask for web framework
- Using Gunicorn for web server
- [Web address for Smart Energy Software is](https://ee209t02.herokuapp.com/)
- To log data onto the smart energy tool, run the `./dataloggin.py` Python script.

- run `python3 -m pip3 install -r requirements.txt` to download and install all Python dependencies needed to run the software


## Development Info:

- Flask expects all HTML to be stored in the `templates` directory
- Flask expects all Javascript and CSS to be stored in the `static` directory
- Flask uses `JinJa2` for templating HTML 
- To run Debug Test Server run `FLASK_ENV=development python -m flask run` in this directory
- Using Heroku as Hosting Server
	- Heroku account is registered under Ankush
- `app.py` contains the main flask web app
- `db.py` is a Python module to impliment a very simple text based database for storing the voltages and currents etc.
- `records.py` is an interface from the text based database to an internal representation of the voltage, current, power and energy data for use by the flask web app `app.py`