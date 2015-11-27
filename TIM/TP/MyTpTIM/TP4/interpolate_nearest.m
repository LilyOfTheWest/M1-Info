function fX = my_interpolate_nearest(X,f)
%function fX = my_interpolate_nearest(X,f)
%
%
% nearest interpolation of f to X coordinates
%
%
% INPUT: 
%       X: X abscisse to evaluate the function (vector values [X,Y])
%       f: function values (2D matrix supposed to be defined on [1:N_x,1:N_y])
%
%
% OUTPUT:
%       fX: interpolated values (vector)
%
%


%nearest interpolation

[N_x,N_y] = size(f);

X = round(X);
fX=zeros(size(X,1),1);


X(:,1)=max(min(X(:,1), N_x),1); 
X(:,2)=max(min(X(:,2), N_y),1); 

nb_point=size(X,1);

for i=1:nb_point
    fX(i)=f(X(i,1), X(i,2));
end

