# Presentation Notes

# Slide 0: Introduction (10-12s)

- A honor to have you at our presentation. My name is _____. And we will walk you through the highlights of our design.
- You may have known this, but to reiterate: in our design course we are developing a home energy monitor.

# Slide 1: Analog (1) (50-60s)
- We designed the signal processing circuit in such a way that we maximized the gain of our captured signals. 
- We found the opportunity to optimize this in order to increase the voltage levels captured by the microcontroller. So that the ADC conversion of the signal will be more representative over the 5V reference.
- The maximum range of input voltages of our LM324 OpAmps before saturation is (VOH and VOL) 0.7V <--> 3.3V.
- First implementation: The maximum peak to peak of the signal is between 1.3V <--> 2.9V. We believe we could optimise this.
- Optimized: Reached much closer to the range of the op amp as input to the ADC. The maximum peak to peak of the signal is now 0.9V <--> 3.3V

# Slide 1: Analog (2)

- We had developed a peak detector. This arises from the limitation of sampling and the quantified representation of the signal. The signal from this circuit will help us perform power calculations in our microcontroller.

# Slide 3: Digital (1)

- We developed modular code, each dictating the functions for a peripheral of the microcontroller.

# Slide 4: Digital (2)

- To highlight, we chose to implement a custom print function for the purpose of transmitting data over UART. 

# Slide 5: Digital (3) (1:30-1:40)

- We decided that the printf() function is a unnecessary intensive/costly function for the purpose of our project. There are many functions of printf() we do not use such as hexadecimal comparability. So, we implemented our own print function.
- This reduced print function also saves valuable memory for the processing of the signal data. Using up 280 bytes, about 70% reduction in size.
- The use of modular, intuitive function implementations is helpful in our collaboration in the project for others to be updated on the development of the firmware.
  
# Slide 6: PCB (1)

- Polarized electrolyte capacitors were chosen to be used for the generation of the common 5V DC power supply. 
- Meanwhile ceramic capacitors were used for the many signal conditioning circuits in AC applications.
- The PCB follows a recommended design, but in particular we added a extra current sinking resistor at the output of the regulation circuit for the ensured operation of the regulator package.

# Slide 7: Breadboard Prototype (20-30s)

- We have developed a breadboard prototype of our analogue circuitry and is looking forward to testing it in reality when the laboratory space opens up.

# Slide 8: End

- Thank you for your time in reviewing our design with us. Any questions.

# Archive
- Ordinarily we would have to transmit each character separately and call multiple functions for transmitting numbers. The custom print function combines our modular transmit and calculation functions to achieve seamless, clean looking snippets of code to transmit anything from the microcontroller.

