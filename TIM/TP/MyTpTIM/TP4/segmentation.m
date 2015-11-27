function [segmented_pic,v_threshold] = segmentation(pic,nbr_threshold)
%function segmented_pic = segmentation(pic,nbr_threshold)
%
%
% Segment the picture in nbr_threshold threshold based on the histogram
% 
% INPUT: 
%       pic           : original picture in uint8
%       nbr_threshold : number of threshold
% OUTPUT:
%       segmented_picture: segmented picture
%       v_threshold        : the limits of each segments
%
%

pic = uint8(pic);

%take histogram
histo = my_imhist(pic,256);

%vector of threshold
v_threshold = floor(linspace(0,255,nbr_threshold-1));
%memory vector
v_threshold_previous = zeros(size(v_threshold));

%number of pixels in a section
N = zeros(1,nbr_threshold);
%average of the section
M = zeros(1,nbr_threshold);


n_iter=0;
MAX_ITER = 200;%security

%iteration until convergence
while(norm(v_threshold_previous-v_threshold)~=0 & n_iter<MAX_ITER)

    %swap memory
    v_threshold_previous = v_threshold;
    
    %extend to get correct boundaries
    extended_threshold = [0,v_threshold,256];
    
    %loop on every sections
    for(k=1:nbr_threshold)

        %get values of this section
        current_X = [extended_threshold(k):extended_threshold(k+1)-1]';
        
        %get histogram of this section
        h = histo(current_X+1);
        
        %get number of pixels of this section
        N(k) = sum(h);
        
        %get average of this section
        if(N(k)~=0)
            M(k) = h'*current_X/N(k);
        else
            M(k) = M(max(k-1,1))+1; 
        end
        
    end
    
    %new threshold are positionned in the middle of the averages
    v_threshold = round((M(1:end-1)+M(2:end))/2);
    
    n_iter= n_iter+1;
end



%calculate thresholded_picture
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


segmented_pic = zeros(size(pic));
v_threshold = [0,v_threshold,256];
for(k=1:nbr_threshold)
    

    %level = (v_threshold(k)+v_threshold(k+1))/2;    %average of value
    level = v_threshold(k);                        %or first value
    %level = floor((k-1)/(nbr_threshold-1)*255);    %or linear segmentation
    
    %get pixture
    segmented_pic = segmented_pic + level*((pic>=v_threshold(k)) .* (pic<v_threshold(k+1)));
end


%convert to uint8
segmented_pic = uint8(segmented_pic);
