%-----------------------------------------------------
% UE Traitement d'Image M1 Info
% TP3 programme TP_reduction_bruit.m
% Objectifs :
%  - Réduction de bruit dans une image
%  - Bruit additif
%  - Filtres gaussiens
%------------------------------------------------------

%Fermer toutes les figures et vider la mémoire
close all
clear

%Rajouter le path de votre répertoire Utils
addpath ('..\Utils')

%Nom du répertoire des images JPG
dir_ima='..\Image_jpg';

%Nom de l'image choisi
nom_ima='ville02032';

%lecture de l'image
ima=imread([dir_ima '\' nom_ima '.jpg' ]); 

%image en niveau de gris
ima_gris = double(0.299*ima(:,:,1)+0.587*ima(:,:,2)+0.114*ima(:,:,3));

%---------------------------------------
%CALCULER LA VARIANCE DES NIVEAUX DE GRIS SUR IMA_GRIS
%variance des niveaux de gris dans l'image 
%var_ima=....... 
var_ima = var(ima_gris(:));

%FIXER LA VARIANCE DU BRUIT
%Paramètrage du niveau de bruit
%rsb=..... %en dB entre 10 et 20
%var_b= .......
rsb=10;
var_b=var_ima/(10*(rsb/10));
%----------------------
%FORMER l'IMAGE BRUITEE
%Bruit gaussien additif
%bruit= ................;
bruit=randn(size(ima_gris))*sqrt(var_b);

%Génération de l'image bruitée
%ima_bruit= ..................;
ima_bruit=ima_gris+bruit;

%AFFICHAGE 
figure
subplot(1,2,1)
image(ima_gris)
axis 'equal'
axis 'off'
title('image originale')
subplot(1,2,2)
image(ima_bruit)
colormap(gray(256))
axis 'equal'
axis 'off'
title(['image bruitée ; ' num2str(var_b)])

disp('Pause : Réduction de bruit par filtrage')
pause

%On considèrera 3 tailles de noyaux de filtrage : 3x3, 5x5, 7x7
taille_kernel=[3 5 7];

%Initialisation de variable si nécessaire pour la génération du filtre
%binomial
%.....
for i=1:length(taille_kernel)
    
    %Convolution avec le filtre moyenne
    %-------------------------------------------------------------
    %FORMER LE NOYAU DU FILTRE MOYENNE ET EFFECTUER LA CONVOLUTION
    % kernel_moy=.........................;
    kernel_moy=ones(taille_kernel(i)).*(1/power(taille_kernel(i),2));
    % ima_moy=............................;
    ima_moy=conv2(ima_bruit,kernel_moy, 'same');
    %Convolution avec le filtre gaussien
    %----------------------------------------------------------------------
    %FORMER RECURSIVEMENT LE NOYAU DU FILTRE GAUSS ET EFFECTUER LA CONVOLUTION
    % kernel_gauss = ...........................;
    kernel_gauss = [1 1];
    for j=1:taille_kernel(i)-2
        kernel_gauss = conv2(kernel_gauss, [1 1]);
        
    end
    kernel_gauss=kernel_gauss'*kernel_gauss;
    kernel_gauss = kernel_gauss.*(1/(sum(sum(kernel_gauss))));
%Rmq : Vérifier que la somme des coefficients des noyaux est égale à 1

    % ima_gauss=..........................;
    ima_gauss=conv2(ima_bruit,kernel_gauss, 'same'); 
%AFFICHAGE  
    figure
    subplot(1,2,1)
    image(ima_gris)
    axis 'equal'
    axis 'off'
    title('image originale')
    subplot(1,2,2)
    image(ima_moy)
    colormap(gray(256))
    axis 'equal'
    axis 'off'
    title(['filtre moyenne ' num2str(taille_kernel(i))])

    figure
    subplot(1,2,1)
    image(ima_gris)
    axis 'equal'
    axis 'off'
    title('image originale')
    subplot(1,2,2)
    image(ima_gauss)
    colormap(gray(256))
    axis 'equal'
    axis 'off'
    title(['filtre Gauss ' num2str(taille_kernel(i))])


    figure
    subplot(2,3,1)
    image(ima_moy)
    axis 'equal'
    axis 'off'
    title(['filtre moyenne ' num2str(taille_kernel(i))])
    subplot(2,3,2)
    image(abs(ima_gris-ima_moy))
    colormap(gray(256))
    axis 'equal'
    axis 'off'
    title(['différence image moyenne'])    
    
    subplot(2,3,4)
    image(ima_gauss)
    axis 'equal'
    axis 'off'
    title(['filtre Gauss ' num2str(taille_kernel(i))])
    subplot(2,3,5)
    image(abs(ima_gris-ima_gauss))
    colormap(gray(256))
    axis 'equal'
    axis 'off'
    title(['différence image gauss'])    
    subplot(2,3,6)
    imagesc(abs(ima_moy-ima_gauss))
    colormap(gray(256))
    colorbar
    axis 'equal'
    axis 'off'
    title(['différence moy gauss'])    
    
    disp(['Taille Noyau ' int2str(taille_kernel(i))])
    pause
end    
    
    
    
    
