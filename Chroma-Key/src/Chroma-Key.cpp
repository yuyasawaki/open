/*
name:Yuya Sawaki
This program performs chromakey composition.
*/

#include <stdio.h>
#include <opencv2/opencv.hpp>

#define FNL 2048
#define SE stderr

char *usage = "\
 options .....\n\
 -i1 fname : file name of the input image.  \n\
 -i2 fname : file name of the input image.  \n\
 -color    : color mode                     \n\
 ";

void MaskImage(cv::Mat mask_image);
void Image1(cv::Mat im_in1,cv::Mat mask_image,cv::Mat image1);
void Image2(cv::Mat im_in2,cv::Mat mask_image,cv::Mat image2);
void Comp(cv::Mat image1,cv::Mat image2,cv::Mat composite_image);

int main(int argc, char** argv)
{


    char ifname1[FNL],ifname2[FNL];
    int mode = cv::IMREAD_COLOR;

    //<------ check options ------>
	for( int idx = 1; idx < argc; idx++){
		if(      !strcmp(argv[idx], "-i1") )	strcpy( ifname1, argv[++idx] );
		else if( !strcmp(argv[idx], "-i2") )	strcpy( ifname2, argv[++idx] );
		else if( !strcmp(argv[idx], "-color") )	mode = cv::IMREAD_COLOR;
		else{    fprintf(SE, "%s", usage); return 0; }
	}


    //<------ read image ------>
    cv::Mat im_in1 = cv::imread( ifname1, mode );
    cv::Mat im_in2 = cv::imread( ifname2, mode );
    if(  im_in1.data == NULL || im_in2.data == NULL){
        fprintf( stderr,"image data is empty.\n");
        exit(-1);
    }


    //<------ resize im_in2 image ------>
    cv::resize(im_in2,im_in2,cv::Size(im_in1.cols,im_in1.rows));


    //<------ make mask image ------>
    cv::Mat mask_image(cv::Size(704,528),CV_8UC3);
    mask_image = im_in1.clone();
    MaskImage(mask_image);


    //<------ Composite im_in1 and im_in2 ------> 
    cv::Mat image1(cv::Size(im_in1.cols,im_in1.rows),CV_8UC3);
    Image1(im_in1,mask_image,image1);
    cv::Mat image2(cv::Size(im_in1.cols,im_in1.rows),CV_8UC3);
    Image2(im_in2,mask_image,image2);
    cv::Mat composite_image(cv::Size(im_in1.cols,im_in1.rows),CV_8UC3);
    Comp(image1,image2,composite_image);


    //<------ output image ------>
    //cv::imshow( "Comp", composite_image );
    cv::waitKey();
    cv::destroyAllWindows();
    cv::imwrite( "result/im_out.bmp", composite_image );

    return 0;
}

void MaskImage(cv::Mat mask_image){
    
    //<------ HSV conversion ------>
    int i,j;
    double hue,sat,val,val_max,val_min;
    for(j = 0;j < 528; j++){
        for(i = 0;i < 704; i++){
            val_max = (double)mask_image.at<cv::Vec3b>(j,i)[0];
            if(val_max < mask_image.at<cv::Vec3b>(j,i)[1]) val_max = (double)mask_image.at<cv::Vec3b>(j,i)[1];
            if(val_max < mask_image.at<cv::Vec3b>(j,i)[2]) val_max = (double)mask_image.at<cv::Vec3b>(j,i)[2];

            val_min = (double)mask_image.at<cv::Vec3b>(j,i)[0];
            if(val_min > mask_image.at<cv::Vec3b>(j,i)[1]) val_min = (double)mask_image.at<cv::Vec3b>(j,i)[1];
            if(val_min > mask_image.at<cv::Vec3b>(j,i)[2]) val_min = (double)mask_image.at<cv::Vec3b>(j,i)[2];

            if(val_max == mask_image.at<cv::Vec3b>(j,i)[0]){ 
                
                hue = ((((double)mask_image.at<cv::Vec3b>(j,i)[2] - (double)mask_image.at<cv::Vec3b>(j,i)[1]) / (val_max - val_min))*60.0) + 240.0;

            }else if(val_max == mask_image.at<cv::Vec3b>(j,i)[1]){

                 hue = ((((double)mask_image.at<cv::Vec3b>(j,i)[0] - (double)mask_image.at<cv::Vec3b>(j,i)[2]) / (val_max - val_min))*60.0) + 120.0;

            }else{

                 hue = (((double)mask_image.at<cv::Vec3b>(j,i)[1] - (double)mask_image.at<cv::Vec3b>(j,i)[0]) / (val_max - val_min))*60.0;
            }
            if(hue < 0.0) hue += 360.0;

            sat = (val_max - val_min) / val_max;
            
            int flag = 0;
            if(205.0 < hue && hue < 215.0){
                if(sat > 0.7){
                    mask_image.at<cv::Vec3b>(j,i)[0] = 0;
                    mask_image.at<cv::Vec3b>(j,i)[1] = 0;
                    mask_image.at<cv::Vec3b>(j,i)[2] = 0;
                    flag = 1;
                }

            }
            if(flag == 0){

                mask_image.at<cv::Vec3b>(j,i)[0] = 1;
                mask_image.at<cv::Vec3b>(j,i)[1] = 1;
                mask_image.at<cv::Vec3b>(j,i)[2] = 1;
            }
            flag = 0;
        }
    }
}

void Image1(cv::Mat im_in1,cv::Mat mask_image,cv::Mat image1){

    int i,j;
    for(j = 0; j < 528; j++){
        for(i = 0; i < 704; i++){
            image1.at<cv::Vec3b>(j,i)[0] = mask_image.at<cv::Vec3b>(j,i)[0]*im_in1.at<cv::Vec3b>(j,i)[0];
            image1.at<cv::Vec3b>(j,i)[1] = mask_image.at<cv::Vec3b>(j,i)[1]*im_in1.at<cv::Vec3b>(j,i)[1];
            image1.at<cv::Vec3b>(j,i)[2] = mask_image.at<cv::Vec3b>(j,i)[2]*im_in1.at<cv::Vec3b>(j,i)[2];
        }
    }
}

void Image2(cv::Mat im_in2,cv::Mat mask_image,cv::Mat image2){

    int i,j;
    for(j = 0; j < 528; j++){
        for(i = 0; i < 704; i++){
            image2.at<cv::Vec3b>(j,i)[0] = (mask_image.at<cv::Vec3b>(j,i)[0]^1)*im_in2.at<cv::Vec3b>(j,i)[0];
            image2.at<cv::Vec3b>(j,i)[1] = (mask_image.at<cv::Vec3b>(j,i)[1]^1)*im_in2.at<cv::Vec3b>(j,i)[1];
            image2.at<cv::Vec3b>(j,i)[2] = (mask_image.at<cv::Vec3b>(j,i)[2]^1)*im_in2.at<cv::Vec3b>(j,i)[2];
        }
    }
}

void Comp(cv::Mat image1,cv::Mat image2,cv::Mat composite_image){

    int i,j;
    for(j = 0; j < 528; j++){
        for(i = 0; i < 704; i++){
            composite_image.at<cv::Vec3b>(j,i)[0] = image1.at<cv::Vec3b>(j,i)[0] + image2.at<cv::Vec3b>(j,i)[0];
            composite_image.at<cv::Vec3b>(j,i)[1] = image1.at<cv::Vec3b>(j,i)[1] + image2.at<cv::Vec3b>(j,i)[1];
            composite_image.at<cv::Vec3b>(j,i)[2] = image1.at<cv::Vec3b>(j,i)[2] + image2.at<cv::Vec3b>(j,i)[2];
        }
    }
}