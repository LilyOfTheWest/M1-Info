function [edges_points, is_edges_points] = hysteresis_segmentation(pic_maxima)
%function [edges_points, is_edges_points] = hysteresis_segmentation(pic_maxima)
%
% Perform hysteresis segmentation
%
% INPUT: 
%       pic_maxima: picture of local maxima (values are the gradient norm)
% 
% OUTPUT: 
%       edges_points: segmented edges
%       is_edges_points: segmented candidate edges
%
%



% %get automatique threshold for picture
% [pic_segmented,threshold] = segmentation(pic_maxima,4);
% edges_points = pic_segmented>=threshold(end-3);
% non_edges_points = pic_segmented<=5;
% is_edges_points = ( (pic_segmented>5) & (pic_segmented<threshold(end-3)) );


pic_maxima = 255*(pic_maxima-min(pic_maxima(:)))/(max(pic_maxima(:))-min(pic_maxima(:)));


[pic_segmented,threshold] = segmentation(pic_maxima,2);
higher_threshold = threshold(2);
lower_threshold = threshold(2)/2;


%size
[N_x,N_y] = size(pic_maxima);

edges_points = pic_maxima>=higher_threshold;
is_edges_points = (pic_maxima>lower_threshold) & (pic_maxima<higher_threshold);


