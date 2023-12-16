**VQASDK 事例程序<br>**

支持视频质量检测的SDK

目标操作系统:
```
Centos 7.4 或rlel 7.4
```

依赖:
```
Opencv 3.4.6 
ffmpeg 
boost-devel 
zlib-devel 
bzip2-devel 
sqlite 
sqlite-devel 
openssl-devel 
freetype
libpng-devel 
libjpeg-devel
```

特性：
    <h2>支持c++/c接口调用</h2>
    <h3>c接口说明</h3>
```C
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
   
```
<h2>SDK使用流程</h2>
1.  引入头文件 pyvqa.h
2.  初始化SDK参数
```C
	//sdk_cfg_path为默认初始化参数路径，可以为空，为空时选择使用默认参数
  initSDKParams(width, height, sdk_cfg_path);
```
3.  阈值定义
VQAThreshold 为阈值，初始化默认设置为50，数值越小越敏感，误报越多，数值越大越迟钝，误报越少。具体在实际环境中使用时，建议全部使用默认参数50，当发现某一类误报多或检测比较迟钝时，再具体调低阈值。
4.  检测结果
SDK采用的是多帧混合的模式提供检测准确度，检测结果为多帧的联合结果。检测结果为VQAResult显示的结果，但某具体检测值大于设定阈值时，所以该项检测结果为确定结果。
比如传入VQAThreshold结构体shaking设置为50，当VQAResult返回的shaking值大于50时，说明检测结果抖动。

<h2>c接口调用示例：test_vqa_c.cpp></h2>
```C
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

```
