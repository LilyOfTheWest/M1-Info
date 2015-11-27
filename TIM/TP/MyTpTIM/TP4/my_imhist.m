function [histo,X] = my_imhist(pic,n)
%function [histo,X] = my_imhist(pic,n)
%
%
% perform histogram calculation
% INPUT: 
%       pic: original gray tone picture in uint8 (or double between [0,1])
%       n  : number of bins
% OUTPUT:
%       histo: histogram
%       X    : gray values
%
%

%convert to uint8 in cas of double
if(isfloat(pic)==1)
  pic = uint(255*min(max(pic,0),1));
end  

%initialize
X = [0:n-1]/(n-1)*255;
histo = zeros(n,1);

%picture size
N_x = size(pic,1);
N_y = size(pic,2);

%loop on every pixels
for(k_x=1:N_x)
  for(k_y=1:N_y)
    
    %index in histogram
    k_histo = floor(double(pic(k_x,k_y))/255*(n-1))+1;
    
    %increment
    histo(k_histo) = histo(k_histo)+1; 
  end
end

%return