function [stitched, inliers, residual] = registration(left, right, harris_coe, ransac_coef, neighbor_size, first_match_limit)
% residual      Æ½¾ù²Ð²î

%% load and convert image
gray_left = rgb2gray(left);
double_gray_left = im2double(gray_left);
gray_right = rgb2gray(right);
double_gray_right = im2double(gray_right);

%% perfrom harris algorithm on each image seperately
[~, l_r, l_c] = harris(gray_left, harris_coe.sigma, neighbor_size+11+mod(neighbor_size+1,2), harris_coe.threshold, harris_coe.radius, harris_coe.display_result);
[~, r_r, r_c] = harris(gray_right, harris_coe.sigma, neighbor_size+11+mod(neighbor_size+1,2), harris_coe.threshold, harris_coe.radius, harris_coe.display_result);

%% get windows
leftwin = getwindows(double_gray_left, l_r, l_c, neighbor_size);
rightwin = getwindows(double_gray_right, r_r, r_c, neighbor_size);

%% compute correlation coefficent between images (with windows) 
leftwinnum = size(leftwin, 1);
rightwinnum = size(rightwin, 1);
coef = zeros(leftwinnum * rightwinnum, 3);
kk = 1;
for ii = 1 : leftwinnum
    for jj = 1 : rightwinnum
        lwindow = leftwin{ii};
        rwindow = rightwin{jj};
        ltmp = (lwindow - mean(lwindow(:))) / std(lwindow(:));
        rtmp = (rwindow - mean(rwindow(:))) / std(rwindow(:));
        dist = mydist(ltmp, rtmp);
        coef(kk, :) = [dist, ii, jj];
        kk = kk + 1;
    end
end

%% wipe off fake matches with threshold
coef_sorted = sortrows(coef, 1);
first_match = coef_sorted(1 : first_match_limit, :, :);
first_match_num = size(first_match, 1);
left_img_match = zeros(first_match_num, 2);
right_img_match = zeros(first_match_num, 2);

for ii = 1 : first_match_num
    left_img_match_ind = first_match(ii, 2);
    left_img_match(ii, :) = [l_c(left_img_match_ind), l_r(left_img_match_ind)];
    right_img_match_ind = first_match(ii, 3);
    right_img_match(ii, :) = [r_c(right_img_match_ind), r_r(right_img_match_ind)];   
end

%% RANSAC algorithm
[H, inliers, residual] = ransac(left_img_match', right_img_match', ransac_coef);
inlier_num = size(inliers', 1);
left_img_inlier = zeros(inlier_num, 2);
right_img_inlier = zeros(inlier_num, 2);

for ii=1:inlier_num
    inlier_index = inliers(ii);
    left_img_inlier(ii, :) = left_img_match(inlier_index, :);
    right_img_inlier(ii, :) = right_img_match(inlier_index, :);
end 

%% show matches after RANSAC
showmatchpoint(left,right,left_img_inlier(:,2),left_img_inlier(:,1),right_img_inlier(:,2),right_img_inlier(:,1));

%% merge two images into a new image which is big enought to hold all the pixels

transform = maketform('projective', H');
[~, ximtran, yimtran] = imtransform(left, transform, 'nearest');
xdataout = [min(1,ximtran(1)) max(size(right,2),ximtran(2))];
ydataout = [min(1,yimtran(1)) max(size(right,1),yimtran(2))];
left_img_tran = imtransform(left,transform,'XData',xdataout,'YData',ydataout);
right_img_tran = imtransform(right,maketform('affine',eye(3)),'XData',xdataout,'YData',ydataout);
stitched = max(right_img_tran, left_img_tran);

end