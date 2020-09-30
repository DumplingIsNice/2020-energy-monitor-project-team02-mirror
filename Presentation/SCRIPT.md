# Presentation Notes

# Slide 0: Title
Hao

- It is an honor to have you at our presentation. My name is _____, and I'm here with ____ ____ and _____, and we will walk you through the highlights of our design project.

# Slide 1: Introduction

- You may have known this already, but to reiterate: in our design course we are developing a home energy monitor that could measure the voltage and current across a provided load. Then, through a microcontroller, the system will process the signal and calculate the the power consumed by the load. Where the information shall be communicated through a 7-segment display on the board and a mobile application using bluetooth.
- From this experience we hope to learn good firmware and hardware developing practices, workflow management, and practical knowledge to help us in the wider industry.

# Slide 2: Analog (1) (1m 55s)
Hao

- For our hardware:
- We have designed the signal processing circuitry in such a way that we maximized the gain of our captured signals. 
- In particular we found the opportunity to optimize the resistors in the differential amplifier circuitry to increase the range of voltage levels captured. This is so that the ADC conversion of the signal downstream will be more representative over the 5V reference.
- We know that the maximum range of input voltages of our LM324 OpAmps before its saturation is (VOH and VOL) 0.7V <--> 3.3V.
- With that limitation in mind, in our first implementation, the maximum peak to peak of the signal is between 1.3V <--> 2.9V. We believe we could optimise this.
- Our optimization allowed the maximum peak to peak of the signal to reach 0.9V <--> 3.3V. 
- This is much closer to the tolerance of the OpAmp's capabilities. When fed into the ADC this will increase the accuracy of the digitized signal.

# Slide 3: Analog (2) (2m 15s)
Hao

- Additionally, to aid in the power calculation in the microcontroller, we have developed a peak detector that samples a voltage when an interrupt is triggered. 
- The signal from this circuit will help us identify signal peaks and perform power calculations. 
- These considerations must be made due to the limitation of the quantification process. The quantified representation of the signal is discrete and requires interpolation by the programme we developed to run on the microcontroller. 
- Of which we'll let _Krithik_ will walk you through the firmware of our energy monitor system.

# Slide 4: Digital (1)
Krithik

- For our firmware, we developed modular code, each dictating the functions for a peripheral of the microcontroller.

# Slide 5: Digital (2)
Krithik

- To highlight, we chose to implement a custom print function for the purpose of transmitting data over UART. 

# Slide 6: Digital (3) (3m 20)
Krithik

- We decided that the printf() function is an unnecessarily intensive and costly function for the purpose of our project. There are many functions of printf() we do not use such as hexadecimal comparability. This is why we implemented a custom print function.
- This reduced print() function also saves valuable memory for the processing of our signal data. Using only up to 244 bytes, this function reduces the size of transmitted data by over 70%.
- The use of modular, intuitive function implementations are helpful in collaborating with others for our project and allows for understanding of our firmware.
- Our function was also modified to round and transmit to 3 significant figures.
  
# Slide 7: PCB (1) (3m 57s)
Hao

- We designed our PCB implementation of the hardware in Altium. The PCB layout follows a recommended design for use to learn about good practices such as ensuring that commonly used nodes like Ground and the 5V source has a large pathway as shown by the pours.
- Bluetooth module with a divider that makes sure the transmitted signal from the microcontroller is compatible with the bluetooth module's input specifications.
- 5V power supply with the regulation package, all connected on the second layer below. The offset voltage are derived from here. A LED to indicate power.
- Sensor for the load voltages using a divider and current through a shunt resistor. Zenor diodes used for over voltage protection to ensure that the captured voltages will not be higher than expected. 
- Differential amplifiers used to offset and provide gain to the captured voltages. Before feeding to the microcontroller, a first order RC filter removes high frequency noise.
- Now the concludes he technical part of our project. But we'd like to mention it was challenging this year in how we as a team managed to collaborate together. Of which we'll let _Krithik_ will walk you through how we worked on the project together.


- The PCB layout follows a recommended design, but in particular we added a extra current sinking resistor at the output of the regulation circuit for the ensured operation of the regulator package.

# Slide 8: Trello/Slack management 
Krithik

- Slack and Zoom were used for virtual meetings and communication over the lock-down period.
- We used Trello for workflow planning and was especially important for collaborations and task delegations.

# Slide 9: Project management 

- We used gitHub for documentation, version control by using rollbacks and remote collaboration. This is especially necessary over lock-down. 
- To generate the project file for Atmel Studio, we used Python to read the makefile.
- We also chose to do the Smart Energy Challenge.
- Our initial plan for the challenge is to local host a python programme to receive information from our energy monitor through Bluetooth.

# Slide 10: End (4m 43s)
Krithik

- On behalf of my team and I, we thank you for your time in reviewing our design with us. Any questions?




# Archive
- Ordinarily we would have to transmit each character separately and call multiple functions for transmitting numbers. The custom print function combines our modular transmit and calculation functions to achieve seamless, clean looking snippets of code to transmit anything from the microcontroller.

# Slide 7: Breadboard Prototype (20-30s) [Removed]

- We have developed a breadboard prototype of our analogue circuitry and is looking forward to testing it in reality when the laboratory space opens up.                                          

