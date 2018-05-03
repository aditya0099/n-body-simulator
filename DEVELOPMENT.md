# Weekly Progress Reports
## Week 1
### Summary
This week, I started by doing some preliminary research into n-body simulations. I found that, depending on the number of bodies, there are various different techniques that can be used. I decided to attempt to implement two algorithms and began working on the simpler of the two that works for few-body problems.

To do this, I came up with a class structure and then implemented a physics engine that could approximate the movement of objects in discrete time intervals.

### Challenges
* Creating the open frameworks project: this caused issues with git as I was unsure of which files to push to my repository.
* Creating test cases: I was not able to compile my test for the OF application. This is something I aim to get working by the next code review.

## Week 2
### Summary
This week, I did the bulk of the coding for the project. First, I fixed the bugs in the physics engine. After that, I begin working on the graphics portion of the project.

The graphics portion of the project can be split into two parts. First was the GUI, which I designed using the ofxGui addon. Second was the actual rendering of the body spheres, which I did using of3d and OpenGL.

This week, I also decided to slightly alter my project. I realized that more complex algorithms for N-body simulations are only needed of the number of bodies is between 500,000 and 1,000,000. Given the way the user interacts with my simulation, it is unlikely that there will be more than 5-10 bodies in the simulation at a time. For this reason, I have decided not to implement two different physics engines at this time. However, I have left my class structure as it was last week, which gives anyone using my code the freedom to add a physics engine at a later date.

Instead of implementing two different physics engines, I have decided to add a system that can handle collisions between the bodies.

### Challenges
* Trying to understand the various parts of open frameworks because of a lack of documentation:
    * Understanding how the ofxGui works
    * Understanding how to us the of3dPrimitives
    * Figuring out how the ofEasyCamera works
* Structuring and logically splitting the code between the update and draw loops.
* Floating point underflow because ofVector uses floats and my code used doubles

## Week 3
### Summary
This week I accomplished two main goals of the project. The first was a collision handling system and the second was interaction with an XML file.

For the collision handling system, I found and implemented the vector equations for perfectly elastic and perfectly inelastic collisions. To do this, I had to give the bodies a defined size, which I based off of the mass of the body. I set a constant density and scaled the radii of the masses by this constant mass density.

For the XML portion, I implemented a system which automatically saved the initial state of the simulation to an XML file during the setup phase. If the simulation is run and then quit, it will revert to this initial state. Furthermore, if the application is closed and reopened, it will reload the previous state. Finally, the XML file can be manually edited before startup and these changes will reflect after startup.

### Challenges
* Learning the equations for elastic collisions in 3 dimensions:
    * I realized that three dimensional collisions can be treated like two dimensional collisions.
    * This is because the collisions take place on the plane of the two velocity vectors.
* Understanding ofxXmlSettings:
    * I quickly realized that this library cannot  be used to open an arbitrarily located XML file. Instead, the file had to be located in /bin/data.
    * I also had trouble understanding how to enter and exit nodes of the XML file. I eventually understood that this was done in a stack-like manner.
