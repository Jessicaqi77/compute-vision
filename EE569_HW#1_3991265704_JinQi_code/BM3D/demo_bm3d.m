y = im2double(imread('BM3D_images/House.png'));
z = im2double(imread('BM3D_images/House_noisy.png'));
[PSNR, y_est] = BM3D(y, z, 25);