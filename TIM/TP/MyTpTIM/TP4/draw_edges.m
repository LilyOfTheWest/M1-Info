function draw_edges(pic,pic_edges)
%function draw_edges(pic,pic_edges)
%
%
%
%

pic_edges = uint8(pic_edges);
pic = uint8(pic);
colormap gray(256);

subplot(2,1,1);
image(pic_edges*255);
axis equal
axis off


T = zeros([size(pic),3]);
T(:,:,1) = pic.*(1-pic_edges)+255*pic_edges;
T(:,:,2) = pic.*(1-pic_edges);
T(:,:,3) = pic.*(1-pic_edges);
T = uint8(T);

subplot(2,1,2);
imagesc(T);
axis equal
axis off