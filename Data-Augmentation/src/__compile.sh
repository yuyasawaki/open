DATA='img000.bmp'

#Blur.cpp
#bash src/__DA.sh 0 image/$DATA 1 

#Gain.cpp
#bash src/__DA.sh 1 image/$DATA 2 

#Offset.cpp
#bash src/__DA.sh 2 image/$DATA 100 -random 

#RandNoize.cpp
#bash src/__DA.sh 3 image/$DATA 10 

#Rotate.cpp
bash src/__DA.sh 4 image/$DATA 90 