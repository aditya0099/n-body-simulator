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
```<body>
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