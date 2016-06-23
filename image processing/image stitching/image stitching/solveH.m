function H = solveH(xx, yy)
    % ԭ�������д����ƪ���µĹ�ʽ(6)��
    % ����˵���ǲ����ȥ�������ӣ��õ����Է����飬
    % ֮���ٶ�������Է����������⡣
    % ����β�дӢ���ˣ�����д��
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
