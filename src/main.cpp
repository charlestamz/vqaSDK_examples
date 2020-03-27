#include "opencv2/opencv.hpp"
#include "pyvqa.h"
#include "vqasdk.h"
using namespace cv;
using namespace cloudvision;
using namespace std;

int main(int argc, char **argv) {
  Size size(480, 270);
  Ptr<cloudvision::VQADetector> pVQA = cloudvision::VQADetector::Create();
  Mat origin;
  VideoCapture video;
  std::string inputfile;
  std::string reference_image_path;
  if (argc < 2) {
    std::cout << "testbad video_file_path [reference_image_path] " << std::endl;
    return -1;
  } else {
    inputfile = argv[1];
    if (argc > 2)
      reference_image_path = argv[2];
    if (reference_image_path == "-debug"){
      pVQA->setDebugMode(true);
      reference_image_path.clear();
    }
    if (argc > 3) {
      string debug = argv[3];
      pVQA->setDebugMode(debug == "-debug");
    }
    video.open(inputfile);

    if (video.isOpened()) {
      if (reference_image_path.empty()) {
        video >> origin;
      } else {
        origin = cv::imread(reference_image_path);
      }

      while (true) {
        int i = 0;
        float start = getTickCount();
        vector<Mat> frames;
        VQAResult result;
        VQAThreshold threshold;
        for (; i < 25; i++) {
          Mat img_input;
          video.read(img_input);
          if (waitKey(3) == 27) break;
          if (img_input.empty())
            break;
          frames.emplace_back(img_input);
        }
        pVQA->vqa(frames, origin, result, threshold,false);
        float end = getTickCount();
        float time = (end - start) / getTickFrequency();
        float fps = i * 1.0f / time;
        std::cout << "time:\t" << time << "\tfps:" << fps << std::endl;
        if (i < 24)break;
      }
      std::cout << " testing end...";

    }
  }

}
