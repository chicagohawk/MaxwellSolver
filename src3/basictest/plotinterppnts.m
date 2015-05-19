% plot interpolatory points (use codegen.m)

clear;

% regular tetrahedron
x = [1 -1 0 0];
y = [0 0 -1 1];
z = [-1/sqrt(2) -1/sqrt(2) 1/sqrt(2) 1/sqrt(2)];

% edge vectors
t23 = [x(3)-x(2), y(3)-y(2), z(3)-z(2)];
t24 = [x(4)-x(2), y(4)-y(2), z(4)-z(2)];
t12 = [x(2)-x(1), y(2)-y(1), z(2)-z(1)];
t13 = [x(3)-x(1), y(3)-y(1), z(3)-z(1)];
t14 = [x(4)-x(1), y(4)-y(1), z(4)-z(1)];
t34 = [x(4)-x(3), y(4)-y(3), z(4)-z(3)];

% twice the opposite triangle areas
S1 = norm( cross(t23, t24) );
S2 = norm( cross(t13, t14) );
S3 = norm( cross(t12, t14) );
S4 = norm( cross(t12, t13) );

% patch
patch(x([1 2 3]), y([1 2 3]), z([1 2 3]), 'red'); hold on
patch(x([1 2 4]), y([1 2 4]), z([1 2 4]), 'green');
patch(x([1 3 4]), y([1 3 4]), z([1 3 4]), 'blue');
patch(x([2 3 4]), y([2 3 4]), z([2 3 4]), 'magenta');
alpha(0.3)

for ii = 1:4,
    str = sprintf('%d',ii);
    text(x(ii),y(ii),z(ii),str, 'FontSize', 30);
end

axis equal;

n=4;

bits = codegen(n-2, 4);
bits(:,1) = bits(:,1) + 1;
bits(:,4) = bits(:,4) + 1;

Z = 1./n * bits;  Z = Z';

A = [1 1 1 1; x; y; z];
F = A / det(A);

X = det(A) * F * Z;
X = X';  X = X(:,2:4);
jj = 1;

    P1 = P(bits(jj,1)-1,n-2,(bits(:,1)-1)/(n-2));
    P2 = P(bits(jj,2),n-2,bits(:,2)/(n-2));
    P3 = P(bits(jj,3),n-2,bits(:,3)/(n-2));
    P4 = P(bits(jj,4)-1,n-2,(bits(:,4)-1)/(n-2));
    PP = P1.*P2.*P3.*P4;
    scatter3(X(:,1), X(:,2), X(:,3), 100, PP,'filled');
    view(3);

