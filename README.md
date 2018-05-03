# N-Body Simulator

## Simulation Instructions
### The setup screen
To start, all you have to do is run the application. When the application is run the screen shown is called the setup screen. Here, you can add bodies to the simulation by manipulating the sliders on the top left. These sliders allow you to adjust the following:
* Initial position
* Initial velocity
* Initial mass
* Initial color
* Collision type

Once the desired initial conditions are set, press the `add` button or the `ENTER` key to add the body to the simulation. A sphere should appear on the screen. If you wish to remove the most recently added body, press the `remove` button or the `BACKSPACE` key.

When all the bodies are added, press the `run` button or the `r` key to start the simulation.

## Running and observing the simulation
Once the simulation is run, the bodies will begin to move at a steady rate under the influence of gravity.

The camera can be manipulated using the mouse. Click and drag with the left mouse button to rotate the camera about the origin. Click and drag with the right mouse button, or use a two finger scrolling gesture, to zoom in and out.

Note: if inelastic collisions are selected, the collision will result in two bodies combining to form a larger body. This will cause the new body to be larger and take on the average color between the two source bodies.   

## Pausing and stepping through the simulation
Press `pause` button, or the `p` key, to pause the simulation. Now, an additional set of controls will appear on the left that will allow you to step through frames of the simulation. Set the step amount using the slider and press the `step` button or the `s` key to step through the simulation frame by frame, or to skip ahead by multiple frames. Note that the camera will still function normally when the simulation is paused

Tip: hold down the l`s` with a large step amount to speed up the simulation.

At any time, press the `reset` button or `BACKSPACE` to return to the setup screen, or press `ESC` to quit the application.

## Loading settings from an XML file
To load settings from an XML file, navigate to the `bin/data` folder and open the file called `setup.xml`. Bodies are stored in the following format:
```
<body>
    <position>
        <x>0.000000000</x>
        <y>0.000000000</y>
        <z>0.000000000</z>
    </position>
    <velocity>
        <x>0.000000000</x>
        <y>0.000000000</y>
        <z>0.000000000</z>
    </velocity>
    <color>
        <r>0</r>
        <g>0</g>
        <b>0</b>
    </color>
    <mass>1.000000000</mass>
</body>
```
# Code description
The classes and code files can be divided into three broad categories: application, physics and bridge:
* Application
    * `ofApp`
    * `XmlHelper`
* Physics
    * `PhysicsEngine`
    * `FewBodyEngine`
* Bridge
    * `ColoredSphere`

I will outline toe most significant of these classes in the following sections

## Application - ofApp
The ofApp class is the main application class that contains the three core functions that allow for the running of the application:
* `::setup` - which loads data from the XML file initializes various parts of the application including lights/camera, GUI, and physics engine.
* `::update` - which updates that the simulation engine and takes input from the GUI.
* `::draw` - which pulls data from the simulation engine, handles the 3d rendering and draws the GUI.

Each of these three core functions have associated helper functions that break down these wide scopes into specific action items.

## Physics - PhysicsEngine
The PhysicsEngine class handles the math for the simulation. This is an abstract class that can be implemented using a variety of techniques, one of which I have demonstrated in the FewBodyEngine class. It requires that all implementations do the following:
* `::update` - which should calculate the force on each body and update their positions given at time increment.
* `::HandleCollisions` - which should check for the edge case where two bodies have the same position.

Some important functions that it contains implementations of are:
* `::AddBody` - which allows the user to add bodies to the simulation with set initial parameters
* `::RemovePreviousBody` - which allows the user to remove a body from the simulation.