function [pic,new_histo,old_histo,X_histo] = histo_egalisation(original_pic)
%function [pic,new_histo,old_histo] = histo_histo_egalisation(original_pic)
%
%
% Perform pic = 255/nbr_pixel * int_{x=0..p1}(h(x) dx)
%
% INPUT:
%       original_pic : original picture in uint8
%
% OUTPUT: 
%       pic      : picture after histogram equalization
%       new_histo: the new histogram
%       old_histo: the old histogram
%       X_histo  : X value of the histogram (X_histo=[0:255])
%
%

%convert into int8 just in case of double
if(max(original_pic(:))<=1)
    original_pic = original_pic*255;
end
original_pic = uint8(original_pic);

%histogram calculation
[old_histo,X_histo] = imhist(original_pic,256);

%number of pixels
N_x = size(original_pic,1);
N_y = size(original_pic,2);
nbr_pixels = N_x*N_y;


%LUT
lut = 255/nbr_pixels*cumsum(old_histo);

%picture reshape
v_picture = reshape(original_pic,[nbr_pixels,1]);

%equalize and reshape picture
pic = reshape(lut(v_picture+1),[N_x,N_y]); %warning index start at 1

%truncate just in case and convert back to uint8
pic = uint8(max(min(pic,255),0));

%take new histogram
[new_histo,junk] = imhist(pic,256);


