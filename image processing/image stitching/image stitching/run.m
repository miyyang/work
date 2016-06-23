%% specify images
% image path
img_folder = 'data/school/';
img_name_list = char('1','2');

%% parameters
% Harris algorithm
harris_params.threshold = 1000;
harris_params.sigma = 2.1;
harris_params.radius = 2;
harris_params.display_result = 0;

% first match
neighbor_size = 10;
first_match_limit = 50;

% RANSAC algorithm
ransac_params.need = 4;
ransac_params.iter = 10000;
ransac_params.threshold = 1;

%% load image
total_number_img = size(img_name_list,1);
all_image = cell(total_number_img);
for i=1:total_number_img
    all_image{i} = imread(sprintf('%s%s', img_folder, img_name_list(i,:)),'jpg');
end

%% image registration
for total_unstitched = total_number_img: -1: 2
    
    % find out all the combination
    shuffler = fliplr(fullfact([total_unstitched total_unstitched]));
    shuffler(~diff(shuffler')',:) = [];
    shuffler(shuffler(:,1)>shuffler(:,2),:) = [];
   
    total_iteration = size(shuffler, 1);

    % stitch each pair of images
    stich_rank = zeros(total_iteration, 2);
    imaga_pool_stied = cell(total_iteration);

    for ii=1:total_iteration
        left_img_rgb = all_image{shuffler(ii,1)};
        right_img_rgb = all_image{shuffler(ii,2)};
        [imaga_pool_stied{ii}, inliers, residual] = registration(left_img_rgb, right_img_rgb, harris_params, ransac_params, neighbor_size,first_match_limit);
        stich_rank(ii, :) = [residual, ii];
    end
    
    stich_rank = sortrows(stich_rank, 1);
    % merge all the images
    all_image{shuffler(stich_rank(1,2), 1)} = imaga_pool_stied{stich_rank(1,2)};
    iindx = [1:shuffler(stich_rank(1,2), 2)-1 shuffler(stich_rank(1,2), 2)+1:total_iteration];
    all_image = all_image(iindx);
end

%% show image
figure, imshow(all_image{1});
