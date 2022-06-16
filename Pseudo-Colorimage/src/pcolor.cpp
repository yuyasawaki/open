#include <stdio.h>
#include <opencv2/opencv.hpp>

#define FNL 2048
#define SE stderr

char *usage = "\
 options .....\n\
 -i fname : file name of the input image.  <image.png>\n\
 ";

typedef struct lut{
    int r_color,b_color,g_color;
}LUT;

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
    cv::Mat im_in = cv::imread( ifname, mode );
    if(  im_in.data == NULL ){
        fprintf( stderr,"image data is empty.\n");
        exit(-1);
    }
    cv::Mat im_out = cv::Mat::zeros(im_in.rows,im_in.cols,CV_8UC3);

    LUT num[256];

    //<------ make LUT ------>
    int i;
    for(i = 0;i < 256; i++){

        num[i].r_color = 0;       
        num[i].b_color = 255;       
        num[i].g_color = 3*i;       

        
        if(i >= 85){
            num[i].b_color = 255-((i-85)*6.09);
            num[i].g_color = 255;
        }
        if(i >= 127){
            num[i].r_color = (i-127)*5.95;
            num[i].b_color = 0;
        }
        if(i >= 170){
            num[i].r_color = 255;
            num[i].g_color = 255-((i-170)*3);
        }
        
    }


    int j,n;
    for(j = 0; j < im_in.rows; j++){
        for(i = 0; i < im_in.cols; i++){
            n = (int)im_in.at<uchar>(j,i);
            
            im_out.at<cv::Vec3b>(j,i)[0] = (uchar)num[n].b_color;
            im_out.at<cv::Vec3b>(j,i)[1] = (uchar)num[n].g_color;
            im_out.at<cv::Vec3b>(j,i)[2] = (uchar)num[n].r_color;
            
        }
    }

    //<------ output image ------>
    cv::imwrite( "result/Lenna-pcolor.bmp", im_out );

    return 0;
}