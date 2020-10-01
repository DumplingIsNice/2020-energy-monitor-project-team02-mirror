<img src="https://github.com/ee209-2020class/ee209-2020class.github.io/blob/master/ExtraInfo/logo.png">

# Software for Smart Energy Monitor

## General Info:

- Web server built using Python as backend
- Using Flask for web framework
- Using Gunicorn for web server
- Using Heroku as Hosting Server
	- Heroku account is registered under Ankush

## Development Info:

- Flask expects all HTML to be stored in the `templates` directory
- Flask expects all Javascript and CSS to be stored in the `static` directory
- Flask uses `JinJa2` for templating HTML 
- To run Debug Test Server run `FLASK_ENV=development python -m flask run` in this directory

## Description of database files

- The format is plain text
- The file extention is `.db`
- Columns are seperated by a single tab '\t'
- Rows are seperated by a single newline '\n'
- The first line of the file contains the names of each column
    - It may be useful to imagine the database as structured like a table
