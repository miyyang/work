function out = myifft( in )
    n = length(in);
    out = bitreverse(in);
    for ss = 1 : log2(n)
        mm = power(2, ss);
        wm = exp(2 * pi * 1i / mm);
        for k = 0 : mm : n - 1
            ww = 1;
            for jj = 0 : mm / 2 - 1
                t = ww * out(k + jj + mm / 2 + 1);
                u = out(k + jj + 1);
                out(k + jj + 1) = u + t;
                out(k + jj + mm / 2 + 1) = u - t;
                ww = ww * wm;
            end
        end
    end
    out = out ./ n;
end