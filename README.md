# universal-testing-machine

## **Abstract**
### This projet at first was about Reverse-Engineering a Stress/Strain analysis machine, then fix it and Automate it's process.
### The following is an image of the machine 
![Machine](https://github.com/ENG-MohamedEssam/universal-testing-machine/blob/main/images/machine.jpeg)

### Every part of the machine was Reverse-Engineered from the boards to the hydraulics to the classic control.
### The following is an image of one of the Reverse-Engineered boards which was mine to Reverese-Engineer.
![Boards]()
### I reverse Engineered The MV3058

### Due to financial and permits issues the project was turned to be a prototype working with Embedded Systems.

### The following is an image of the Prototype
![prototype](https://github.com/ENG-MohamedEssam/universal-testing-machine/blob/main/images/prototype.jpg)

### The boards were desiged as follows, one board for the control, the second as a relay module. 

## **How the prototype works?**
 
### The prototype mainly does exactly what the original machine does but on a smaller scale.
### we mainly put a specimen between the two grippers and the machine puts tension or compression on the specimen till it breaks 
### then it draws the Stress/Strain curves of the specimen's material.
### It has a stepper motor used to adjust the place of the speciment, 
### a piston that's derived by a hydraulic pump, 
### a gripper used to grab the specimen.
### As far as the Embedded systems part is concerend the machine had mainly 2 sensors ,
### The Load Cell that's used to measure the Force and the Linear potentiometer that's used to measer the delta L.
### the prototype is based mainly on two equations, Stress equation and Strain equation.
### σ = F/A   ,    ε = δ/L  
### the only two variables in these equations are the Force and the change in the length 

### The following is images of the boards and panel.
![board](https://github.com/ENG-MohamedEssam/universal-testing-machine/blob/main/images/stm.png)
![relay](https://github.com/ENG-MohamedEssam/universal-testing-machine/blob/main/images/relay.png)
![panel](https://github.com/ENG-MohamedEssam/universal-testing-machine/blob/main/images/panel.jpeg)

### The follwing is Single Line Diagram that was made by me 
![SID](https://github.com/ENG-MohamedEssam/universal-testing-machine/blob/main/images/sid.png)

### The following link has some small SolidWorks parts that i've made for the machine whether it was as a specimen or for the sensors housings 
[parts]()

### The following link has an explanation of the Embedded systems part explained by me 
### [Explanation](https://drive.google.com/file/d/1bGaOVOjb-tQGSpPLI7ITkfYBf-VQDN8E/view)