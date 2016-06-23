function chosen = randsubset(total, need)

% not enought candidates
if need > total
	chosen = [];
    disp('warning: not enought candidates');
	return
end

% get random subset
chosen = zeros(1, need);
array = 1 : total;
ras = ceil(rand(1, need) .* (total : -1 : total - need + 1));
for ii = 1 : need
	while ras(ii) == 0
		ras(ii) = ceil(rand(1)*(total-ii+1));
	end
	chosen(ii) = array(ras(ii));
	array(ras(ii)) = [];
end