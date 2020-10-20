voltage_range = 12.6:0.1:15.4; % Rms Voltage
frequency_range = [49 50 51];

load_steps = 2; % Go up in steps of 2 Ohms 
min_load = 1;
max_load = 105;

load_range = min_load:load_steps:max_load;

inductance = 40e-3; % L is fixed at 40 mH

S_max = 7.5;
S_min = 2.5;

for f = frequency_range
	for v = voltage_range
		for r = load_range
			Z = (j * 2 * pi * f * inductance) + r;
			S = v^2 / Z;
			if (abs(S) >= S_min && abs(S) <= S_max)
				disp([num2str(v) 'Vrms @ ' num2str(f) 'Hz, R_L = ' num2str(r) ' (|S| = ' num2str(abs(S)) ')']);
			end
		end
	end
end

