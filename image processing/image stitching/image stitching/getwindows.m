function windows = getwindows(image, xx, yy, winsize)
    % extract all the windows
    [row_size, col_size] = size(image);
    windows = cell(size(xx, 1));
	for i=1 : size(xx)
	row = xx(i);
	col = yy(i);
	windows{i} = []; 
	if (row - winsize >= 1 && row + winsize <= row_size && col - winsize >= 1 && col + winsize <= col_size)
        windows{i} = reshape(image(row - winsize : row + winsize, col - winsize : col + winsize), 1, (winsize * 2 + 1) ^ 2);
	end
end


