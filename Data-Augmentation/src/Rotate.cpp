/*
name:Yuya Sawaki
date:2021,8,22
This program adds noise to the image
*/

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <time.h>

#define FNL 2048

int GetRandom(int min,int max);
void Rotation(cv::Mat *im_in,cv::Mat *im_out,int theta);             

int main(int argc, char** argv)
{   
    //parameter
    char ifname[FNL];
    int mode = cv::IMREAD_GRAYSCALE;      //color mode
    int random = 0;                       //random mode
    int theta;                            //rotate value
    cv::Mat im_in;                        //input image
    cv::Mat im_out;                       //output image

    // Check Options
	for( int idx = 1; idx < argc; idx++){
		if(      !strcmp(argv[idx], "-i") )	     strcpy( ifname, argv[++idx] );
		else if( !strcmp(argv[idx], "-theta") )	 theta = atoi(argv[++idx]);
		else if( !strcmp(argv[idx], "-color") )	 mode = cv::IMREAD_COLOR;
	}

    srand((unsigned) time(NULL));

    //<------ input image ------>
    im_in = cv::imread( ifname, mode);
    if(  im_in.data == NULL){
        printf("Erorr : image data is empty.\n");
        return -1;
    }


    //<------ Rotate.txt open ------>
    FILE *fp;
    fp = fopen("result/Rotate.txt","a");
    if(fp==NULL){
        printf("Erorr : can nor read text\n");
        return -1;
    }


    //<------ rotate ------>
    Rotation(&im_in,&im_out,theta);


    //<------ output log ------>
    fprintf(fp,"theta:%d\n",theta);


    //<------ output imamge ------>
    cv::imwrite("result/im_out.bmp",im_out);

    fclose(fp);

    return 0;
}

int GetRandom(int min,int max){

    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));; 
}

void Rotation(cv::Mat *im_in,cv::Mat *im_out,int theta){

    int i,j;
    int c,d;
    double hin_cols,hin_rows;
    double hout_cols,hout_rows;
    double a,b;
    double pi = M_PI / 180.0;
    double rtwo,rtwo_cols,rtwo_rows;

    rtwo = sqrt((im_in->rows*im_in->rows) + (im_in->cols*im_in->cols));

    *im_out = cv::Mat::zeros(rtwo,rtwo,CV_8UC3);

    hin_cols = (double)im_in->cols / 2.0;
    hin_rows = (double)im_in->rows / 2.0;
    hout_cols = (double)im_out->cols / 2.0;
    hout_rows = (double)im_out->rows / 2.0;

    double rad = (double)theta*pi;//change degree to radian
    double tx = ((cos(rad)*hout_cols) + (sin(rad)*hout_rows)) - hin_cols;
    double ty = ((-sin(rad)*hout_cols) + (cos(rad)*hout_rows)) - hin_rows;
    double rotate[2][2] = {{cos(rad),sin(rad)},//rotation invers matrix
                            {-sin(rad),cos(rad)}};

    for(j = 0;j < im_out->rows;j++){
        for(i = 0;i < im_out->cols;i++){
            a = ((rotate[0][0]*(double)i) + (rotate[0][1]*(double)j) - tx);//find the pixel value before rotate
            b = ((rotate[1][0]*(double)i) + (rotate[1][1]*(double)j) - ty);
            c = (int)(a + 0.5); d = (int)(b + 0.5);//rounding up

            if(0 <= c && 0 <= d){
                if(c < im_in->cols && d < im_in->rows){

                    im_out->at<cv::Vec3b>(j,i)[0] = im_in->at<cv::Vec3b>(d,c)[0];
                    im_out->at<cv::Vec3b>(j,i)[1] = im_in->at<cv::Vec3b>(d,c)[1];
                    im_out->at<cv::Vec3b>(j,i)[2] = im_in->at<cv::Vec3b>(d,c)[2];
                }
            }
            a = 0.0,b = 0.0,c = 0,d = 0;//initialization
        }
    }
}
