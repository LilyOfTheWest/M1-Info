function [ima_rgb_q, ima_index]=findexcoul(ima, table_coul); 
%function [ima_rgb_q, ima_index]=findexcoul(ima, table_coul); 
%Cette fonction r�alise l'indexation des couleurs d'une image ima suivant
%la table des couleurs table_coul
%Param�tres d'entr�e
%ima : tableau image (hauteur, largeur, 3) des pixels de l'image
%table_coul : tableau (nb_coul, 3) de correspondance couleur des index
%Param�tres de sortie
%ima_rgb_q : tableau image (hauteur, largeur, 3) avec les couleurs quantifi�es
%ima_index : tableau image (hauteur, largeur) des index
%

[lig, col, z]=size(ima);
nb_pix=size(ima,1)*size(ima,2); 

data=double(reshape(ima, nb_pix, size(ima,3)));

%----------------------------------
%Indexation des couleurs de l'image
%----------------------------------
d = dist2(data, table_coul);
[temp,index_coul]=min(d,[],2);  
ima_index=reshape(index_coul, lig, col);

ima_rgb_q=uint8([]);
for i=1:lig
    for j=1:col
        ima_rgb_q(i,j,:)=table_coul(ima_index(i,j),:);
    end
end    

