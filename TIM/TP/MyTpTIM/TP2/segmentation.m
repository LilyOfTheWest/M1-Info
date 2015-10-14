function [segmented_pic,v_threshold] = segmentation(pic,nbr_class, mode)
%function segmented_pic = segmentation(pic,nbr_class, mode)
%
%
% Segment the picture in nbr_class classes based on the histogram
% 
% INPUT: 
%       pic           : original picture in uint8
%       nbr_class     : number of classes
%       mode          : 'threshold' or 'mean_gray' : how to fill the segmented picture 
%                     : - threshold : the gray level in a region is the
%                     middle of the two thrsholds
%                     : - mean_gray : the gray level is the mean gray of
%                     the pixels in the region
% OUTPUT:
%       segmented_picture  : segmented picture
%       v_threshold        : the limits of each segments
%
%

pic = uint8(pic);

%take histogram
histo = imhist(pic,256);

%vector of threshold
v_threshold = floor(linspace(0,255,nbr_class-1));
%memory vector
v_threshold_previous = zeros(size(v_threshold));

%number of pixels in a section
N = zeros(1,nbr_class);
%average of the section
M = zeros(1,nbr_class);


n_iter=0;
MAX_ITER = 200;%security

%iteration until convergence
while(norm(v_threshold_previous-v_threshold)~=0 && n_iter<MAX_ITER)

    %swap memory
    v_threshold_previous = v_threshold;
    
    %extend to get correct boundaries
    extended_threshold = [0,v_threshold,256];
    
    %loop on every sections
    for(k=1:nbr_class)

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
vect_pic = pic(:);

switch lower(mode(1:4))
    case 'thre'
        for k=1:nbr_class
            
%-----A FAIRE---------------------------
%Caculer ici le niveau level pour les pixels de cette classe
%Nom de la variable 'level'
            level =(v_threshold(k) + v_threshold(k+1))/2;
            %get pixture
            segmented_pic = segmented_pic + level*((pic>=v_threshold(k)) .* (pic<v_threshold(k+1)));
        end

    case 'mean'
        for k=1:nbr_class
            
%-----A FAIRE---------------------------
%Caculer ici le niveau level pour les pixels de cette classe
%Nom de la variable 'level'
            if(N(k)~=0)
                current_X = [v_threshold(k):v_threshold(k+1)-1]';
                h2=histo(current_X+1);
                level = h2'*current_X/N(k);
            else
                level = 0; 
            end
            %get pixture
            segmented_pic = segmented_pic + level*((pic>=v_threshold(k)) .* (pic<v_threshold(k+1)));
        end
end

%convert to uint8
segmented_pic = uint8(segmented_pic);
