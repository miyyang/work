function resultimg = showmatchpoint(image1, image2, x1, y1, x2, y2)

    % show images
    [h1, w1, d] = size(image1);
    [h2, w2, ~] = size(image2);
    resultimg = zeros(max(h1, h2), w1 + w2, d);
    resultimg(1 : h1, 1 : w1, :) = image1;
    resultimg(1 : h2, w1 + 1 : w2 + w1, :) = image2;
    figure;
    imshow(uint8(resultimg));
    hold on;
    % show match points
    for ii = 1 : size(x1)
        plot([y1(ii), y2(ii) + w1], [x1(ii), x2(ii)], '-ro', 'LineWidth', 2,  'MarkerSize', 8, 'MarkerFaceColor', 'g' );
    end 
end

