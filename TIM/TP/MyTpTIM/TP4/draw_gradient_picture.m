function draw_gradient_picture(pic_x,pic_y,pic_n,pic)
%function draw_gradient_picture(pic_x,pic_y,pic_n,pic)
%
% draw picture of gradient
%
%


colormap(gray(256));

subplot(2,2,1);
pic_x = 255*(pic_x-min(pic_x(:)))/(max(pic_x(:))-min(pic_x(:)));
image(uint8(pic_x));
title('I_x');
axis equal
axis off

subplot(2,2,2);
pic_y = 255*(pic_y-min(pic_y(:)))/(max(pic_y(:))-min(pic_y(:)));
image(uint8(pic_y));
title('I_y');
axis equal
axis off


subplot(2,2,4);
image(pic);
title('picture');
axis equal
axis off

subplot(2,2,3);
pic_n = 255*(pic_n-min(pic_n(:)))/(max(pic_n(:))-min(pic_y(:)));
image(uint8(pic_n));
title('I_n');
axis equal
axis off