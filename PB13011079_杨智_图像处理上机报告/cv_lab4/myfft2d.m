function out = myfft2d(in)
    out = in;
    for ii = 1 : size(in, 1)
        out(ii, :) = myfft(out(ii, :));
    end
    for ii = 1 : size(in, 2)
        out(:, ii) = myfft(out(:, ii));
    end
end