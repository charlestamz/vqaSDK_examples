//
// Created by kanbig on 19-5-8.
//

//
#include <stdio.h>
#include <malloc.h>
#include "vqasdk_export.h"
#include "pyvqa.h"

int main() {
  char *sdk_cfg_path = "/home/kanbig/vqaSDK";
  char *yuv_data_path = "/home/charlie/Videos/video_quality/bus_cif.yuv";
  int width = 352;
  int height = 288;
  const int framesize = width * height * 3 / 2;   //一副图所含的像素个数
  initSDKParams(width, height, sdk_cfg_path);
  FILE *fileIn = fopen(yuv_data_path, "rb+");

  if (fileIn == NULL) {
    printf("the file is error\n");
    return -1;
  }
  fseek(fileIn, 0L, SEEK_END);
  long ps = ftell(fileIn);

  unsigned frame_count = ps / framesize; //帧大小
  printf("file size: %d   frame count: %d \n", ps, frame_count); //输出帧数
  int vqa_frames_count = 10;
  char pYuvBuf[framesize * vqa_frames_count]; //一帧数据大小
  //存储到图像
  rewind(fileIn);
  for (int i = 0; i < frame_count; ++i) {
    struct VQAResult result;
    struct VQAThreshold threshold;
    fread(pYuvBuf, framesize * vqa_frames_count * sizeof(char), 1, fileIn);
    vqa(pYuvBuf, pYuvBuf, &result, &threshold, width, height, vqa_frames_count, 1);
    printf(" result :  "
           "亮度异常，类型ID=101: %d  \n  "
           "对比度异常，类型ID=102: %d  \n "
           "颜色异常（偏色），类型ID=103: %d  \n "
           "信号丢失（黑屏、蓝屏、LOGO屏），类型ID=104: %d  \n "
           "视频冻结，类型ID=105: %d  \n "
           "图像模糊（清晰度异常），类型ID=106: %d  \n "
           "图像噪声，类型ID=107: %d  \n "
           "图像条纹，类型ID=108: %d  \n "
           "场景改变，类型ID=109: %d  \n "
           "画面遮挡，类型ID=110: %d  \n "
           "PTZ异常，类型ID=111: %d  \n "
           "视频抖动，类型ID=112 ): %d  \n ",
           result.brightness,
           result.contrast,
           result.color_cast,
           result.no_signal,
           result.freeze,
           result.blur,
           result.noise,
           result.bars,
           result.scene_change,
           result.occlusion,
           result.ptz_exception,
           result.shaking);
    printf("第 %d 帧\n", i);
    i += vqa_frames_count;
  }

  fclose(fileIn);

  return 0;
}
