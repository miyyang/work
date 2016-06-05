function out = myfft(in)
    n = length(in);
    nlog = log2(n);

    out = bitreverse(in);
    for ss = 1 : nlog
        mm = power(2, ss);
        wm = exp(- 2 * pi * 1i / mm);

        for kk = 0 : mm : n - 1
            ww = 1;
            for j = 0 : mm / 2 - 1
                tt = ww * out(kk + j + mm / 2 + 1);
                uu = out(kk + j + 1);
                out(kk + j + 1) = uu + tt;
                out(kk + j + mm / 2 + 1) = uu - tt;
                ww = ww * wm;
            end
        end
    end
end