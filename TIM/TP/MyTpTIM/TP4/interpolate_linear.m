function fX = interpolate_linear(X,f)
%function fX = interpolate_linear(X,f)
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




[N_x,N_y] = size(f);

for(k=1:size(X,1))


    x0 = floor(X(k,1));
    y0 = floor(X(k,2));
    x1 = x0+1;
    y1 = y0+1;

    u = X(k,1)-x0;
    v = X(k,2)-y0;
    
    
    if(x0>0 && x0<=N_x && y0>0 && y0<=N_y)
        A = f(x0,y0);
    else
        A=0;
    end
    
    if(x1>0 && x1<=N_x && y0>0 && y0<=N_y)
        B = f(x1,y0);
    else
        B=0;
    end
    
    if(x0>0 && x0<=N_x && y1>0 && y1<=N_y)
        C = f(x0,y1);
    else
        C=0;
    end
    
    if(x1>0 && x1<=N_x && y1>0 && y1<=N_y)
        D = f(x1,y1);
    else
        D=0;
    end
    

    fX(k,1) = A*(1-u)*(1-v) +...
        B*u*(1-v) + ...
        C*(1-u)*v + ...
        D*u*v;

    %fprintf('%d/%d\n',k,size(X,1));
end


