%-----------------------------------------------------
% UE Traitement d'Images M1 Info
% TP1 programme TP_quantif.m
% Objectifs :
%  - Manipulation d'une image couleur
%       . Quantification des couleurs
%       . Table d'indexation de couleur
%------------------------------------------------------

%Fermer toutes les figures et vider la m�moire
close all
clear

%Rajouter le path de votre r�pertoire Utils
addpath ('..\Utils')

%Nom du r�pertoire des images JPG
dirIma='..\Image_jpg';

%Nom de l'image choisi
%nomIma='ville02032';
nomIma='ville01068';

%Fixer le nombre maximum de couleurs 
nbCoul=32;

%lecture de l'image
[ima, map]=imread([dirIma '\' nomIma '.JPG']);

[lig, col, z]=size(ima);

nbPix = lig*col; 

%Affichage
n1=figure;
image(ima)
colormap('default')
axis 'equal'
axis 'off'
title(['image originale ' num2str(lig) ' x ' num2str(col)])

%--------------------------------------
%Base de donn�es pour la quantification
%--------------------------------------
%Cr�ation d'un tableau data contenant pour chaque ligne les coordonn�es couleur R G B du pixel. 
%Nombre de lignes du tableau = nombre de pixels dans l'image
%Nombre de colonnes du tableau = 3
%A partir de ce tableau data, cr�ation du tableau dataLearn correspondant 
%� 10% des pixels de l'image pris al�atoirement.
%Les tableaux data et dataLearn seront des 'double'
%Utilisation des fonctions randperm et reshape

ratioLearn  = 0.1;
data        = double(reshape(ima, nbPix, size(ima,3)));

index       = randperm(nbPix);
nbPixLearn  = fix(nbPix*ratioLearn);
index       = index(1:nbPixLearn);
dataLearn   = data(index,:);

%Affichage de la distribution des couleurs des pixels de la base
%d'apprentissage, dans l'espace 3D (R, G, B) 
n2 = figure;
plot3(dataLearn(:, 1), dataLearn(:, 2), dataLearn(:, 3), 'b.')
grid on
xlabel('Rouge')
ylabel('Vert')
zlabel('Bleu')

%-------------------------------------------
%Quantification par l'algorithme des Kmeans
%-------------------------------------------    
[temp, couleur] = kMeansCluster(dataLearn,nbCoul,1);

% On affiche le contenu de couleur et sa taille
couleur
length(couleur)

couleur         = min(round(couleur),255);
disp('fin du Kmeans')

%Affichage des couleurs des index  
figure(n2)
hold on
plot3(couleur(:, 1), couleur(:, 2), couleur(:, 3), 'rs', 'MarkerEdgeColor','r',...
      'MarkerFaceColor','r', 'MarkerSize',10)
legend('couleur(pixel)', 'couleur(index)', 'location', 'North')
            
pause
%Que repr�sente le tableau couleur ?


%----------------------------------
%Indexation des couleurs de l'image
%----------------------------------
%En �tudiant les aides sur ces fonctions, expliquer 
%ce qui est r�alis� par cette s�quence d'instructions
d                = dist2(data, couleur);
[temp,indexCoul] = min(d,[],2);  
imaIndexCoul     = reshape(indexCoul, lig, col);
disp('fin de l''indexation')

size(imaIndexCoul)
min(imaIndexCoul(:))
max(imaIndexCoul(:))

%Table des couleurs utilisable par colormap
%Cr�er une table des couleurs avec les couleurs choisies
couleurLut = couleur/255;


%Affichage
n3 = figure;
imagesc(imaIndexCoul)
colormap('default')
axis 'equal'
axis 'off'
title(['image des index couleur ' int2str(nbCoul)])

n4 = figure;
image(imaIndexCoul)
colormap(couleurLut)
axis 'equal'
axis 'off'
title(['image quantifi�e index�e ' int2str(nbCoul)])


%Creer une image couleur sur trois composantes au m�me format 
%que l'image originale mais en rempla�ant les couleurs originales
%avec les couleurs quantifi�es
%Faire attention au typage des variables
%Appeler cette image par la variable imaQuantifRGB
%---------------Ins�rer le code-------------------------%
%On cr�e la matrice qui correspondra � notre image quantifi�e
imaQuantifRGB = ones(lig, col, 3);

%Pour chaque pixel de la nouvelle image, on retrouve la composante de chaque couleur
%correspondante dans le LUT
for i=1:lig
    for j=1:col
        for k=1   :3
            imaQuantifRGB(i,j,k) = couleurLut(imaIndexCoul(i,j),k);
        end
    end
end

%-------------------------------------------------------%

%Affichage 
n5 = figure;
%--Ins�rer le code pour l'affichage de imaQuantifRGB----%
image(imaQuantifRGB)
colormap('default')
%--------------------------------------------------------%
axis 'equal'
axis 'off'
title(['image quantifi�e ' int2str(nbCoul)])


