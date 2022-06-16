#################################
#bash src/DA.sh mode
#
# mode=0   Blur.cpp
# mode=1   Gain.cpp
# mode=2   Offset.cpp
# mode=3   RandNoize.cpp
# mode=4   Rotate.cpp
#################################


echo "----------parameter----------"
echo " 第1引数:$1"
echo " 第2引数:$2"
echo " 第3引数:$3"
echo " 第4引数:$4"
echo " 第5引数:$5"
echo " 第6引数:$6"
echo " 第7引数:$7"
echo "-----------------------------"


#<Blur>
# -i         :file name of the input image.
# -blur      :set the revel of blur
# -random    :random mode (ON:-random OFF:none)
if [ $1 -eq 0 ];then
	rm result/Blur.txt
	g++ src/Blur.cpp -o build/Blur.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	./build/Blur.out -i $2 -blur $3
fi



#<Gain>
# -i         :file name of the input image.
# -gain      :adjust image gain.
# -random    :random mode (ON:-random OFF:none)
if [ $1 -eq 1 ];then
	rm result/Gain.txt
	g++ src/Gain.cpp -o build/Gain.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	./build/Gain.out -i $2 -gain $3
fi



#<Offset>
# -i         :file name of the input image.
# -offset    :adjust image offset.
# -random    :random mode (ON:-random OFF:none)
if [ $1 -eq 2 ];then
	rm result/Offset.txt
	g++ src/Offset.cpp -o build/Offset.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	./build/Offset.out -i $2 -offset $3 $4
fi



#<Random Noize>
# -i         :file name of the input image.
# -sigma     :sigma of gaussian distribution.
# -random    :random mode. (ON:-random OFF:none)
if [ $1 -eq 3 ];then
	rm result/RandNoize.txt
	g++ src/RandNoize.cpp -o build/RandNoize.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	./build/RandNoize.out -i $2 -sigma $3  
fi



#<Rotate>
# -i         :file name of the input image.
# -random    :random mode (ON:-random OFF:none).
# -color     :color mode
if [ $1 -eq 4 ];then
	rm result/Rotate.txt
	g++ src/Rotate.cpp -o build/Rotate.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
	./build/Rotate.out -i $2 -theta $3 -color
fi
