function draw_fig_hist_black_and_white(pic,title_fig)
%function draw_fig_hist_black_and_white(pic,h,title_fig)
%
%

[eff, pos] = hist(double(pic(:)),50);

%affichage des résultats
% _ histogramme et image
figure
subplot(1,2,1);

bar(pos,eff, 'b');

subplot(1,2,2);
colormap(gray(256));
image(pic);
colorbar
axis equal
axis off
title(title_fig)
