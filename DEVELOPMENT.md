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

The graphics portion of the project can be split into two parts. First was teh GUI, which I designed using the ofxGui addon. Second was the actual rendering of the body spheres, which I did using of3d and OpenGL.

This week, I also decided to slightly alter my project. I realized that more complex algorithms for N-body simulations are only needed of the number of bodies is between 500,000 and 1,000,000. Given the way the user interacts with my simulation, it is unlikely that there will be more than 5-10 bodies in the simulation at a time. For this reason, I have decided not to implement two different physics engines at this time. However, I have left my class structure as it was last week, which gives anyone using my code the freedom to add a physics engine at a later date.

Instead of implementing two different physics engines, I have decided to add a system that can handle collisions between the bodies.

### Challenges
* Trying to understand the various parts of open frameworks because of a lack of documentation:
    * Understanding how the ofxGui works
    * Understanding how to us the of3dPrimitives
    * Figuring out how the ofEasyCamera works
* Structuring and logically splitting the code between the update and draw loops.
* Floating point underflow because ofVector uses floats and my code used doubles