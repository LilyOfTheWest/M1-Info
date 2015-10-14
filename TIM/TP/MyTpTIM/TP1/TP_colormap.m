%-----------------------------------------------------
% UE Traitement d'Images M1 Info
% TP1 programme TP_colormap.m
% Objectifs :
%  - Passage en niveau de gris
%  - Manipulation d'une table de couleurs
%------------------------------------------------------

%Fermer toutes les figures et vider la mémoire
close all
clear

%Nom du répertoire des images JPG
dir_ima='..\Image_jpg';

%Nom de l'image choisi
nomIma='ville02032';

%lecture de l'image
ima=imread([dir_ima '\' nomIma '.JPG']);

%maxima, minima
max(max(ima(:,:,1)))
max(max(ima(:,:,2)))
max(max(ima(:,:,3)))
min(min(ima(:,:,1)))
min(min(ima(:,:,2)))
min(min(ima(:,:,3)))

%image en niveau de gris
imaGris = 0.299*ima(:,:,1)+0.587*ima(:,:,2)+0.114*ima(:,:,3);

n1=figure;
subplot(1,2,1)
image(ima)
axis 'equal'
axis 'off'
title('image originale')
subplot(1,2,2)
image(imaGris)
colormap(gray(256))
gray(256)
axis 'equal'
axis 'off'
title('image en niveau de gris')

%comprendre l'instruction colormap
%lire la table des couleurs utilisée avec l'instruction colormap
%expliquer la séquence suivante d'instructions 
n2=figure;
colormap(gray(256))
map = colormap
colormap(gray(64))
map = colormap


%Afficher l'image en niveau de gris avec 32 niveaux de gris
nbGris = 32;
pause

figure(n2)
colormap(gray(nbGris));
map = colormap
image(imaGris/(255/nbGris-1))
axis 'equal'
axis 'off'
title(['image en ' int2str(nbGris) ' niveau de gris'])

