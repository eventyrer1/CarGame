### Human Detection System



The game includes a lightweight computer-vision system that detects humans based on their color.  
Each rendered frame is captured from the in-game camera and processed using OpenCV to identify yellow human models.

![Human Detector Comparison](Data/Img/output.png)

#### How It Works

- Capture the current game frame.
- Convert the frame from BGR to HSV color space.
- Apply a yellow color filter:
  ```cpp
  cv::inRange(
      hsv_,
      cv::Scalar(20, 100, 50),
      cv::Scalar(35, 255, 255),
      mask_
  );
- The mask keeps only yellow pixels (the human models) and discards everything else.
- Extract contours from the mask and compute bounding boxes.
- Select the human whose bounding box center is closest to the center of the screen as the active target.

  
### Kilder:
Jon aksel for kode hjelp/tips
Magnus For Fjeset sitt og kræsj lyder

"Lowpoly Human Reff" (https://skfb.ly/ot8Cu) by fadhlisl is licensed under Creative Commons Attribution (http://creativecommons.org/licenses/by/4.0/).

For kodingen av opencv cmake https://github.com/opencv/opencv/blob/4.x/samples/cpp/example\_cmake/CMakeLists.txt
