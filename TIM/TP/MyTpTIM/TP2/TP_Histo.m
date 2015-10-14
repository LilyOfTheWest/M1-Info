%-----------------------------------------------------
% UE Traitement d'Image M1 Info
% TP2 programme TP_Histo.m
% Objectifs :
%  - Modification d'histogrammes
%       . Image en niveaux de gris, en couleur
%       . Etalement, Egalisation
%------------------------------------------------------

%effacement mémoire
clear
close all

%Rajouter le path de votre répertoire Utils
addpath ('..\Utils')

%Nom du répertoire des images JPG
dir_ima='..\Image_jpg';

%chargement de l'image

%name_picture = 'lake.jpg';
%name_picture = 'see.jpg'
%name_picture = 'city.jpg';
%name_picture = 'house.jpg';
name_picture = 'venise.jpg';

pic = imread([dir_ima '\' name_picture]);

%image noir et blanc
pic_gray = floor(0.299*pic(:,:,1)+0.587*pic(:,:,2)+0.114*pic(:,:,3));


%facteur d'étirement (à faire varier)
factor_max = 1.5; %fait décroitre le maximum (max/factor_max) 1.5 par défaut
factor_min = 1; %fait accroitre le minimum (si > 1) (min*factor_min) 1 par défaut


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%1. Etalement d'histogramme noir et blanc
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%appel de la fonction d'étalement d'histogramme

% <TO DO:  FONCTION A COMPLETER !!>
[pic_gray_linearized,h,h0] = histo_etalement(pic_gray,factor_max,factor_min);
% </TO DO>


%affichage des résultats
title_fig=('Etalement en niveau de gris');
draw_results_black_and_white(pic_gray_linearized,pic_gray,h,h0, title_fig);

%Etalement
fprintf('\n[1]. Etalement d histogramme noir et blanc ... Pause\n');
pause




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%2. Egalisation d'histogramme noir et blanc
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%close all

%appel de la fonction d'egalisation d'histogramme

[pic_gray_equalized,h,h0] = histo_egalisation(pic_gray);



%affichage des résultats
title_fig=('Egalisation en niveau de gris');
draw_results_black_and_white(pic_gray_equalized,pic_gray,h,h0, title_fig);


%égalisation
fprintf('[2]. Egalisation d histogramme noir et blanc ... Pause\n');
pause



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%3. etirement d'histogramme couleur (RGB naif)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%close all


%appel de la fonction d'étirement d'histogramme
pic_RGB_linearized = uint8(zeros(size(pic)));


% <TO DO:  étirement d'histogramme couleur séparé suivant R,G et B
% à compléter !!>
%
% obtenir pic_RGB_linearized, ainsi que chaque histogramme pour chaque
% composante [h_r,h_g,h_b]
%
%
% </TO DO>


%affichage des résultats
title_fig=('Etalement en R, G, B');
draw_results_color(pic_RGB_linearized,pic,[h_r,h_g,h_b],[h_r0,h_g0,h_b0], title_fig);


%égalisation
fprintf('[3]. Etalement d histogramme couleur ... Pause\n');
pause


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%4. egalisation d'histogramme couleur (RGB naif)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%close all

%appel de la fonction d'egalisation d'histogramme
pic_RGB_equalized = uint8(zeros(size(pic)));


% <TO DO:  égalisation d'histogramme couleur séparé suivant R,G et B
% à compléter !!>
%
% obtenir pic_RGB_equalized, ainsi que chaque histogramme pour chaque
% composante [h_r,h_g,h_b]
%
%
% </TO DO>



%affichage des résultats
title_fig=('Egalisation en R, G, B');
draw_results_color(pic_RGB_equalized,pic,[h_r,h_g,h_b],[h_r0,h_g0,h_b0], title_fig);


%égalisation
fprintf('[4]. Egalisation d histogramme couleur ... Pause\n');
pause


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%5. etirement d'histogramme couleur (changement base => luminosite)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%close all


%<TO DO: Etirement de l'histogramme couleur dans l'espace YCbCr>
% 
% 1. conversion RGB->YCbCr (voir fonction convert_rgb_to_YCbCr)
% 2. étirement d'histogramme sur la coordonnée de luminance
% 3. conversion inverse YCbCr->RGB dans la variable pic_Lum_linearized (voir fonction convert_YCrCb_to_rgb)
%
%</TO DO>

%affichage des résultats
h_r = imhist(pic_Lum_linearized(:,:,1),256); 
h_g = imhist(pic_Lum_linearized(:,:,2),256); 
h_b = imhist(pic_Lum_linearized(:,:,3),256);

title_fig=('Etalement en luminance');
draw_results_color(pic_Lum_linearized,pic,[h_r,h_g,h_b],[h_r0,h_g0,h_b0], title_fig);


%étalement
fprintf('[5]. Etalement d histogramme couleur, changement de base ... Pause\n');
pause



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%6. egalisation d'histogramme couleur (changement base => luminosite)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%close all

%<TO DO: Egalisation de l'histogramme couleur dans l'espace YCbCr>
% 
% 1. conversion RGB->YCbCr (voir fonction convert_rgb_to_YCbCr)
% 2. Egalisation d'histogramme sur la coordonnée de luminance
% 3. conversion inverse YCbCr->RGB dans la variable pic_Lum_equalized (voir fonction convert_YCbCr_to_rgb)
%
%</TO DO>

%affichage des résultats
h_r = imhist(pic_Lum_equalized(:,:,1), 256); 
h_g = imhist(pic_Lum_equalized(:,:,2), 256); 
h_b = imhist(pic_Lum_equalized(:,:,3), 256);
title_fig=('Egalisation en luminance');
draw_results_color(pic_Lum_equalized,pic,[h_r,h_g,h_b],[h_r0,h_g0,h_b0], title_fig);

%égalisation
fprintf('[6]. Egalisation d histogramme couleur, changement de base ... Pause\n');
pause




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%7. Comparaison Couleur
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%étalement et égalisation en R,G, B iu en Luminance
%close all


figure
for k=1:2
    subplot(2,2,k);
    image(pic);
    axis equal
    axis off
    title('Image originale')
end

subplot(2,2,3);
image(pic_RGB_linearized);
axis equal
axis off
title('Image étalée en R, G, B')

subplot(2,2,4);
image(pic_Lum_linearized);
axis equal
axis off
title('Image étalée en Luminance')



figure
for k=1:2
    subplot(2,2,k);
    image(pic);
    axis equal
    axis off
    title('Image originale')
end

subplot(2,2,3);
image(pic_RGB_equalized);
axis equal
axis off
title('Image égalisée en R, G, B')

subplot(2,2,4);
image(pic_Lum_equalized);
axis equal
axis off
title('Image égalisée en Luminance')

fprintf('[7]. Comparaisons\n');




