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


double GaussNoize(double mu,double d_sigma);
double GetRandom();
int GetRand(int min,int max);

int main(int argc, char** argv)
{   
    //<------ parameter ------>
    char ifname[FNL];
    int mode = cv::IMREAD_GRAYSCALE;      //color mode
    int random = 0;                       //random mode
    double sigma;                         //sigma of gaussian distribution
    double temp;                          //vlaue of gaussian distribution
    double mu;                            //average of gaussian distribution
    cv::Mat im_in;                        //input image
    cv::Mat im_out;                       //output image


    //<------ check options ------>
	for( int idx = 1; idx < argc; idx++){
		if(      !strcmp(argv[idx], "-i") )	     strcpy( ifname, argv[++idx] );
		else if( !strcmp(argv[idx], "-sigma") )	 sigma = atof(argv[++idx]); 
		else if( !strcmp(argv[idx], "-random") ) random = 1; 
		else if( !strcmp(argv[idx], "-color") )	 mode = cv::IMREAD_COLOR;
        else printf("Error : please specify options");
	}

    srand((unsigned) time(NULL));

    //<------ input image ------>
    im_in = cv::imread( ifname, mode);
    if(  im_in.data == NULL){
        printf("Erorr : image data is empty.\n");
        return -1;
    }


    //<------ output log ------>
    FILE *fp;
    fp = fopen("result/RandNoize.txt","a");
    if(fp == NULL){
        printf("Erorr : can not read text.");
        return -1;
    }


    //<------ random mode ------>
    if (random == 1){
        sigma = GetRand(1,1);
    }


    //<------ initialize ------>
    im_out = cv::Mat::zeros(cv::Size(im_in.cols,im_in.rows),CV_8UC1);


    int i,j;
    //<------ generate noise-added images ------> 
    for(j = 0; j < im_in.rows; j++){
        for(i = 0; i < im_in.cols; i++){
                

            mu = (double)im_in.at<uchar>(j,i);
            temp = GaussNoize(mu,sigma);

            if(temp < 0.0) im_out.at<uchar>(j,i) = 0;
            else if(temp > 255.0) im_out.at<uchar>(j,i) = 255;
            else im_out.at<uchar>(j,i) = (int)temp;
            
        }
    }


    //<------ output log&image ------>
    fprintf(fp,"sigma:%lf\n",sigma);
    cv::imwrite("result/im_out.bmp",im_out);

    fclose(fp);

    return 0;
}

int GetRand(int min,int max){

    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX)); 
}

double GetRandom(){
    return ((double)rand()+1.0)/((double)RAND_MAX+2.0);
}

double GaussNoize( double mu, double d_sigma ){
    double z=sqrt( -2.0*log(GetRandom()) ) * sin( 2.0*M_PI*GetRandom() );
    return mu + d_sigma*z;
}