function out = fftshift(in)
    out = in;
    ii = size(in, 1);
    jj = size(in, 2);
    bii = ii / 2;
    bjj = jj / 2;
    out(1 : bii, 1 : bjj) = in(bii + 1 : ii, bjj + 1 : jj);
    out(1 : bii, bjj + 1 : jj) = in(bii + 1 : ii, 1 : bjj);
    out(bii + 1 : ii, 1 : bjj) = in(1 : bii, bjj + 1 : jj);
    out(bii + 1 : ii, bjj + 1 : jj) = in(1 : bii, 1 : bjj);
end