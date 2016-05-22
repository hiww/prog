
# -*- coding: utf-8 -*-
import cv2
import numpy as np

#Ipythonで表示用の設定
import matplotlib.pyplot as plt
%matplotlib inline

#画像読込
img_in = cv2.imread("lena.jpg", 0)

#ヒストグラム平坦化
img_equ = cv2.equalizeHist(img_in)


#以下、結果の表示
plt.figure(figsize=(16,8))

#入力画像の表示
plt.subplot(221)
plt.imshow(img_in,cmap='gray')
plt.title('input image')

#入力画像の累積ヒストグラム作成
hist_in,bins_in = np.histogram(img_in.flatten(),256,[0,256])
cdf_in = hist_in.cumsum()
cdf_in_normalized = cdf_in *hist_in.max()/ cdf_in.max()

#入力画像のヒストグラム表示
plt.subplot(222)
plt.plot(cdf_in_normalized, color = 'b')
plt.hist(img_in.flatten(),256,[0,256], color = 'r')
plt.xlim([0,256])
plt.legend(('cdf','histogram'), loc = 'upper left')
plt.title('input image histogram')

#出力画像の表示
plt.subplot(223)
plt.imshow(img_equ,cmap='gray')
plt.title('output image')

#出力画像の累積ヒストグラム作成
hist_equ,bins_equ = np.histogram(img_equ.flatten(),256,[0,256])
cdf_equ = hist_equ.cumsum()
cdf_equ_normalized = cdf_equ *hist_equ.max()/ cdf_equ.max()

#出力画像のヒストグラム表示
plt.subplot(224)
plt.plot(cdf_equ_normalized, color = 'b')
plt.hist(img_equ.flatten(),256,[0,256], color = 'r')
plt.xlim([0,256])
plt.legend(('cdf','histogram'), loc = 'upper left')
plt.title('output image histogram')

plt.show()
