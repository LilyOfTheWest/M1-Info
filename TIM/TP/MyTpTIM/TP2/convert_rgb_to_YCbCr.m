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

pic_YCbCr = reshape(double(pic_rgb)./255,[],3)*M;
pic_YCbCr = reshape(pic_YCbCr,size(pic_rgb));
% pic_YCbCr = pic_rgb;
% 
% pic_YCbCr = double(pic_YCbCr);
% pic_YCbCr = pic_YCbCr./255;
% 
% for i=1 :N_x
%     for j=1 :N_y
%         pic_YCbCr(i,j,1) = pic_rgb(i,j,1)*M(1,1) + pic_rgb(i,j,2)*M(1,2)+pic_rgb(i,j,3)*M(1,3);
%         pic_YCbCr(i,j,2) = pic_rgb(i,j,1)*M(2,1) + pic_rgb(i,j,2)*M(2,2)+pic_rgb(i,j,3)*M(2,3)+128;
%         pic_YCbCr(i,j,3) = pic_rgb(i,j,1)*M(3,1) + pic_rgb(i,j,2)*M(3,2)+pic_rgb(i,j,3)*M(3,3)+128;
%     end
% end

%</TO DO>

