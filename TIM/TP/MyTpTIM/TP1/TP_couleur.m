%-----------------------------------------------------
% UE Traitement d'Images M1 Info
% TP1 programme TP_couleur.m
% Objectifs :
%  -D�couvrir Matlab
%  - Premi�res manipulations d'une image
%       . Tableau image en m�moire, codage des intensit�s et des couleurs
%       . Transformation de couleurs en niveaux de gris
%       . Effet d'inverse vid�o
%------------------------------------------------------

%Fermer toutes les figures et vider la m�moire
close all
clear

%Nom du r�pertoire des images JPG
dirIma='..\Image_jpg';

%Nom de l'image choisi
nomIma='ville02032';

%lecture de l'image
ima=imread([dirIma '\' nomIma '.JPG']);

%Affichage avec "plot"
n1=figure;
subplot(1,2,1)
image(ima)
axis 'equal'
axis 'off'
title('image couleur')

%taille de l'image
size(ima)

%retirer 16 pixels en haut et en bas, � droite et � gauche
ima = ima(17:end-16, :,:);
ima = ima(:, 17:end-16,:);

%v�rifier que l'image est � la bonne taille
taille = size(ima)

%poursuivre l'affichage
figure(n1)
subplot(1,2,2)
image(ima)
axis 'equal'
axis 'off'
title('image couleur sans les bords')

%maxima, minima
max(max(ima(:,:,1)))
max(max(ima(:,:,2)))
max(max(ima(:,:,3)))
min(min(ima(:,:,1)))
min(min(ima(:,:,2)))
min(min(ima(:,:,3)))

%image en niveau de gris
%On rappelle l'�quation de la luminance : Luminance = 0.299*Rouge+0.587*Vert+0.114*Bleu;
%On applique cette �quation pour trouver l'image en niveau de gris, variable : ima_gris

imaGris = 0.299*ima(:,:,1)+0.587*ima(:,:,2)+0.114*ima(:,:,3);

n2=figure;
image(imaGris)
colormap(gray(256))
axis 'equal'
axis 'off'

%-----------------ecrire et completer les instructions-------------------%
%Mettre en inverse vid�o pour l'image couleur et pour l'image en niveaux de gris
imaGrisInverse = 255-imaGris;
imaInverse     = 255-ima;
%-------------------------------------------------------------------------%

disp('Pause : Ecrire les �quations pour passer en vid�o inverse')
pause

%Affichage 
%Expliquer les inversions de couleurs
n3=figure;
subplot(2,2,1)
image(ima)
axis 'equal'
axis 'off'
title('image couleur')
subplot(2,2,2)
image(imaInverse)
axis 'equal'
axis 'off'
title('image inverse vid�o')
subplot(2,2,3)
image(imaGris)
axis 'equal'
axis 'off'
colormap(gray(256))
title('image gris')
subplot(2,2,4)
image(imaGrisInverse)
axis 'equal'
axis 'off'
colormap(gray(256))
title('image inverse vid�o')

