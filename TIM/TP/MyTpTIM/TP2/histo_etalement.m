function [pic,new_histo,old_histo,X_histo] = histo_etalement(original_pic,alpha,beta)
%function [pic,new_histo,old_histo] = histo_etalement(original_pic,alpha,beta)
%
% Enlarge picture dynamic
%
% 
%
% INPUT:
%       original_pic : original picture in uint8
%       alpha (>=1)  : a weighted parameter to adjust the maximum
%       of the dynamic
%       beta (>=1)   : a weighted parameter to adjust the minimum
%       of the dynamic (if min>0)
% OUTPUT: 
%       pic      : picture after linearization
%       new_histo: the new histogram
%       old_histo: the old histogram
%       X_histo  : X value of the histogram (X_histo=[0:255])
%
%

%convert into int8 just in case of double
if(max(original_pic(:))<=1)
    original_pic = original_pic*256;
end

original_pic = uint8(original_pic);

%histogram calculation
[old_histo,X_histo] = imhist(original_pic,256);


%convert to double to perform calculation
original_pic = double(original_pic);

%take min and weighted max
pic_min =   beta *min(original_pic(:));
pic_max = 1/alpha*max(original_pic(:));



%enlarge histogram

% <TO DO !!!>
%
% pic = ...
%
% tronquez les valeurs de l'image entre 0 et 255, puis repassez
% l'image en codage sur des entiers uint8 (pensez aux fonctions min
% et max de matlab)
%
% </TO DO>

pic = 255*((original_pic-pic_min)/(pic_max-pic_min));
pic = uint8(max(min(pic,255),0));

%take new histogram
[new_histo,junk] = imhist(pic,256);


