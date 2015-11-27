function noisy_pic = add_gaussian_noise(pic,rsb)
%function noisy_pic = add_gaussian_noise(pic,rsb)
%
% Add gaussian noise to pic
%
% INPUT
%       pic: original picture in uint8
%       rsb: Signal to noise ratio (in dB)
% OUTPUT
%       noisy_pic: the noisy picture in uint8
%
%

pic = double(pic);

%power of pic as the variance
var_pic = var(pic(:),1);

%power of noise
var_noise = var_pic*10^(-rsb/10);

%noise
noise = sqrt(var_noise)*randn(size(pic));

%noisy picture
noisy_pic = uint8(min(max(pic+noise,0),255));