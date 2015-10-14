function ima_out=fbandeauout(ima_in, n)
%function ima_out=fbandeauout(ima_in, n)
%retirer n pixels en haut et en bas, à droite et à gauche
ima_out=ima_in(n+1:end-n, :,:);
ima_out=ima_out(:, n+1:end-n,:);
