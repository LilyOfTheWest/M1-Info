function edges_link = link_picture(edges_points, is_edges_points)
%function edges_link = link_picture(edge_points, is_edge_points)
%
% Perform a linkage function
%
% INPUT: 
%       edges_points: binary picture of  edge points
%       is_edges_points: binary picture of  candidate edge points
% 
% OUTPUT: 
%       edges_link: segmented edges after linkage
%
%

%size
[N_i,N_j] = size(edges_points);


%<to do !!!!!!!!!!!!!!>
%
%
% Réalisez les 4 passes vues en cours afin de completer edges_points.
% <gauche-droite> | <haut-bas> | <droite gauche> | <bas-haut>
%    
% %1ere passage
% for(k_i=...)
%   for(k_j=...)
%
% 2eme passage
% for(k_j=...)
%   for(k_i=...)
%
% 3eme passage
% for(k_i=...)
%   for(k_j=...)
%
% 4eme passage
% for(k_j=...)
%   for(k_i=...)
%
%
%
%
%</to do>

%Passe No 1
for i = 2:N_i-1
    for j = 2:N_j-1
         if is_edges_points(i,j)==1
            v1 = [i, j-1];
            v2 = [i-1, j-1];
            v3 = [i-1, j];
            v4 = [i-1, j+1];
            if edges_points(v1(1,1), v1(1,2)) == 1
                edges_points(i,j) = 1;
            end
            if edges_points(v2(1,1), v2(1,2)) == 1
                edges_points(i,j) = 1;
            end
            if edges_points(v3(1,1), v3(1,2)) == 1
                edges_points(i,j) = 1;
            end 
            if v4(1,1) <= 180 && v4(1,1) > 0 && v4(1,2) > 0 && v4(1,2) <= 243
                if edges_points(v4(1,1), v4(1,2)) == 1 
                    edges_points(i,j) = 1;
                end
            end
         end
    end
end

%Passe No 2
for j = N_j-1:-1:2
    for i=2 :N_i-1
         if is_edges_points(i,j)==1
            v1 = [i-1, j];
            v2 = [i-1, j+1];
            v3 = [i, j+1];
            v4 = [i+1, j+1];
            if edges_points(v1(1,1), v1(1,2)) == 1
                edges_points(i,j) = 1;
            end
            
            if edges_points(v2(1,1), v2(1,2)) == 1
                edges_points(i,j) = 1;
            end
            
            if edges_points(v3(1,1), v3(1,2)) == 1
                edges_points(i,j) = 1;
            end
            
            if v4(1,1) <= 180 && v4(1,1) > 0 && v4(1,2) > 0 && v4(1,2) <= 243
               if edges_points(v4(1,1), v4(1,2)) == 1
                   edges_points(i, j) = 1;
               end
            end
         end
    end
end

%Passe No 3
for i =N_i-1:-1:2
    for j=N_j-1:-1 :2
         if is_edges_points(i,j)==1
            v1 = [i, j+1];
            v2 = [i+1, j+1];
            v3 = [i+1, j];
            v4 = [i+1, j-1];
                
            if edges_points(v1(1,1), v1(1,2)) == 1
                edges_points(i,j) = 1;
            end
            
            if edges_points(v2(1,1), v2(1,2)) == 1
                edges_points(i,j) = 1;
            end
            
            if edges_points(v3(1,1), v3(1,2)) == 1
                edges_points(i,j) = 1;
            end
            
            if v4(1,1) <= 180 && v4(1,1) > 0 && v4(1,2) > 0 && v4(1,2) <= 243
               if edges_points(v4(1,1), v4(1,2)) == 1
                   edges_points(i, j) = 1;
               end
            end
         end
    end
end

%Passe No 4
for j =2   :N_j-1
    for i=N_i-1:-1 :2
         if is_edges_points(i,j)==1
            v1 = [i+1, j];
            v2 = [i+1, j-1];
            v3 = [i, j-1];
            v4 = [i-1, j-1];

            if edges_points(v1(1,1), v1(1,2)) == 1
                edges_points(i,j) = 1;
            end
            
            if edges_points(v2(1,1), v2(1,2)) == 1
                edges_points(i,j) = 1;
            end
            
            if edges_points(v3(1,1), v3(1,2)) == 1
                edges_points(i,j) = 1;
            end
            
            if v4(1,1) <= 180 && v4(1,1) > 0 && v4(1,2) > 0 && v4(1,2) <= 243
               if edges_points(v4(1,1), v4(1,2)) == 1
                   edges_points(i, j) = 1;
               end
            end
         end
    end
end

edges_link = edges_points;
