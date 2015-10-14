function draw_results_color(pic,pic0,h,h0,title_fig)
%function draw_results_color(pic,pic0,h,h0,title_fig)
%
%

col = ['r','g','b'];

%affichage des résultats
% _ histogrammes
figure

StrLabel{1} = 'Niveau Couleur Rouge'; 
StrLabel{2} = 'Niveau Couleur Vert'; 
StrLabel{3} = 'Niveau Couleur Bleu'; 

for k=0:2
    subplot(3,2,1+2*k);
    plot([0:255],h0(:,1+k),col(k+1));
    grid on
    axis([0,255,0,max(h0(:))]);
    xlabel(StrLabel{k+1})
    ylabel('Effectif')


    subplot(3,2,2+2*k);
    plot([0:255],h(:,1+k),col(k+1));
    grid on
    axis([0,255,0,max(h0(:))]);
    xlabel(StrLabel{k+1})
    ylabel('Effectif')
    title([title_fig ' : Après'])
end


% _ images
figure
subplot(1,2,1);
image(pic0);
axis equal
axis off
subplot(1,2,2);
image(pic);
axis equal
axis off
title([title_fig ' : Après'])

