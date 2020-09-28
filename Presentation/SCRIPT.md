# Presentation Notes

# Slide 0: Introduction (10-12s)

- It is an honor to have you at our presentation. My name is _____, and I'm here with ____ ____ and _____, and we will walk you through the highlights of our design.
- You may have known this, but to reiterate: in our design course we are developing a home energy monitor that could measure the voltage and current across a load. The signals will be read by a microcontroller which will calculate the original signal and the power consumed by it.
- We hope to learn good firmware and hardware developing practices, workflow management, and practical knowledge to help us in the wider industry.

# Slide 1: Analog (1) (50-60s)

- We designed the signal processing circuit in such a way that we maximized the gain of our captured signals. 
- We found the opportunity to optimize this in order to increase the voltage levels captured by the microcontroller. So that the ADC conversion of the signal will be more representative over the 5V reference.
- The maximum range of input voltages of our LM324 OpAmps before saturation is (VOH and VOL) 0.7V <--> 3.3V.
- In our first implementation, the maximum peak to peak of the signal is between 1.3V <--> 2.9V. We believe we could optimise this.
- Our optimization allowed us to reach much closer to the range of the op amp as input to the ADC. The maximum peak to peak of the signal is now 0.9V <--> 3.3V
- This will increase the accuracy of the captured signal.

# Slide 2: Analog (2)

- We had developed a peak detector that triggers on waveform peaks. The signal from this circuit will help us identify peaks perform power calculations in our microcontroller. This arises from the limitation of sampling and the quantified representation of the signal. 

# Slide 3: Digital (1)

- We developed modular code, each dictating the functions for a peripheral of the microcontroller.

# Slide 4: Digital (2)

- To highlight, we chose to implement a custom print function for the purpose of transmitting data over UART. 

# Slide 5: Digital (3) (1:30-1:40)

Also support driving the LED display using the library.

- We decided that the printf() function is an unnecessary intensive and costly function for the purpose of our project. There are many functions of printf() we do not use such as hexadecimal comparability. This is why we implemented a custom print function.
- This reduced print() function also saves valuable memory for the processing our signal data. Using only up to 280 bytes, this function reduces the size of transmitted data by about 70%.
- The use of modular, intuitive function implementations are helpful in collaborating with others for our project and allows for understanding of our firmware.
  
# Slide 6: PCB (1)

Add some arrows/lines pointing to highlights.

- Polarized electrolyte capacitors were chosen to be used for the generation of the common 5V DC power supply. 
- Meanwhile ceramic capacitors were used for the many signal conditioning circuits in AC applications.
- The PCB follows a recommended design, but in particular we added a extra current sinking resistor at the output of the regulation circuit for the ensured operation of the regulator package.

# Slide 7: Project management 

- We used gitHub for documentation, version control (rollbacks) and remote collaboration. This is especially necessary over lock-down. 
- Using python to read the makefile to generate project file.
- Slack and Zoom were used for virtual meetings and communication over the lock-down period.
- We used Trello for workflow planning, especially important for collaborations and task delegation.
- We also chose to do Smart Energy Challenge.
- Our initial plan is to local host a python programme to receive information from our energy monitor through its Bluetooth module.

# Slide 8: End

- On behalf of my team and I, we thank you for your time in reviewing our design with us. Any questions?

# Archive
- Ordinarily we would have to transmit each character separately and call multiple functions for transmitting numbers. The custom print function combines our modular transmit and calculation functions to achieve seamless, clean looking snippets of code to transmit anything from the microcontroller.

# Slide 7: Breadboard Prototype (20-30s) [Removed]

- We have developed a breadboard prototype of our analogue circuitry and is looking forward to testing it in reality when the laboratory space opens up.                                          

