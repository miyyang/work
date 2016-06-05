%% load image
subplot(2,4,1);
rect = imread('Rect2.bmp');
imshow(histeq(rect));
title('原图');

%% checck my ifft2d & my fft2d
subplot(2,4,2);
temp = abs(myifft2d(myfft2d(double(rect))));
imshow(histeq(uint8(temp)));
title('myifft2d(myfft2d(image))的图像');

%% my fft2d
result = myfft2d(double(rect));
result_mag = abs(result);
result_pha = angle(result);
subplot(2,4,3);
temp = fftshift(log(result_mag + 1));
imshow(histeq(uint8(temp)));
title('my rect的幅度谱');
subplot(2,4,4);
temp = abs(myifft2d(result_mag));
temp = histeq(uint16(myconvertf(temp)));
imshow(temp);
title('my 反变换后的幅度谱');
subplot(2,4,5);
temp = 10000 * exp(1i * result_pha);
temp = uint8(myifft2d(temp));
imshow(temp);
title('my 反变换后的相位谱');

%% standard fft2d
result = fft2(rect);
result_mag = abs(result);
result_pha = angle(result);
subplot(2,4,6);
temp = fftshift(log(result_mag + 1));
imshow(histeq(uint8(temp)));
title('standart rect的幅度谱');
subplot(2,4,7);
temp = abs(ifft2(result_mag));
temp = histeq(uint16(myconvertf(temp)));
imshow(temp);
title('standart 反变换后的幅度谱');
subplot(2,4,8);
temp = 10000 * exp(1i * result_pha);
temp = uint8(ifft2(temp));
imshow(temp);
title('standart 反变换后的相位谱');
