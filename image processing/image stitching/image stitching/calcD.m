function [d, residual] = calcD(H, x, y)
    % xx is a project of x using H, 
    % return the distance between xx and y
    n = size(x, 2);
    % convert to homogeneous coordinates, then project
    xx = H * [x ; ones(1,n)];
    xx = xx(1:2,:) ./ repmat(xx(3,:), 2, 1);
    d = sum((y-xx) .^ 2, 1);

    residual = sum(d) / n;
end