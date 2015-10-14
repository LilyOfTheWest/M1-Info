%-----------------------------------------------------
% UE Traitement d'Image M1 Info
% TP2 programme TP_Segment.m
% Objectifs :
%  - Segmentation d'une image par recherche de seuils à partir de
%  l'histogramme
%       . Image en niveaux de gris
%       . Segmentation par seuillage
%------------------------------------------------------


clear all;
close all;

%------------------------------------------------
%Rajouter le path de votre répertoire Utils
%------------------------------------------------
addpath ('..\Utils')

%------------------------------------------------
%Nom du répertoire des images JPG
%------------------------------------------------
 dir_ima='..\Image_jpg';
%dir_ima='.';

%------------------------------------------------
%Nom de l'image choisi
%------------------------------------------------
% nom_ima='liftingbody';
nom_ima='graines';

%------------------------------------------------
%Mode pour le remplissage des valeurs en niveaux de gris après la segmentation 
%l'un ou l'autre des deux modes
%------------------------------------------------
mode = 'mean_gray';   %valeur moyenne des niveaux de gris après seuillage
% mode = 'threshold'; %valeur millieu des seuils 


%------------------------------------------------
%Choisir le nombre de classes
%------------------------------------------------
nbr_class = input('Nombre de classes : '); 


%------------------------------------------------
%Chargement de l'image
%------------------------------------------------
pic         = imread([dir_ima '\' nom_ima '.jpg']); 
nbr_bin     = 256;
[histo,bin] = imhist(pic,nbr_bin);
nbpix       = sum(histo);

%Affichage
n1 = figure;
subplot(1,2,1)
image(pic)
colormap(gray(256))
axis equal
axis off
subplot(1,2,2)
plot(bin,histo);
grid on
xlabel('Niveau de gris')
ylabel('Effectif')

%------------------------------------------------
%Segmentation 
%------------------------------------------------
[segmented_pic,v_threshold] = segmentation_sol(pic,nbr_class, mode); 
[seg_histo,seg_bin]         = imhist(segmented_pic, nbr_bin);

%------------------------------------------------
%Affichage
%------------------------------------------------
figure
subplot(1,2,1)
image(segmented_pic)
colormap(gray(256))
axis equal
axis off
title([int2str(nbr_class) ' classes'])
subplot(1,2,2)
plot(seg_bin,seg_histo);
hold on
for k = 1 : length(v_threshold)
    plot(v_threshold(k)*[1 1], [0 nbpix/20], 'r-')
end
grid on
xlabel('Niveau de gris')
ylabel('Effectif')

figure(n1)
subplot(1,2,2)
hold on
for k = 1 : length(v_threshold)
    plot(v_threshold(k)*[1 1], [0 nbpix/50], 'r-')
end

%------------------------------------------------
%------A FAIRE-----------------------------------
%La classe la plus fréquente  : en rouge
%Ecrire votre code
%Utiliser la manipulation des tables de couleurs

%La classe la plus fréquente  : en rouge
%Ecrire votre code
%Utiliser la manipulation des tables de couleurs
