function [inliers, inliers_index, residual] = ransac(x, y, params)
    % parameters:
    %       pretty self explained， 不解释了
    need = params.need;
    iter = params.iter;
    threshold = params.threshold;
    total = size(x,2);

    inliers_size = zeros(1,iter);
    inliers_can = cell(1,iter);

    % 当 （循环次数大于iter） 或者 （inliers的数目小于4） 时 结束循环 
    for ii = 1:iter
        % get a subset
        subset = randsubset(total,need);
        HH = solveH(x(:,subset),y(:,subset));
        % filtered with threshold
        dist = calcD(HH, x, y);
        inliers_index = find(dist < threshold);
        inliers_size(ii) = length(inliers_index);
        if length(inliers_index) < 4
            continue;
        end
        % record
        inliers_can{ii} = HH;
    end
    % return the model with most inliers
    [~,ii] = max(inliers_size);
    inliers = inliers_can{ii};
    [dist, residual] = calcD(inliers,x,y);
    inliers_index = find(dist < threshold);
	
end

