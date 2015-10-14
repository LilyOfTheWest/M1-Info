function pic_YCbCr = convert_rgb_to_YCbCr(pic_rgb)
%function pic_YCbCr = convert_rgb_to_YCbCr(pic_rgb)
%
%
% Perform the change of basis RGB-> YCrCb
%
%
% INPUT:
%       pic_rgb: input picture in uint8
%
% OUTPUT:
%       pic_YCbCr: output picture in double
%
%

N_x = size(pic_rgb,1);
N_y = size(pic_rgb,2);
nbr_pixels = N_x*N_y;

%transformation matrix 
M = [ [ 0.299 , 0.587 , 0.114];...
      [-0.168 ,-0.331 , 0.5];...
      [ 0.5 ,-0.4187 ,-0.0813] ];
  
%space conversion
%<TO DO: SPACE Conversion to the picture>
%
%
%
%</TO DO>