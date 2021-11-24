# doodleJumpGL

## What is this thing?!

This is the code for the first project for the Computer Graphics course at the University Of Bologna. The goal was to make an interactable 2D scene in OpenGL.
I decided to make a clone of the mobile game "DoodleJump", which is the perfect example of a simple yet fun game.

Some of the features of the original are missing (such as enemies and springs) due to time and complexity constraints.


## How to compile

This branch represents the <b>Linux version</b> of the code (which is essentially the same aside from some minor tweaks and the compilation method). You can check the Windows version of the code [here](https://github.com/AngeloGalav/doodleJumpGL/tree/windows).

To compile and run in Linux, simply use the following commands:

```
cd doodleJumpGL
make && ./DoodleJumpGL
```

and that's pretty much it.

## Dependencies

This project uses the following libraries:
<ul>
<li>freeGLUT - an implementation of GLUT</li>
<li>GLEW</li>
<li>glm - the openGL math library</li>
</ul>

Both can be easily downloaded with `pacman` or `apt-get`.

The project also uses two additional libraries: `json.hpp` and `gltext.h`, which are both included in the project. 

## How do you play this darn game?!

You simply press `a` to go left and `d` to go right. The goal is to reach the highest point possible. If you die, you can simply press `r` to restart (as prompted). 

## Known issues

Here are some of the known issues with this version, which hopefully will get fixed in the next version:
<ul>
<li>The game does NOT recognize capital 'A', 'D' or 'R' as input. Check if Caps Lock is enabled. </li>
<li>The collisions with the platforms are a bit wonky.</li>
<li>Some of the Hermite meshes are slightly broken.</li>
<li>The code is still very rough, and could use some refactoring.</li>
</ul>

## Additional things

The game features a debug mode, which shows the main character's colliders, as well as additional info on the game on the stdout.
Also, there's a special Mesh for the character made with an Hermite curve, which is disabled by default.  
Both of these features can be enabled by modifying their respective macros in `Definitions.h`.

## Scheenshots

<figure>
<img src=".\linux_screenshots\image1.png" alt="first linux screenshot" style="zoom:50%;" />
<p align="center">
    <i>A normal gameplay session.</i>
</p>
</figure>
<hr />
<figure>
<img src=".\linux_screenshots\image2.png" alt="second linux screenshot" style="zoom:50%;" />
<p align="center">
    <i>The special character mesh. It's disabled by default 'cause I like the first one better. </i>
</p>
</figure>

