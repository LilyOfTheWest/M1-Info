function [pic_x,pic_y,pic_norm] = roberts_differential(pic)
%function [pic_x,pic_y,pic_norm] = roberts_differential(pic)
%
% Calculate classical forward finite difference dI/dx = I(x+1,y)-I(x,y)
%                                               dI/dy = I(x,y+1)-I(x,y)
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

%filter definition
D = [1,-1];


%<to do !!!!!!!>
%
% calculer pic_x et pic_y par convolution en utilisant le noyau D
% calculer la norme du gradient
%
%</to do>
pic_x = conv2(pic, D, 'same');
pic_y = conv2(pic, D', 'same');

pic_norm = sqrt(power(pic_x, 2)+power(pic_y, 2));
