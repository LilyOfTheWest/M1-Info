function draw_maxima_picture(pic,pic_norm,pic_maxima)
%function draw_maxima_picture(pic,pic_norm,pic_maxima)
%
% Draw Local maximum of the gradient norm
% 
% INTPUT:
%         pic: original picture
%         pic_norm: norm of the gradient
%         pic_maxima: local maxima of the gradient
%
%


colormap(gray(256));

pic = uint8(pic);
pic_norm = uint8( 256*(pic_norm-min(pic_norm(:)))/(max(pic_norm(:))-min(pic_norm(:))) );
pic_maxima = uint8( 256*(pic_maxima-min(pic_maxima(:)))/(max(pic_maxima(:))-min(pic_maxima(:))) );


subplot(2,2,1);
image(pic);
title('original picture');
axis equal
axis off

subplot(2,2,2);
image(pic_norm);
title('norm of the gradient');
axis equal
axis off

subplot(2,2,[3,4]);
image(pic_maxima);
title('Local maxima');
axis equal
axis off