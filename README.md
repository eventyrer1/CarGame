
<div align="center">

![CarGame Title](Data/Img/Tittel.png)
</div>

![CarGameIMGTitle](Data/Img/oopProsjektTittel.png)
<br/><br/>
**candidate number: [10054]**
## Project Overview
Auto-Slaughter is a "game" where the goal is to drive over every human. The game can be controlled classically with keyboard inputs but also has an AI mode where the car drives itself and hunts down humans using computer vision.
The game is primarily a Tech demo, so I am very aware it is a terrible game, but rather a demonstration of my skills in C++ and computer vision using OpenCV.

## Controls
- WASD to move
- Press "AI Steering" button to toggle Auto detection<br>
- Press the Reset button to restart the game
- Change the sliders to change the properties of the car<br>
  ![AI button](Data/Img/AI-mode.png)


## UML Diagram

![UML Diagram](Data/Img/UML.png)
<div align="center">
(White classes are classes that i did not create)
</div>

## Features
- Dynamic movement of the car 
- AI mode that detects humans and drives over them
- Reset button to restart the game
- Powerup when driving over a human (decreases the turn speed of the car)
- Entertaining(?) sound effects
- ImGui interface for changing car properties in real-time



# Code information

### Foreword: 
A lot of stuff in this project is done in a weird or unneeded way. Often the reason behind this was that I wanted to show/learn that I can do it, or as a wise man once said:<br>
**"But, but why?** <br>
**Because fun."**

### Notes:

- ImGui’s setup is more complicated than necessary because it was implemented before discovering threepp’s built-in ImGui integration. But since it doesn't affect the project negatively, I left it as is.
  <br/><br/>
- Why are some libraries fetched using CMake FetchContent and others using external libraries? while OpenCV uses vcpkg <br>
  -Because I wanted to show that I can use all these methods. And OpenCV has too large files for GitHub so I had to use vcpkg.
  <br/><br/>
- Each time you clone this project, vcpkg will be downloaded and installed automatically. This makes it waaay slower if you already have vcpkg installed, but it makes it more deterministic, and I don't trust people to be able to install vcpkg on their own.


## Human Detection System
The game uses OpenCV's colour detection method to determine where the humans are, converting frames into a format the computer can parse easily.

![Human Detector Comparison](Data/Img/output.png)

### How It Works
1. Capture the current game frame.
2. Convert the frame from BGR to HSV colour space.
3. Apply a yellow colour filter to isolate humans:
   ```cpp
   cv::inRange(
       hsv_,
       cv::Scalar(20, 100, 50),
       cv::Scalar(35, 255, 255),
       mask_
   );
   ```
4. Extract contours from the mask and compute bounding boxes.
5. Select the human whose bounding box centre is closest to the screen centre as the active target.

## Reflection

### What works wel

    - AI detection pipeline reliably highlights yellow targets and feeds the steering logic clean bounding boxes thanks to the HSV mask and contour filtering.
  

<br/><br/>
### What needs improvement

    - SoC principles could be better applied; separating visual and logic in for example Car could be done better, by for example splitting it into CarLogic and CarVisual classes.
    - Testing coverage was done as a afterthought; more and better testing practices could be implemented to ensure better code quality from the start.
    - The AI steering controller can oscillate at high speeds; implementing a PID controller with clamped outputs
    - Commenting and readabilty could be done way better, but this was something that i didnt focus on during development (which i now regret) 
  

### Sources:

Coding examples for OpenCV were found here: https://github.com/opencv/opencv/tree/4.x/samples/cpp/example_cmake<br>
Magnus Evenstuen for voicing all sounds in the game and for using his face in the human model

Developed using threepp,OpenCV, ImGui,vcpkg, CMake

"Lowpoly Human Reff" (https://skfb.ly/ot8Cu) by fadhlisl is licensed under Creative Commons Attribution (http://creativecommons.org/licenses/by/4.0/). Edited by me to include the Face   <br/><br/>
 3D model "Low-Poly Car" by wufudufu — downloaded from Free3D (https://free3d.com/3d-model/low-poly-car-40967.html), accessed 15.10.2025.  <br/><br/>
"Prism Stone - Magical Energy Stone" (https://skfb.ly/6S6oL) by ENOMIC is licensed under CC Attribution-NonCommercial-ShareAlike (http://creativecommons.org/licenses/by-nc-sa/4.0/). Edited by me to change the texture to black and blue <br/><br/>
Sound Effect by <a href="https://pixabay.com/users/freesound_community-46691455/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=82807">freesound_community</a> from <a href="https://pixabay.com//?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=82807">Pixabay</a>