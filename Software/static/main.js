function draw_rms_voltage_graph()
{
	/* Send a POST request and grab the data first */
	var json_data;
	const request_url = "/get/json/rms_voltage";
	var request = new XMLHttpRequest();

	/* Response Handler */
	request.onreadystatechange = function () {
		if (this.readyState == 4 && this.status == 200) {
			json_data = JSON.parse(this.response);

			/* Now draw the chart using chart.js library */
			var canvas = document.getElementById('rms_voltage_graph');
			var chart = new Chart(canvas, {
				type: 'line',
				data: {
					labels: Array.from(Array(json_data.length).keys()),
					datasets: [{
						data: json_data,
						label: "RMS Voltage"
					}]
				},
				options: {
				}
			});
		}
	}

	/* Make the request */
	request.open("POST", request_url, true);
	request.send();
}

function draw_pk_current_graph()
{
	/* Send a POST request and grab the data first */
	var json_data;
	const request_url = "/get/json/pk_current";
	var request = new XMLHttpRequest();

	/* Response Handler */
	request.onreadystatechange = function () {
		if (this.readyState == 4 && this.status == 200) {
			json_data = this.response;
		}
	}

	/* Make the request */
	request.open("POST", request_url, true);
	request.send();
}

function draw_power_graph()
{
	/* Send a POST request and grab the data first */
	var json_data;
	const request_url = "/get/json/power";
	var request = new XMLHttpRequest();

	/* Response Handler */
	request.onreadystatechange = function () {
		if (this.readyState == 4 && this.status == 200) {
			json_data = this.response;
		}
	}

	/* Make the request */
	request.open("POST", request_url, true);
	request.send();
}

function draw_energy_graph()
{
	/* Send a POST request and grab the data first */
	var json_data;
	const request_url = "/get/json/energy";
	var request = new XMLHttpRequest();

	/* Response Handler */
	request.onreadystatechange = function () {
		if (this.readyState == 4 && this.status == 200) {
			json_data = this.response;
		}
	}

	/* Make the request */
	request.open("POST", request_url, true);
	request.send();
}

function main()
{
	draw_rms_voltage_graph();
	draw_pk_current_graph();
	draw_power_graph();
	draw_energy_graph();
}
