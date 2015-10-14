function ima_out= fimacrop(ima_in, centre, width, height)
%function ima_out= fimacrop(ima, centre, width, height)
% Extraction d'un sous image de taille 'width' x 'height' de centre 'centre'
% premiere composantre de centre : position en ligne
% deuxième composantre de centre : position en colonne

[lig, col, z]=size(ima_in);
half_width=fix(width/2);
half_height=fix(height/2);


ima_out=ima_in(1+centre(1)-half_height : centre(1)-half_height+height,:,:);
ima_out=ima_out(:, 1+centre(2)-half_width : centre(2)-half_width+width,:,:);



