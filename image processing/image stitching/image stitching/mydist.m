function dist = mydist(x, y)
    % calculate eu distance between x and y
    dist = (sum((x .^ 2), 2))' + sum(y .^ 2, 2) - 2 * (x * y');
    dist(dist < 0) = 0;
end