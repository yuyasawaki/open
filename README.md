# Chroma-Key
<details>
### 各ディレクトリの説明
build：全プログラムの実行型を格納するディレクトリ

image：処理対象の画像を格納するディレクトリ

result：実験結果を格納するディレクトリ

src：プログラムを格納するディレクトリ

### 作成したプログラムの説明
【Chroma-Key.cpp】

入力：rila.bmp  galaxy.jpg

出力：「rila.bmp」と「galaxy.jpg」をクロマキー合成した画像

内容：クロマキー合成をおこなうプログラム


【compile.sh】

ターミナル上で「bash src/compile.sh」と打つと「Chroma-Key.cpp」が実行される。
<\details>

# Data-Augmentation
画像処理をおこなうプログラムです
### 各ディレクトリの説明
※「Chroma-Key」を参照

### 作成したプログラムの説明
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


# Labeling
画像中の対象物をラベリングするプログラムです。
### 各ディレクトリの説明
※「Chroma-Key」を参照

### 作成したプログラムの説明



# Pseudo-Colorimage
疑似カラー画像を作成するプログラムです
### 各ディレクトリの説明
※「Chroma-Key」を参照

### 作成したプログラムの説明
