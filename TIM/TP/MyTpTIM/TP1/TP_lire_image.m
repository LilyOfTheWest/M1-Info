%-----------------------------------------------------
% UE Traitement d'Images M1 Info
% TP1 , programme TP_lire_image.m
% Objectifs :
%  -Découvrir Matlab
%  - Premières manipulations d'une image
%------------------------------------------------------

%Fermer toutes les figures et vider la mémoire
close all
clear

%Le répertoire où se trouve les images est le répertoire de travail
dir_ima='./Image_jpg';

%Nom de l'image choisi
fic_ima=[dir_ima '\' 'image_a.pgm'];

%lecture de l'image
ima = imread(fic_ima);

%Affichage avec "plot"
n1=figure;
image(ima)
colormap(gray(256))
axis 'equal'
axis 'off'
title('image originale')

%taille de l'image

[lig, col] = size(ima);
fprintf('Nombre de lignes   : %d\n', lig)
fprintf('Nombre de colonnes : %d\n', col)
disp('Pause : Taille de l''image')
pause

%maxi et min
valMin = min(min(ima));
valMax = max(max(ima));
fprintf('Valeur minimale : %d\n', valMin)
fprintf('Valeur maximale : %d\n', valMax)
disp('Pause : valeurs du maximum et minimum')
pause

%Quelle la valeur de niveau de gris du pixels à la ligne 25 et et la colonne 82 ?
%------------------ecrire et completer l'instruction----------------------%
valPix = ima(25,82);
%------------------------------------------------------------------------%

fprintf('Valeur du pixel (25, 82) : %d\n', valPix)
disp('Pause : niveau de gris du pixel ligne 25 et colonne 82') 
pause


%Affichage du profil de niveau de gris sur la ligne 25 et sur la colonne 82 
numLig = 25; 
numCol = 82;

%-----------------ecrire et completer les instructions-------------------%
oneLig = ima(numLig, :);
oneCol = ima( :, numCol);
%------------------------------------------------------------------------%


%Affichage des 2 profils
figure
plot(oneLig, 'r-')
hold on
plot(oneCol, 'g-')
grid on
legend(['ligne' int2str(numLig)], ['colonne' int2str(numCol)])

figure(n1)
hold on
plot((1:col), numLig*ones(col), 'r-')
plot(numCol*ones(lig), (1:lig), 'g-')

disp(['Pause : profil des des niveaux de gris sur la ligne ' int2str(numLig) ' et sur la colonne ' int2str(numCol)])
pause


%Transformation de l'image
imaOut =uint8(255*(ima > 200));


%Affichage avec 'subplot'
n2 = figure;
subplot(1,2,1)
image(ima)
colormap(gray(256))
axis 'equal'
axis 'off'
title('image originale')
subplot(1,2,2)
image(imaOut)
colormap(gray(256))
axis 'equal'
axis 'off'
title('image transformée')

disp('Binarisation de l''image : quelle est la valeur du seuil ?')


