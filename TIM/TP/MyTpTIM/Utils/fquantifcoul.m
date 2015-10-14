function [ima_rgb_q, ima_index, table_rgb]=fquantifcoul(ima, nb_coul, ratio_learn); 
%function [ima_rgb_q, ima_index, table_rgb]=fquantifcoul(ima, nb_coul, ratio_learn); 
%Cette fonction réalise la quantification des couleurs avec l'algorithme
%des Kmeans. 
%Paramètres d'entrée
%ima : tableau image (hauteur, largeur, 3) des pixels de l'image
%nb_coul : nombre de couleurs à extraire
%ratio_learn : le ratio de pixels servant dans l'apprentissage des 
%couleurs à quantifier , ex ratio_learn=0.1 pour 10%
%Paramètres de sortie
%ima_rgb_q : tableau image (hauteur, largeur, 3) avec les couleurs quantifiées
%ima_index : tableau image (hauteur, largeur) des index
%table_rgb : tableau (nb_coul, 3) de correspondance couleur des index
%

[lig, col, z]=size(ima);
nb_pix=size(ima,1)*size(ima,2); 
nb_pix_learn=fix(nb_pix*ratio_learn);

%--------------------------------------
%Base de données pour la quantification
%--------------------------------------
index=randperm(nb_pix);
data=double(reshape(ima, nb_pix, size(ima,3)));
data_learn=data(index,:);
data_learn=data_learn(1:nb_pix_learn,:);

%-------------------------------------------
%Quantification par l'alogorithme des Kmeans
%-------------------------------------------    
[temp, table_rgb]=kMeansCluster(data_learn,nb_coul,1);
table_rgb=min(round(table_rgb),255);

%----------------------------------
%Indexation des couleurs de l'image
%----------------------------------
d = dist2(data, table_rgb);
[temp,index_coul]=min(d,[],2);  
ima_index=reshape(index_coul, lig, col);

ima_rgb_q=uint8([]);
for i=1:lig
    for j=1:col
        ima_rgb_q(i,j,:)=table_rgb(ima_index(i,j),:);
    end
end    

