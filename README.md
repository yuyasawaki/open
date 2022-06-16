# Chroma-Key

<details>
 <summary>各ディレクトリの説明</summary>

build：全プログラムの実行型を格納するディレクトリ

image：処理対象の画像を格納するディレクトリ

result：実験結果を格納するディレクトリ

src：プログラムを格納するディレクトリ
</details>

<details>
 <summary>作成したプログラムの説明</summary>
【Chroma-Key.cpp】

入力：rila.bmp  galaxy.jpg

出力：「rila.bmp」と「galaxy.jpg」をクロマキー合成した画像

内容：クロマキー合成をおこなうプログラム


【compile.sh】

ターミナル上で「bash src/compile.sh」と打つと「Chroma-Key.cpp」が実行される。
</details>

# Data-Augmentation
画像処理をおこなうプログラムです

<details>
 <summary>各ディレクトリの説明</summary>
※「Chroma-Key」を参照
</details>

<details>
 <summary>作成したプログラムの説明</summary>
【Blur.cpp】

入力：img000.bmp

出力：「img000.bmp」をぼやかした画像

内容：入力した画像に平均化フィルタをかけるプログラム

【Gain.cpp】

入力：img000.bmp

出力：「img000.bmp」をぼやかした画像

内容：入力した画像に平均化フィルタをかけるプログラム

【Offset.cpp】

入力：img000.bmp

出力：「img000.bmp」のオフセットを変化させた画像

内容：入力した画像のオフセットを変更した画像を出力するプログラム

【RandNoize.cpp】

入力：img000.bmp

出力：「img000.bmp」にガウシアンノイズを付与した画像

内容：入力した画像にガウシアンノイズを付与するプログラム

【Rotate.cpp】

入力：img000.bmp

出力：「img000.bmp」を回転させた画像

内容：入力した画像を回転させた画像を出力するプログラム

【__DA.sh】

上記のプログラムの実行方法をまとめたbashファイル

【__compile.sh】

ターミナル上で「bash src/__compile.sh <コマンドライン引数>」を実行することで
上記のいずれかのプログラムを実行できる。
</details>

# Labeling
画像中の対象物をラベリングするプログラムです。
<details>
 <summary>各ディレクトリの説明</summary>
 ※「Chroma-Key」を参照
</details>
  
<details> 
 <summary>作成したプログラムの説明</summary>
 
【labeling.cpp】

入力：spiral-003.bmp

出力：「img000.bmp」をラベリングした画像

内容：入力した画像のラベリングをおこなうプログラムです。
 
【compile.sh】
 
 ターミナル上で「bash src/compile.sh」と打つと「labeling.cpp」が実行される。
</details>


# Pseudo-Colorimage
疑似カラー画像を作成するプログラムです

<details>
 <summary>各ディレクトリの説明</summary>
※「Chroma-Key」を参照
</details>

<details>
 <summary>作成したプログラムの説明</summary>
 
 【pcolor.cpp】

入力：Lenna256x256.bmp

出力：「Lenna256x256.bmp」を擬似カラー化した画像

内容：入力した画像を擬似カラー化するプログラムです。
 
【compile.sh】
 
 ターミナル上で「bash src/compile.sh」と打つと「pcolor.cpp」が実行される。
</details>
 
 # 色認識を用いた神経衰弱ゲームの開発
<https://www.youtube.com/watch?v=aDYHnTLiALw>
