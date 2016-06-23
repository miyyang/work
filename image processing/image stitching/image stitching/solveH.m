function H = solveH(xx, yy)
    % 原理就是我写的那篇文章的公式(6)。
    % 简单来说就是叉积消去比例因子，得到线性方程组，
    % 之后再对这个线性方程组进行求解。
    % （这段不写英文了，好难写）
    xx = xx';
    yy = yy';
    nn = size(xx, 1);
    A = zeros(2 * nn, 9);
    for ii = 1 : nn
        kk = 2 * ii-1;
        tmp = [xx(ii,1), xx(ii,2), 1];
        A(kk, 4:6) = tmp;
        A(kk, 7:9) = -yy(ii,2) * tmp;
        A(kk+1,1:3) = tmp;
        A(kk+1,7:9) = -yy(ii,1) * tmp;
    end
    [~,~,V] = svd(A);
    H = reshape(V(:,end), [3,3])';
end
