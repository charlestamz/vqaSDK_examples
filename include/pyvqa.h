//
// Created by Charles Tamz on 10/17/2017.
//

#pragma once

#include "vqasdk_export.h"
#ifdef __cplusplus
extern "C" {
#endif
struct VQAThreshold {
  int brightness{50};    //  亮度异常，类型ID=101
  int contrast{50};      //  对比度异常，类型ID=102
  int color_cast{50};    //  颜色异常（偏色），类型ID=103
  int no_signal{50};     //  信号丢失（黑屏、蓝屏、LOGO屏），类型ID=104
  int freeze{50};        //  视频冻结，类型ID=105
  int blur{50};          //  图像模糊（清晰度异常），类型ID=106
  int noise{50};         //  图像噪声，类型ID=107
  int bars{50};          //  图像条纹，类型ID=108
  int scene_change{50};  //  场景改变，类型ID=109
  int occlusion{50};     //  画面遮挡，类型ID=110
  int ptz_exception{50}; //  PTZ异常，类型ID=111
  int shaking{50};       //  视频抖动，类型ID=112
};

struct VQAResult {
  int brightness{0};    //  亮度异常，类型ID=101
  int contrast{0};      //  对比度异常，类型ID=102
  int color_cast{0};    //  颜色异常（偏色），类型ID=103
  int no_signal{0};     //  信号丢失（黑屏、蓝屏、LOGO屏），类型ID=104
  int freeze{0};        //  视频冻结，类型ID=105
  int blur{0};          //  图像模糊（清晰度异常），类型ID=106
  int noise{0};         //  图像噪声，类型ID=107
  int bars{0};          //  图像条纹，类型ID=108
  int scene_change{0};  //  场景改变，类型ID=109
  int occlusion{0};     //  画面遮挡，类型ID=110
  int ptz_exception{0}; //  PTZ异常，类型ID=111
  int shaking{0};       //  视频抖动，类型ID=112
};

/**
 * set the SDK's params
 * 设置sdk默认参数
 * @param width
 * @param height
 * @param profile_path
 */
void VQASDK_EXPORT initSDKParams(int width, int height, const char *profile_path);
/**
 * 对一帧进行数据诊断
 *
 * @param yuvdata
 * @param width
 * @param height
 */
void VQASDK_EXPORT vqaFrame(const char *yuvdata, VQAResult *result, VQAThreshold *threshold, int width, int height);
/**
 * 对连续帧进行检测
 * @param yuvdata yuv图像序列
 * @param reference_yuvdata 参考帧
 * @param width 宽度
 * @param height 高度
 * @param frame_count 需要检测的帧数
 * @show
 * @return
 */
float VQASDK_EXPORT vqa(const char *yuvdata,
                        const char *reference_yuvdata,
                        VQAResult *result,
                        VQAThreshold *threshold,
                        int width,
                        int height,
                        int frame_count, bool show);

#ifdef __cplusplus
}
#endif
