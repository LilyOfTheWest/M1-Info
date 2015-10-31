function pic_rgb = convert_YCbCr_to_rgb(pic_YCbCr)
%function pic_rgb = convert_YCbCr_to_rgb(pic_YCbCr)
%
%
% Perform the change of basis YCbCr -> RGB
%
% INPUT: 
%       pic_YCbCr: picture in YCbCr space (double)
%
% OUTPUT: 
%       pic_rgb: picture in RGB space (uint8)
%
%

M = [ [ 0.299 , 0.587 , 0.114];...
      [-0.168 ,-0.331 , 0.5];...
      [ 0.5 ,-0.4187 ,-0.0813] ];
  
pic_rgb = reshape(double(pic_YCbCr), [], 3)*inv(M);
pic_rgb = reshape(pic_rgb, size(pic_YCbCr));

pic_rgb = pic_rgb.*255;
pic_rgb = uint8(pic_rgb);
% N_x = size(pic_YCbCr,1);
% N_y = size(pic_YCbCr,2);
% pic_rgb = pic_YCbCr;
% 
% 
% for i=1 :N_x
%     for j=1 :N_y
%         pic_rgb(i,j,1) = pic_YCbCr(i,j,1) + 1.402*(pic_YCbCr(i,j,3));
%         pic_rgb(i,j,2) = pic_YCbCr(i,j,1) - 0.34414*(pic_YCbCr(i,j,2))-0.71414*(pic_YCbCr(i,j,3));
%         pic_rgb(i,j,3) = pic_YCbCr(i,j,1) + 1.772*(pic_YCbCr(i,j,2));
%     end
% end
% 
% pic_rgb = pic_rgb.*255;
% pic_rgb = uint8(pic_rgb);

%<TO DO: Inverse Space Conversion YCbCr->RGB>
%
%
%
%</TO DO>