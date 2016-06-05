function [ out ] = myconvertf( in )

maxx = max(max(in));
minn = min(min(in));
out = ((in - minn) / (maxx - minn) * 65535);

end

