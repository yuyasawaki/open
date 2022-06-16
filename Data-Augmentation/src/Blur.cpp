#include <stdio.h>
#include <opencv2/opencv.hpp>

#define FNL 2048

int GetRandom(int min,int max);

int main(int argc, char** argv )
{   
    //<------ parameter ------>
    char ifname[FNL];
    int mode = cv::IMREAD_GRAYSCALE;        //gray scale mode
    int N;                                  //degree of blurriness
    int random;                             //random mode

    //<------ check options ------>
	for( int idx = 1; idx < argc; idx++){
		if(      !strcmp(argv[idx], "-i") )	strcpy( ifname, argv[++idx] );
		else if( !strcmp(argv[idx], "-blur") ) N = atoi(argv[++idx]);	
		else if( !strcmp(argv[idx], "-random") ) random = 1;	
		else if( !strcmp(argv[idx], "-color") )	mode = cv::IMREAD_COLOR; 
	}


    //<------ read image ------>
    cv::Mat im_in = cv::imread( ifname, mode );
    if(  im_in.data == NULL ){
        fprintf( stderr,"Erorr : image data is empty.\n");
        exit(-1);
    }


    //<------ define output image ------>
    cv::Mat im_out;
    im_out = im_in.clone();

    if(N%2 == 0 || N == 1){
        printf("Erorr : please input odd number.\n");
        return -1;
    }

    FILE *fp;
    fp = fopen("result/Blur.txt","a");
    if(fp == NULL){
        printf("Erorr : can not read text.");
        return -1;
    }


    //<------ random mode ------>
    if (random == 1){
        N = GetRandom(0,50);
    }


    //<------ Averaging filtering ------>
    int i,j,k,l,convolution;
    int w = (N - 1) / 2;//radius of averaging filter.
    int filter_rows = im_in.rows - w,filter_cols = im_in.cols - w;
    for(l = w; l < filter_rows; l++){
        for(k = w; k < filter_cols; k++){
            convolution = 0;
            for(j = -w;j <= w; j++){
                for(i = -w;i <= w; i++){
                    convolution += (int)im_in.at<uchar>(l + j,k + i) / (N*N);//Convolutuin operation
                }
            }
            im_out.at<uchar>(l,k) = (uchar)convolution;
        }
    }


    //<------ output image&log ------>
    fprintf(fp,"N:%d\n",N);
    cv::imwrite("result/im_out.bmp", im_out );

    fclose(fp);

    return 0;
}

int GetRandom(int min,int max){

    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX)); 
}