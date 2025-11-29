

![CarGame Title](Data/Img/Tittel.png)
![CarGameIMGTitle](Data/Img/oopProsjektTittel.png)

## Project Overview
Auto Slaughter is a 3D driving game that combines classis WASD-controls with a computer-vision-based human detection system.

## Key Features
- **Driving gameplay**: Accelerate, brake, and steer a car through the environment with responsive keyboard controls.
- **Human detection**: OpenCV-based colour detection highlights humans and make the car automaticly target the closest human


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

### Kilder:
Jon aksel for kode hjelp/tips
Magnus For Fjeset sitt og kræsj lyder

"Lowpoly Human Reff" (https://skfb.ly/ot8Cu) by fadhlisl is licensed under Creative Commons Attribution (http://creativecommons.org/licenses/by/4.0/).

For kodingen av opencv cmake https://github.com/opencv/opencv/blob/4.x/samples/cpp/example\_cmake/CMakeLists.txt
