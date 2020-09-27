# Presentation Notes

# Slide 0: Introduction

- We are developing a home energy monitor as a part of this design course.

# Slide 1: Analog (1)
- Designed the signal processing circuit in a way that the maximum gain was achieved in order to increase the voltage levels we could capture with the micro controller.
- More representative over the 5V reference.
- The maximum range of input voltages (VOH and VOL) the LM324 OpAmps may tolerate before saturation is 0.7V <--> 3.3V.
- Before: Peak to peak between 1.3V <--> 2.9V. We believe we could optimise this.
- After: Reached much closer to the range of the op amp as input to the ADC. The peak to peak range is now 0.9V <--> 3.3V

# Slide 1: Analog (2)

- 50% increase???

# Slide 3: Digital (1)

- We developed modular code, each dictating the functions are a peripheral of the microcontroller.

# Slide 4: Digital (2)

- We chose to implement a custom print function for the purpose of transmitting data over UART. 

# Slide 5: Digital (3)

- The custom print function combines our modular transmit and calculation functions to achieve seamless, clean looking snippets of code to transmit anything from the microcontroller.
- The use of simple, intuitive function implementations is helpful in our collaboration in the project for others to be updated on the development of the firmware.
- [How the hell is the custom print function uses less space?]
  
# Slide 6: PCB (1)

# Slide 7: Breadboard Prototype

- To meet the deadlines for this design project, the peak detector was unable to be added to the PCB layout before send off to manufacture due to technical issues.
- However, that did not stop us from developing and testing a peak detector on our bread board.

# Slide 8: End

- Thank you for your time in reviewing our design with us. Any questions.

