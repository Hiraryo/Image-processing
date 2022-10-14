#include <iostream>
#include <opencv2/opencv.hpp>

#define HIGHVAL (255)   //白画素の値
#define LOWVAL (0)      //黒画素の値
#define FILENAME "二値画像のフルパス"
#define NEIGHBORS (4)   //近傍基準（この場合4近傍）
int delta[NEIGHBORS][2] = {{0,-1},{-1,0},{1,0},{0,1}};   //注目画素から見た近傍画像の相対位置

int main(int argc, const char * argv[])
{
    //変数定義
    cv::Mat bin_img, dilated_img;
    int nx, ny;
    //画像入力
    bin_img = cv::imread(FILENAME, cv::IMREAD_GRAYSCALE);
    if(bin_img.empty()){    //画像ファイル読み込み失敗
        printf("Cannot read image file: %s\n",FILENAME);
        return (-1);
    }
    //膨張画像の生成（生成時は白画素で占められているとする）
    dilated_img.create(bin_img.size(),bin_img.type());
    dilated_img.setTo(HIGHVAL);

    //膨張処理
    for(int y=0; y<bin_img.rows; y++){
        for(int x=0; x<bin_img.cols; x++){
            if(bin_img.at<unsigned char>(y,x) == LOWVAL){  //黒画素の場合
                dilated_img.at<unsigned char>(y,x) = LOWVAL;   //注目画素を黒画素にする
                for(int idx=0; idx<NEIGHBORS; idx++){   //近傍画素も黒画素にする
                    nx = x + delta[idx][0];
                    ny = y + delta[idx][1];
                    if(nx >= 0 && nx < dilated_img.cols && ny >= 0 && ny < dilated_img.rows){
                        dilated_img.at<unsigned char>(ny,nx) = LOWVAL;
                    }
                }
            }                                               //白画素の場合は何もしない
        }
    }
    //画像表示
    cv::imshow("input image",bin_img);
    cv::imshow("dilated image",dilated_img);
    cv::imwrite("binaryImage_.png",dilated_img);
    //キー入力待ち
    cv::waitKey(0);
    return (0);
}