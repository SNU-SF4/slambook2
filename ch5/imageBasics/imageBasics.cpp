#include <iostream>
#include <chrono>

using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv) {
  // Read the image in argv[1]
  cv::Mat image;
  image = cv::imread(argv[1]); // call cv::imread to read the image from file

  // check the data is correctly loaded
  if (image.data == nullptr) { // maybe the file does not exist
    cerr << "file" << argv[1] << " not exist." << endl;
    return 0;
  }

  // print some basic information
  cout << "Image cols: " << image.cols << ", rows: " << image.rows << " , channels: " << image.channels() << endl;
  cv::imshow("image", image);      // use cv::imshow to show the image
  cv::waitKey(0);                  // display and wait for a keyboard input

  // check image type
  if (image.type() != CV_8UC1 && image.type() != CV_8UC3) {
    // we need grayscale image or RGB image
    cout << "image type incorrect." << endl;
    return 0;
  }

  // In line 41~52, we iterate over all pixels in the image and calculates the time
  // spent in the entire loop. Please note that the pixel visiting method is not
  // unique, and the method given by the example is not the most efficient way.
  // OpenCV provides an iterator of cv::Mat. You can traverse the pixels of the
  // image through the iterator. Or, cv::Mat::data provides a raw pointer to the
  // beginning of the image data. You can also directly calculate the offset through
  // this pointer, and then get the memory location of the pixel. The method used
  // in the example is to facilitate the reader to understand the structure of the image.
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  for (size_t y = 0; y < image.rows; y++) {
    // use cv::Mat::ptr to get the pointer of each row
    unsigned char *row_ptr = image.ptr<unsigned char>(y);  // row_ptr is the pointer to y−th row
    for (size_t x = 0; x < image.cols; x++) {
      // read the pixel on (x,y), x=column, y=row
      unsigned char *data_ptr = &row_ptr[x * image.channels()]; // data_ptr is the pointer to (x,y)
      // visit the pixel in each channel
      for (int c = 0; c != image.channels(); c++) {
        unsigned char data = data_ptr[c]; // data should be pixel of I(x,y) in c−th channel
      }
    }
  }
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
  chrono::duration<double> time_used = chrono::duration_cast < chrono::duration < double >> (t2 - t1);
  cout << "time used: " << time_used.count() << " seconds." << endl;

  // copying cv::Mat
  // operator = will not copy the image data, but only the reference
  cv::Mat image_another = image;
  // changing image_another will also change image
  image_another(cv::Rect(0, 0, 100, 100)).setTo(0); // set top−left 100∗100 block to zero
  cv::imshow("image", image);
  cv::waitKey(0);

  // use cv::Mat::clone to actually clone the data
  cv::Mat image_clone = image.clone();
  image_clone(cv::Rect(0, 0, 100, 100)).setTo(255);
  cv::imshow("image", image);
  cv::imshow("image_clone", image_clone);
  cv::waitKey(0);

  // We are not going to copy the OpenCV's documentation here
  // please take a look at it for other image operations like clipping, rotating and scaling.
  cv::destroyAllWindows();
  return 0;
}
