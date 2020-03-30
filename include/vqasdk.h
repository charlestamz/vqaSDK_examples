#pragma once
#include <vector>
#include <opencv2/opencv.hpp>
#include "vqasdk_export.h"
#include "pyvqa.h"

namespace cloudvision {

class VQASDK_EXPORT VQADetector {
 public:
  VQADetector();
  virtual void setSize(int width, int height) = 0;
  virtual void setDebugMode(bool debug) = 0;
/**
 * 对一帧进行数据诊断
 *
 * @param frame
 * @param width
 * @param height
 */
  virtual void vqaFrame(cv::Mat frame, VQAResult &result, VQAThreshold &threshold) = 0;
/**
 * 对连续帧进行检测
 * @param frames 视频序列
 * @param origin 参考帧
 * @param result 输出结果
 * @param threshold 阈值
 * @param show 
 * @return
 */
  virtual void vqa(std::vector<cv::Mat> frames, cv::Mat origin, VQAResult &result, VQAThreshold &threshold, bool show) = 0;
  /**
   * 返回质量检测器实例
   * @return
   */
  static VQADetector * Create();

};

}





