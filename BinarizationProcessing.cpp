#include <iostream>
#include <opencv2/opencv.hpp>

#define HIGHVAL (255)   //白画素の値
#define LOWVAL (0)      //黒画素の値
#define TH (95)        //しきい値
#define FILENAME "画像ファイルのフルパス"

int main(int argc, const char * argv[])
{
    //変数定義
    cv::Mat src_img, gray_img, bin_img;
    //画像入力
    src_img = cv::imread(FILENAME, cv::IMREAD_COLOR);
    if(src_img.empty()){    //画像ファイル読み込み失敗
        printf("Cannot read image file: %s\n",FILENAME);
        return (-1);
    }
    //輝度画像への変換
    cv::cvtColor(src_img, gray_img, cv::COLOR_RGB2GRAY);

    //二値画像の生成
    bin_img.create(gray_img.size(), gray_img.type());
    //二値画像への変換
    for(int y=0; y<gray_img.rows; y++){
        for(int x=0; x<gray_img.cols; x++){
            if(gray_img.at<unsigned char>(y,x) > TH){
                bin_img.at<unsigned char>(y,x) = HIGHVAL;
            }else{
                bin_img.at<unsigned char>(y,x) = LOWVAL;
            }
        }
    }
    //画像表示
    cv::imshow("input image",src_img);
    cv::imshow("grayscale image",gray_img);
    cv::imshow("binary image",bin_img);
    cv::imwrite("binaryImage.png",bin_img);
    //キー入力待ち
    cv::waitKey(0);
    return (0);
}