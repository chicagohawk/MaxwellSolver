clear; clf;

% regular tetrahedron

% tetra 1
% x = [0.333 0.167 0.195 0.238];
% y = [1 1 1 0.885];
% z = [0.5 0.5 0.3885 0.5];

% tetra 2
x = [0.27 0.121 0.168 0.168];
y = [0.35 0.378 0.421 0.25];
z = [0 0 0.253 0.25];

% edge vectorsc
t23 = [x(3)-x(2), y(3)-y(2), z(3)-z(2)];  l23 = norm(t23);
t24 = [x(4)-x(2), y(4)-y(2), z(4)-z(2)];  l24 = norm(t24);
t12 = [x(2)-x(1), y(2)-y(1), z(2)-z(1)];  l12 = norm(t12);
t13 = [x(3)-x(1), y(3)-y(1), z(3)-z(1)];  l13 = norm(t13);
t14 = [x(4)-x(1), y(4)-y(1), z(4)-z(1)];  l14 = norm(t14);
t34 = [x(4)-x(3), y(4)-y(3), z(4)-z(3)];  l34 = norm(t34);

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
alpha(0.2);

for ii = 1:4,
    str = sprintf('%d',ii);
    text(x(ii),y(ii),z(ii),str, 'FontSize', 30);
end

axis equal;

% determine left or right tetrahedron
if( cross(t12, t13) * t14' > 0 ),
    type = 1;
    K = 1;
else
    type = 2;
    K = -1;
end

F = [1 1 1 1; x; y; z];
V = 1/6 * abs( det(F) );
F = F / det(F);

S = diag([S1, S2, S3, S4]);

Mat = - K * inv(S) * inv(F);
S = diag(S);

n1 = Mat(1,2:4);
n2 = Mat(2,2:4);
n3 = Mat(3,2:4);
n4 = Mat(4,2:4);

quiver3(x, y, z, Mat(:,2)', Mat(:,3)', Mat(:,4)', 0.785, 'LineWidth', 3);
nabla1 = - S(1) / 6 / V * n1;
nabla2 = - S(2) / 6 / V * n2;
nabla3 = - S(3) / 6 / V * n3;
nabla4 = - S(4) / 6 / V * n4;

bits = splitcodegen(4, 4);
Z = 1./4 * bits;  Z = Z';
A = [1 1 1 1; x; y; z];
F = A / det(A);
X = det(A) * F * Z;
X = X';  X = X(:,2:4);  Z = Z';
 
% plot N12
n12x = l12 * ( Z(:,1) * nabla2(1) - Z(:,2) * nabla1(1) );
n12y = l12 * ( Z(:,1) * nabla2(2) - Z(:,2) * nabla1(2) );
n12z = l12 * ( Z(:,1) * nabla2(3) - Z(:,2) * nabla1(3) );

scatter3(X(:,1), X(:,2), X(:,3), 60, 'filled');
quiver3(X(:,1), X(:,2), X(:,3), n12x, n12y, n12z, 0.6, 'LineWidth', 1);

