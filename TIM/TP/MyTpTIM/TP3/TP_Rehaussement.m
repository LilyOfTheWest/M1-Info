%-----------------------------------------------------
% UE Traitement d'Image M1 Info
% Année 2013 - 2014
% TP3 programme TP_Rehaussement.m
% Objectifs :
%  - Filtrage Passe Haut
%  - Rehaussement de contraste dans une image
% 
%------------------------------------------------------

%Fermer toutes les figures et vider la mémoire
close all
clear

%Rajouter le path de votre répertoire Utils
addpath ('..\Utils')

%Nom du répertoire des images JPG
dir_ima='..\Image_jpg';

%chargement de l'image

%nom_ima = 'lake.jpg';
%nom_ima = 'see.jpg'
%nom_ima = 'city.jpg';
%nom_ima = 'house.jpg';
nom_ima = 'fillette.jpg';
%nom_ima = 'cameraman.jpg';
%nom_ima = 'graines.jpg';
%nom_ima = 'ex1_passe-haut.jpg';

%lecture de l'image
ima=imread([dir_ima '\' nom_ima ]);

ima = double(ima); 
% Si l'image est en RGB, décommentez la ligne suivante :
%ima = 0.299*ima(:,:,1)+0.587*ima(:,:,2)+0.114*ima(:,:,3);


%dynamique de l'image 
ima_max = max(ima(:))
ima_min = min(ima(:))
ima_moy = mean(ima(:))

sprintf('Image originale, max : %7.2f , min : %7.2f , moy : %7.2f \n',ima_max, ima_min, ima_moy)

%AFFICHAGE 
draw_fig_hist_black_and_white(ima,'image originale')

disp('Pause : Passe Haut ')
pause

%Filtrage Passe Haut 3 x 3
%Image filtée Passe Haut : Image originale - Image filtrée Passe Bas 
%Former le noyau du filtre Passe Haut à partir de son opposé Passe Bas
%--------------- A FAIRE----------------------%
%Ker_PB = .....; 
taille_kernel = 3;
choix_filtre = 1;
if(choix_filtre == 1)
    Ker_PB = [1 1];
    for j=1:taille_kernel-2
        Ker_PB = conv2(Ker_PB, [1 1]);
    end
    Ker_PB=Ker_PB'*Ker_PB;
    Ker_PB = Ker_PB.*(1/(sum(sum(Ker_PB))));
elseif(choix_filtre == 2)
    Ker_PB=ones(taille_kernel).*(1/power(taille_kernel,2));
end
%Ker_PH = ......;
Ker_imp = zeros(taille_kernel, taille_kernel);
Ker_imp((taille_kernel+1)/2, (taille_kernel+1)/2) = 1;
Ker_PH = Ker_imp - Ker_PB;

%Convolution avec l'image
ima_PH = conv2(ima, Ker_PH, 'same'); 

%dynamique de l'image 
ima_PH_max = max(ima_PH(:));
ima_PH_min = min(ima_PH(:));
ima_PH_moy = mean(ima_PH(:));

sprintf('Image Passe Haut, max : %7.2f , min : %7.2f , moy : %7.2f \n',ima_PH_max, ima_PH_min, ima_PH_moy)

%AFFICHAGE 
draw_fig_hist_black_and_white(ima_PH,'image Passe Haut')

%Interpréter l'affichage obtenu. Que faut-il faire pour afficher
%correctement l'information ?
% => L'ajouter à l'image d'origine ! (avec le réhaussement)


disp('Pause : Rehaussement ')
pause

%Filtrage Passe Haut de rehaussement 
%Image réhaussée = image originale + alpha * image filtrée passe haut
%Former le noyau de convolution du filtre équivalent
%alpha = ... ; 
%Ker_RH = ..... ; 
alpha = 5;
%Ker_L = [0 0 0;-1 2.0 -1;0 0 0]; 
%Ker_RHL = Ker_imp + alpha*Ker_L;
Ker_RH = Ker_imp + alpha*Ker_PH;
%Convolution avec l'image
ima_RH = conv2(ima, Ker_RH, 'same'); 

%dynamique de l'image 
ima_RH_max = max(ima_RH(:));
ima_RH_min = min(ima_RH(:));
ima_RH_moy = mean(ima_RH(:));

ima_RH_nm_dym = ((ima_RH-ima_RH_min)/(ima_RH_max-ima_RH_min))*(ima_max-ima_min)+ima_min;
%dynamique de l'image 
ima_RH_dym_max = max(ima_RH_nm_dym(:));
ima_RH_dym_min = min(ima_RH_nm_dym(:));
ima_RH_dym_moy = mean(ima_RH_nm_dym(:));
sprintf('Image réhaussée, max : %7.2f , min : %7.2f , moy : %7.2f \n',ima_RH_max, ima_RH_min, ima_RH_moy)

%AFFICHAGE 
draw_fig_hist_black_and_white(ima_RH_nm_dym,['image réhaussée, alpha = ' num2str(alpha)])

%Troncature entre 0 et 255
ima_RH_tronc = min(max(ima_RH, ima_min), ima_max); 

%AFFICHAGE 
draw_fig_hist_black_and_white(ima_RH_tronc,['image réhaussée tronc, alpha = ' num2str(alpha)])

%Interpréter l'affichage obtenu. Mettre en relation l'histogramme à gauche
%et l'image correspondante à droite. Que constatez vous ? 

%Modifier l'image pour afficher integralement toute l'information dans
%l'image rehaussée. Faire l'affichage. Commenter le résultat obtenu


disp('Pause : Nouvelle itération du filtre rehausseur ')
pause
%On réitère le filtre rehausseur 
ima_RH2 = conv2(ima_RH, Ker_RH, 'same'); 

%dynamique de l'image 
ima_RH2_max = max(ima_RH2(:));
ima_RH2_min = min(ima_RH2(:));
ima_RH2_moy = mean(ima_RH2(:));

ima_RH2_nm_dym = ((ima_RH2-ima_RH2_min)/(ima_RH2_max-ima_RH2_min))*(ima_max-ima_min)+ima_min;
%dynamique de l'image 
ima_RH2_dym_max = max(ima_RH2_nm_dym(:));
ima_RH2_dym_min = min(ima_RH2_nm_dym(:));
ima_RH2_dym_moy = mean(ima_RH2_nm_dym(:));

sprintf('Image réhaussée 2 fois, max : %7.2f , min : %7.2f , moy : %7.2f \n',ima_RH2_max, ima_RH2_min, ima_RH2_moy)
%AFFICHAGE 
draw_fig_hist_black_and_white(ima_RH2,['image réhaussée, alpha = ' num2str(alpha)])

ima_RH2_tronc = min(max(ima_RH2, ima_RH_min), ima_RH_max); 
%AFFICHAGE 
draw_fig_hist_black_and_white(ima_RH2_tronc,['image réhaussée 2 fois tronc, alpha = ' num2str(alpha)])
