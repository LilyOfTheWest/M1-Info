% TP 4 Détection de contours
% Approche par convolution directe
% 
% M1 info
%

clear all;
close all;

%Rajouter le path de votre répertoire Utils
addpath ('..\Utils')

%Nom du répertoire des images JPG
dir_ima='..\Image_jpg';

%Nom de l'image choisi
nom_ima='graines';

%lecture de l'image
pic=imread([dir_ima '\' nom_ima '.jpg' ]); 



if size(pic(1,1)) == 3
    pic = double(pic);
    pic = 0.299*pic(:,:,1)+0.587*pic(:,:,2)+0.114*pic(:,:,3);
else
    pic = pic(4:end-5,4:end-5,1);
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%1.1 DIFFERENCES FINIES SIMPLES
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


fprintf('\n[1.1]. Roberts differential ... \n');

% Sobel differential
[pic_x_roberts,pic_y_roberts,pic_norm_roberts] = roberts_differential(pic); %function to complete
figure
draw_gradient_picture(pic_x_roberts,pic_y_roberts,pic_norm_roberts,pic);
title('Roberts')
pause;



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%1.2 FILTRES DE SOBEL
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


fprintf('\n[1.2]. Sobel differential without noise ... \n');

% Sobel differential
[pic_x_sobel,pic_y_sobel,pic_norm_sobel] = sobel_differential(pic); %function to complete
figure
draw_gradient_picture(pic_x_sobel,pic_y_sobel,pic_norm_sobel,pic);
title('Sobel')
pause;



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%1.3 Action du bruit
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fprintf('\n[1.3]. Add gaussian noise ... \n');

%signal to noise ratio in dB
rsb = 10;

%build noisy picture
pic_noisy = add_gaussian_noise(pic,rsb);

%get gradient
[pic_x_roberts_noisy,pic_y_roberts_noisy,pic_norm_roberts_noisy] = roberts_differential(pic_noisy);
[pic_x_sobel_noisy,pic_y_sobel_noisy,pic_norm_sobel_noisy] = sobel_differential(pic_noisy);


%draw
figure;
draw_gradient_picture(pic_x_roberts_noisy,pic_y_roberts_noisy,pic_norm_roberts_noisy,pic_noisy);
title('Roberts + bruit')

figure;
draw_gradient_picture(pic_x_sobel_noisy,pic_y_sobel_noisy,pic_norm_sobel_noisy,pic_noisy);
title('Sobel + bruit')

pause;



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%2.1 Maximum Locaux 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fprintf('\n[2.1]. Keep only local maximum ...\n');


d=1;%distance of neighboors
pic_maxima_roberts = keep_local_maxima(pic_x_roberts,pic_y_roberts,d, 'bilinear');
pic_maxima_sobel = keep_local_maxima(pic_x_sobel,pic_y_sobel,d, 'bilinear');

%draw
figure
draw_maxima_picture(pic,pic_norm_roberts,pic_maxima_roberts);
title('Roberts + maxima locaux')

figure
draw_maxima_picture(pic,pic_norm_sobel,pic_maxima_sobel);
title('Sobel + maxima locaux')


pause


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%2.2 Chainage 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fprintf('\n[2.2]. Linkage ...\n');


%hysteresis segmentation
[pic_edges, is_pic_edges] = hysteresis_segmentation(pic_maxima_roberts.*pic_norm_roberts);
pic_edges2 = pic_edges;
pic_edges_link_roberts = link_picture(pic_edges, is_pic_edges); %function to complete
pic_diff_rob = pic_edges_link_roberts - pic_edges2;

[pic_edges, is_pic_edges] = hysteresis_segmentation(pic_maxima_sobel.*pic_norm_sobel);
pic_edges2 = pic_edges;
pic_edges_link_sobel = link_picture(pic_edges, is_pic_edges); %function to complete
pic_diff_sobel = pic_edges_link_sobel - pic_edges2;

%draw
figure
draw_edges(pic,pic_edges_link_roberts);
title('Roberts + chaînage')

figure;
draw_edges(pic, pic_diff_rob);
title('Différence Roberts + chaînage')

figure
draw_edges(pic,pic_edges_link_sobel);
title('Sobel + chaînage')

figure;
draw_edges(pic, pic_diff_sobel);
title('Différence Sobel + chaînage')

pause;



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%2.3 Add Noise 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


fprintf('\n[2.3]. Roberts differential with noise ... \n\n\n');


%get local maxima and segment
pic_maxima_roberts_noisy = keep_local_maxima(pic_x_roberts_noisy,pic_y_roberts_noisy,d, 'nearest');
%hysteresis segmentation
[pic_edges, is_pic_edges] = hysteresis_segmentation(pic_maxima_roberts_noisy.*pic_norm_roberts_noisy);
pic_edges2 = pic_edges;
pic_edges_link_roberts_noisy = link_picture(pic_edges, is_pic_edges); %function to complete
pic_diff = pic_edges_link_roberts_noisy - pic_edges2;

%draw
figure;
draw_gradient_picture(pic_x_roberts_noisy,pic_y_roberts_noisy,pic_norm_roberts_noisy,pic_noisy);
title('Roberts + gradient +bruit')

figure
draw_maxima_picture(pic,pic_norm_roberts_noisy,pic_maxima_roberts_noisy);
title('Roberts + maxima locaux + bruit')

figure;
draw_edges(pic,pic_edges_link_roberts_noisy);
title('Roberts + chaînage + bruit')

figure;
draw_edges(pic, pic_diff);
title('Différence Roberts + chaînage + bruit')


pause;

fprintf('\n[2.4]. Sobel differential with noise ... \n\n\n');


%get local maxima and segment
pic_maxima_sobel_noisy = keep_local_maxima(pic_x_sobel_noisy,pic_y_sobel_noisy,d, 'nearest');
%hysteresis segmentation
[pic_edges, is_pic_edges] = hysteresis_segmentation(pic_maxima_sobel_noisy.*pic_norm_sobel_noisy);
pic_edges2 = pic_edges;
pic_edges_link_sobel_noisy = link_picture(pic_edges, is_pic_edges); %function to complete
pic_diff = pic_edges_link_sobel_noisy - pic_edges2;
%draw
figure;
draw_gradient_picture(pic_x_sobel_noisy,pic_y_sobel_noisy,pic_norm_sobel_noisy,pic_noisy);
title('Sobel + gradient +bruit')

figure
draw_maxima_picture(pic,pic_norm_sobel_noisy,pic_maxima_sobel_noisy);
title('Sobel + maxima locaux + bruit')

figure;
draw_edges(pic,pic_edges_link_sobel_noisy);
title('Sobel + chaînage + bruit')

figure;
draw_edges(pic, pic_diff);
title('Différence Sobel + chaînage + bruit')






