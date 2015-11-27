function pic_maxima = keep_local_maxima(pic_x,pic_y,d, choice)
%function pic_maxima = keep_local_maxima(pic_x,pic_y,d, choice)
%
% INPUT
%       pic_x: differential approximation of the picture in x direction
%       pic_y: differential approximation of the picture in y direction
%       d: distance to compare the local maxima
%       choice : 'bilinear' or 'nearest' for the interpolate procedure
%
% OUTPUT
%       pic_maxima: binary picture, 1 when local maxima of the gradient
%       norm
%                                   0 otherwise
%
%
%


[N_x,N_y] = size(pic_x);

pic_n = (pic_x.*pic_x+pic_y.*pic_y).^(1/2);


%normalization
epsilon = 10^(-8);
pic_x = pic_x./max(pic_n,epsilon); %to avoid dividing by zero
pic_y = pic_y./max(pic_n,epsilon);


%only [x,y] 
v_x = [1:N_x];
v_y = [1:N_y];

%create axis x and y in vector
[xx,yy] = ndgrid(v_x,v_y);


%calculate X, X+d*gradient, X-d*gradient
X = [xx(:),yy(:)];


V  = pic_n(:);

if strcmp(choice, 'bilinear')

V1 = interpolate_linear(X + d*[pic_x(:),pic_y(:)],pic_n);
V2 = interpolate_linear(X - d*[pic_x(:),pic_y(:)],pic_n);
else
V1 = interpolate_nearest(X + d*[pic_x(:),pic_y(:)],pic_n);
V2 = interpolate_nearest(X - d*[pic_x(:),pic_y(:)],pic_n);

end

%set pic_maxima to 1 when there is a maxima
pic_maxima=[];
pic_maxima = (V>V2).*(V>V1);


%resize
pic_maxima = reshape(pic_maxima, N_x, N_y);







