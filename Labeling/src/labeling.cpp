/*
name:Yuya Sawaki
date:2020,8,28
This program labels spiral-003 in three color. 
*/

#include <stdio.h>
#include <opencv2/opencv.hpp>

#define FNL 2048
#define SE stderr
#define FG 0 //intensity of foreground object
#define BG 255 //intensity of background 
#define MAX_VALUE 5000  //look up table array size 

char *usage = "\
 options .....\n\
 -i fname : file name of the input image.  <image.png>\n\
 ";

int main(int argc, char** argv )
{
    char ifname[FNL];
    int mode = cv::IMREAD_GRAYSCALE;


    //<------ check options ------>
	for( int idx = 1; idx < argc; idx++){
		if(      !strcmp(argv[idx], "-i") )	strcpy( ifname, argv[++idx] );
		else if( !strcmp(argv[idx], "-color") )	mode = cv::IMREAD_COLOR;
		else{ fprintf(SE, "%s", usage); return 0; }
	}


    //<------ read image ------>
    cv::Mat im_in = cv::imread( ifname, CV_8UC1 );
    if(  im_in.data == NULL ){
        fprintf( stderr,"image data is empty.\n");
        exit(-1);
    }
    
    int N;
    printf("4 conection or 8 conection ?\n");
    printf("0: 8 conection 1: 4 conection\n"); scanf("%d",&N);

    cv::Mat im_binaraize = cv::Mat::zeros(im_in.rows,im_in.cols,CV_8UC1);
    cv::Mat im_out = cv::Mat::zeros(im_in.rows,im_in.cols,CV_8UC3) ;


    //<------ discriminant analysis method ------>
    int arr[256] = {};
    int i,j;
    uchar val = 0;
    for(j = 0;j < im_in.rows;j++){
        for(i = 0;i < im_in.cols;i++){
            val = im_in.at<uchar>(j,i);
            arr[val]++;
            val = 0;
        }
    }

    int th;
    int add1 = 0,add2 = 0;
    int w1 = 0,w2 = 0;
    double m1,m2;
    double max,a,b;
    int k;
    for(k = 1;k < 255;k++){
        for(i = 0;i < k; i++){
            w1 += arr[i];
            add1 += (i * arr[i]);
        }
        for(j = 255;j > k;j--){
            w2 += arr[j];
            add2 += (j * arr[j]);
        }
        m1 = (double)add1 / (double)w1; m2 = (double)add2 / (double)w2;
        
        a = (double)w1*(double)w2*(m1 - m2)*(m1 - m2);
        if(max < a){
            max = a;
            th = k;
        }
        w1 = 0; w2 = 0; 
        add1 = 0; add2 = 0;
    }

    //<------ binaraize ------>
    for(j = 0;j < im_in.rows;j++){
        for(i = 0;i < im_in.cols;i++){
            if(im_in.at<uchar>(j,i) > th) im_binaraize.at<uchar>(j,i) = 255;
            else im_binaraize.at<uchar>(j,i) = 0;
        }
    }


    int LUT[MAX_VALUE][2];
    int labering[im_in.rows][im_in.cols];
    //initialization
    for(j = 0;j < im_in.rows;j++){
        for(i = 0;i < im_in.cols;i++){
            labering[j][i] = 0;
        }
    }
    for(i = 0; i < MAX_VALUE; i++){
        LUT[i][0] = i;
        LUT[i][1] = i;
    }

    int l,n,m;
    int s = 0,t = 0;
    int MIN = MAX_VALUE,SUM = 0;
    int count = 1;
    for(j = 0; j < im_in.rows; j++){
        for(i = 0; i < im_in.cols; i++){
            //find black pixel
            if(im_binaraize.at<uchar>(j,i) == 0){
                //find left,top left,top,top right labels
                for(k = N; k < 4; k+=(N+1)){
                    s = (k/3) - 1; t = (k%3) - 1;
                    if(im_binaraize.at<uchar>(j + s,i + t) < 255){
                        if(MIN >= labering[j + s][i + t]){
                            MIN = labering[j + s][i + t];
                            labering[j][i] = MIN;
                        }
                    }
                }
                //update lookup table
                for(l = 0; l < 4; l++){
                    s = (l/3) - 1; t = (l%3) - 1;
                    if(MIN < labering[j + s][i + t]) LUT[labering[j + s][i + t]][1] = MIN; 
                }
                //input new label
                if(labering[j][i] == 0){
                    for(n = j - 1; n <= j + 1; n++){
                        for(m = i - 1; m <= i + 1; m++){
                            SUM += im_binaraize.at<uchar>(n,m);
                        }
                    }
                    //don't label individual pixel
                    if(SUM == 2040) LUT[labering[j][i]][1] = 0;
                    else {
                        labering[j][i] = LUT[count][0];
                        count++;
                    }
                }
                MIN = MAX_VALUE; SUM = 0;
            }
        }
    }

    //update lookup tabel
    for(j = 0; j < im_in.rows; j++){
        for(i = 0; i < im_in.cols; i++){
            if(labering[j][i] != 0){
                while(LUT[labering[j][i]][0] != LUT[labering[j][i]][1]){
                    labering[j][i] = LUT[labering[j][i]][1];
                }
            }
        }
    }
    //find the value of the label
    int label[count] = {};
    int count2 = 0;
    for(i = 1; i < count; i++){
        if(LUT[i][0] == LUT[i][1]){
            label[count2] = LUT[i][1];
            count2++;
        } 
    }

    //color labels
    for(j = 0; j < im_in.rows; j++){
        for(i = 0; i < im_in.cols; i++){
            if(labering[j][i] == label[0]){
                im_out.at<cv::Vec3b>(j,i)[0] = 255;
                im_out.at<cv::Vec3b>(j,i)[1] = 0;
                im_out.at<cv::Vec3b>(j,i)[2] = 0;
            }
            if(labering[j][i] == label[1]){
                im_out.at<cv::Vec3b>(j,i)[0] = 0;
                im_out.at<cv::Vec3b>(j,i)[1] = 255;
                im_out.at<cv::Vec3b>(j,i)[2] = 0;
            }
            if(labering[j][i] == label[2]){
                im_out.at<cv::Vec3b>(j,i)[0] = 0;
                im_out.at<cv::Vec3b>(j,i)[1] = 0;
                im_out.at<cv::Vec3b>(j,i)[2] = 255;
            }
        }
    }
    cv::imwrite("result/labering.bmp",im_out);

    return 0;
}