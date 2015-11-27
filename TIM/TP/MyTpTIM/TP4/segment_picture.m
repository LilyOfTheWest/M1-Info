function pic_segmented = segment_picture(pic)
%function pic_segmented = segment_picture(pic)
%
%
% Perform segmentation in two class using histogram clusterization
%
%

[pic_segmented,threshold] = segmentation(pic,2);
pic_segmented = (pic_segmented==threshold(end-1));

