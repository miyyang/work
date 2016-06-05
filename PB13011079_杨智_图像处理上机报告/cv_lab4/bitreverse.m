function out = bitreverse(in)
    n = length(in);
    out = zeros(1, n);
   	nlog = log2(n);
	for ii = 0 : n - 1
        out(bin2dec(fliplr(dec2bin(ii, nlog))) + 1) = in(ii + 1);
    end
end