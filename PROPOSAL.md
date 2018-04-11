# 
# Project Proposal: A Simulation and Visualization of The N-Body Problem
## Background and Motivation
The n-body problem is a generalization of the famous but unsolvable three body problem in physics. The problem statement is as follows:
> Given a set of `n` bodies with fixed masses, initial positions and initial velocities that iteract gravitationally, describe the motion of these objects at any given future time.

The two-body version of this problem can be solved easily, but there is no general, closed-form solution for `n > 2`.The true motions of these bodies, however, can be accurately approximated through the use of computer simulations. N-body simulations, therefore, are critical in allowing cosmologists and astrophysicists to model and predict the motion of complex celestial systems.

## Goals
The goal of this project is to create an application that can model and visulaize the motions of an arbitrary n-body problem under a certain set of physical laws. The application will allow the user to set the following initial conditions:
* Number of bodies (`n`)
* Mass of each body
* Initial position of each body in 3D space
* Initial velocity of each body
* Laws governing the motion of the bodies:
    * Gravitational constant (`G`)
    * Newton's inverse square law
    * Kepler's laws of planetary motion

From these initial conditions the application will generate a 3D visualization, with spheres representing the various bodies. The relative distance between and masses of the bodies will be indicated by the relative sizes of the spheres. During the simulation, the user will have the ability to pause and step through the frames of the simulation. They will also be able to adjust the point of view of the simulation.

_**Note**: the application will calculate movements predicted by classical mechanics, and will not consider the relativistic effects of large masses._

## Libraries
This project will make use of the following libraries:
1. [ofMath](http://openframeworks.cc/documentation/math/) - this library will be used to perform the physical calculations at each frame of the simulation. This will inform the visualization by describing the motions and the positions of the bodies.
1. [of3d](http://openframeworks.cc/documentation/3d/) - this library will be used to visualize the simulation by generating,  moving and resizing spheres to represent the bodies, their motion and their relative positions.
1. [OpenGL](http://openframeworks.cc/documentation/gl/) - this library will be used at a later stage for more advanced graphics such as adding textures to the bodies and rendering a more dynamic background.
1. [ofxGui](http://openframeworks.cc/documentation/ofxGui/) - this library will be used to take user input regarding the initial states of the simulation in a user friendly way. It will also be used during the simulation to pause and step through the frames and to manipulate the point of view in the simulation.
1. [ofxGui](http://openframeworks.cc/documentation/ofxXmlSettings/) - this library will be used to save and load user input in a more efficient way. It will also be used to store the state of a certain simulation for reloading.

