/*
name:Yuya Sawaki
date:2021,8,24
This program adjusts the gain and offset of the image.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <time.h>

#define FNL 2048


int GetRandom(int miin,int max);

int main(int argc, char** argv)
{   
    //<------ parameter ------>
    char ifname[FNL];
    int mode = cv::IMREAD_GRAYSCALE;        //gray scale mode
    int gain=1;                             //adjust image gain
    int offset;                             //adjust image offset
    int random;                             //random mode
    cv::Mat im_tmp;                         //template image
    cv::Mat im_out;                         //output image


    //<------ check options ------>
	for( int idx = 1; idx < argc; idx++){
		if(      !strcmp(argv[idx], "-i") )	        strcpy( ifname, argv[++idx] );
		else if( !strcmp(argv[idx], "-offset") )	offset = atoi(argv[++idx]);
		else if( !strcmp(argv[idx], "-random") )	random = 1;
		else if( !strcmp(argv[idx], "-color") )	    mode = cv::IMREAD_COLOR;
	}


    //<------ input template image ------>
    im_tmp = cv::imread( ifname, mode);
    if(  im_tmp.data == NULL){
        printf("Erorr : image data is empty.\n");
        return -1;
    }


    //<------ define output image ------>
    im_out = cv::Mat::zeros(cv::Size(im_tmp.cols,im_tmp.rows),CV_8UC1);
    double arr[im_tmp.rows][im_tmp.cols] = {};


    srand((unsigned) time(NULL));

    FILE *fp;
    fp = fopen("result/Offset.txt","a");
        

    //<------ random mode ------>
    if (random == 1) offset = GetRandom(-140,59);


    //<------ Offset correction ------>
    int i,j;
    for(j = 0; j < im_tmp.rows; j++){
        for(i = 0; i < im_tmp.cols; i++){
            arr[j][i] = (double)((gain * im_tmp.at<uchar>(j,i)) + offset);
        }
    }


    for(j = 0; j < im_tmp.rows; j++){
        for(i = 0; i < im_tmp.cols; i++){
            if(arr[j][i] > 255.0) im_out.at<uchar>(j,i) = 255.0;
            else if(arr[j][i] < 0) im_out.at<uchar>(j,i) = 0.0;
            else im_out.at<uchar>(j,i) = (uchar)arr[j][i];
        }
    }

    cv::imwrite("result/im_out.bmp",im_out);

    fprintf(fp,"gain:%d offset:%d\n",gain,offset);

    fclose(fp);

    return 0;
}

int GetRandom(int min,int max){

    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX)); 
}
