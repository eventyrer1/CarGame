![CarGame Title](Data/Img/Tittel.png)
![CarGameIMGTitle](Data/Img/oopProsjektTittel.png)






### Human Detection System



The game uses OpenCV's colour detection method to determine where the humans are, but before it does that we need to convert the image into somethign the computer understands more easily 

![Human Detector Comparison](Data/Img/output.png)

#### How It Works

-  1 Capture the current game frame.
-  2 Convert the frame from BGR to HSV color space.
-  3 Apply a yellow color filter:
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
