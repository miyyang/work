function out = myifft2d(in)
    out = in;
    for jj = 1 : size(in, 1)
        out(jj, :) = myifft(out(jj, :));
    end
    for jj = 1 : size(in, 2)
        out(:, jj) = myifft(out(:, jj));
    end
end