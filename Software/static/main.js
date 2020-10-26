var v_chart = null;
var i_chart = null;
var p_chart = null;
var e_chart = null;

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
			if (v_canvas != null) {
				v_chart.destroy();
				v_chart = null;
			}
			var v_canvas = document.getElementById('rms_voltage_graph');
			v_chart = new Chart(v_canvas, {
				type: 'line',
				data: {
					labels: Array.from(Array(json_data.length).keys()),
					datasets: [{
						data: json_data,
						fill: true,
						backgroundColor: 'rgba(0, 110, 199, 0.2)',
						borderColor: "#006ec7"
					}]
				},
				options: {
					title: {
						display: true,
						text: 'RMS Voltage Vs. Time',
						fontColor: "#006ec7"
					},
			 		scales: {
						yAxes: [{
							ticks: {
								min: 0,
								max: Math.ceil(Math.max(...json_data)),
							},
							scaleLabel: {
								display: true,
								labelString: 'Voltage (Vrms)',
								fontColor: "#006ec7"
							},
							gridLines: {
								color: 'rgba(247, 25, 233, 0.4)'
							}
					    	}],
						xAxes: [{
								scaleLabel: {
									display: true,
									labelString: 'Time (s)',
									fontColor: "#006ec7"
								},
							gridLines: {
								color: 'rgba(247, 25, 233, 0.4)'
							}
						    }]
					},
					legend: {
						display: false
					},
					tooltips: {
						enabled: true,
						callbacks: {
							label: function(tooltipItem, data) {
								return tooltipItem.yLabel + ' Vrms';
							}
						}
					}
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
			json_data = JSON.parse(this.response);
			/* Now draw the chart using chart.js library */
			if (i_chart != null) {
				i_chart.destroy();
				i_chart = null;
			}
			var i_canvas = document.getElementById('pk_current_graph');
			i_chart = new Chart(i_canvas, {
				type: 'line',
				data: {
					labels: Array.from(Array(json_data.length).keys()),
					datasets: [{
						data: json_data,
						fill: true,
						backgroundColor: 'rgba(115, 0, 255, 0.2)',
						borderColor: "#7300ff"
					}]
				},
				options: {
					title: {
						display: true,
						text: 'Peak Current Vs. Time',
						fontColor: "#7300ff"
					},
			 		scales: {
						yAxes: [{
							ticks: {
								min: 0,
								max: Math.ceil(Math.max(...json_data)),
							},
							scaleLabel: {
								display: true,
								labelString: 'Peak (A)',
								fontColor: "#7300ff"
							},
							gridLines: {
								color: 'rgba(247, 25, 233, 0.4)'
							}
					    	}],
						xAxes: [{
								scaleLabel: {
									display: true,
									labelString: 'Time (s)',
									fontColor: "#7300ff"
								},
							gridLines: {
								color: 'rgba(247, 25, 233, 0.4)'
							}
						    }],
					},
					legend: {
						display: false
					},
					tooltips: {
						enabled: true,
						callbacks: {
							label: function(tooltipItem, data) {
								return tooltipItem.yLabel + ' Apk';
							}
						}
					}
				}
			});
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
			json_data = JSON.parse(this.response);
			/* Now draw the chart using chart.js library */
			if (p_chart != null) {
				p_chart.destroy();
				p_chart = null;
			}
			var p_canvas = document.getElementById('power_graph');
			p_chart = new Chart(p_canvas, {
				type: 'line',
				data: {
					labels: Array.from(Array(json_data.length).keys()),
					datasets: [{
						data: json_data,
						fill: true,
						backgroundColor: 'rgba(214, 0, 0, 0.2)',
						borderColor: "#d60000"
					}]
				},
				options: {
					title: {
						display: true,
						text: 'Power Vs. Time',
						fontColor: "#d60000"
					},
			 		scales: {
						yAxes: [{
							ticks: {
								min: 0,
								max: Math.ceil(Math.max(...json_data)),
							},
							scaleLabel: {
								display: true,
								labelString: 'Power (W)',
								fontColor: "#d60000"
							},
							gridLines: {
								color: 'rgba(247, 25, 233, 0.4)'
							}
					    	}],
						xAxes: [{
								scaleLabel: {
									display: true,
									labelString: 'Time (s)',
									fontColor: "#d60000"
								},
							gridLines: {
								color: 'rgba(247, 25, 233, 0.4)'
							}
						    }]
					},
					legend: {
						display: false
					},
					tooltips: {
						enabled: true,
						callbacks: {
							label: function(tooltipItem, data) {
								return tooltipItem.yLabel + ' W';
							}
						}
					}
				}
			});
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
			json_data = JSON.parse(this.response);
			/* Now draw the chart using chart.js library */
			if (e_chart != null) {
				e_chart.destroy();
				e_chart = null;
			}
			var e_canvas = document.getElementById('energy_graph');
			e_chart = new Chart(e_canvas, {
				type: 'line',
				data: {
					labels: Array.from(Array(json_data.length).keys()),
					datasets: [{
						data: json_data,
						fill: true,
						backgroundColor: 'rgba(0, 238, 255, 0.2)',
						borderColor: "#00eeff"
					}]
				},
				options: {
					title: {
						display: true,
						text: 'Energy Vs. Time',
						fontColor: "#00eeff"
					},
			 		scales: {
						yAxes: [{
							ticks: {
								min: 0,
								max: Math.ceil(Math.max(...json_data)),
							},
							scaleLabel: {
								display: true,
								labelString: 'Energy (Wmin)',
								fontColor: "#00eeff"
							},
							gridLines: {
								color: 'rgba(247, 25, 233, 0.4)'
							}
					    	}],
						xAxes: [{
								scaleLabel: {
									display: true,
									labelString: 'Time (s)',
									fontColor: "#00eeff"
								},
							gridLines: {
								color: 'rgba(247, 25, 233, 0.4)'
							}
						    }]
					},
					legend: {
						display: false
					},
					tooltips: {
						enabled: true,
						callbacks: {
							label: function(tooltipItem, data) {
								return tooltipItem.yLabel + ' Wmin';
							}
						}
					}
				}
			});
		}
	}

	/* Make the request */
	request.open("POST", request_url, true);
	request.send();
}

function wipe_data()
{
	request = new XMLHttpRequest();
	request.onreadystatechange = function () {
		if (this.readyState == 4 && this.status == 200) {
			main();
		}
	}
	request.open('POST', '/delete/records')
	request.send();
}

function main()
{
	draw_rms_voltage_graph();
	draw_pk_current_graph();
	draw_power_graph();
	draw_energy_graph();
}
