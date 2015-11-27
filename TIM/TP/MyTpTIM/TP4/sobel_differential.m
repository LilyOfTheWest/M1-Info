function [pic_x,pic_y,pic_norm] = sobel_differential(pic)
%function [pic_x,pic_y,pic_norm] = sobel_differential(pic)
%
% Calculate Sobel Filtering
%
%
% INTPUT: 
%         pic: original picture in uint8
% OUTPUT:
%         pic_x: differential in x
%         pic_y: differential in y
%         pic_norm: norm of the gradient
%


pic = double(pic);

S=[1,2,1];
D=[1,0,-1];
Gx=S'*D;
Gy=D'*S;

%<to do !!!!!!!!>
%
% calculer les noyaux de convolution 2D à partir noyaux 1D S(binomial) et D(gradient)
% calculez pic_x, pic_y et la norme du gradient
%
%</to do>
pic_x = conv2(pic, (1/4)*Gx,'same');
pic_y = conv2(pic, (1/4)*Gy, 'same');

pic_norm = sqrt(power(pic_x, 2)+power(pic_y, 2));
