clear; clf;

% tetrahedron
x = 5*rand(1,4);
y = 5*rand(1,4);
z = 5*rand(1,4);

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

% n1 normal vector
n1 = cross(t23, t24);  n1 = n1 / norm(n1);
n1 = sign(n1 * t12') * n1;

% n2 normal vector
n2 = cross(t34, -t13);  n2 = n2 / norm(n2);
n2 = sign(n2 * t23') * n2;

% n3 normal vector
n3 = cross(t14, t24);  n3 = n3 / norm(n3);
n3 = sign(n3 * t34') * n3;

% n4 normal vector
n4 = cross(t12, t13);  n4 = n4 / norm(n4);
n4 = sign(- n4 * t14') * n4;

% plot tetrahedron
plot3(x([1,2]),y([1,2]),z([1,2]));  hold on;
plot3(x([1,3]),y([1,3]),z([1,3]));
plot3(x([1,4]),y([1,4]),z([1,4]));
plot3(x([2,3]),y([2,3]),z([2,3]));
plot3(x([2,4]),y([2,4]),z([2,4]));
plot3(x([3,4]),y([3,4]),z([3,4]));

for ii = 1:4,
    str = sprintf('%d',ii);
    text(x(ii),y(ii),z(ii),str);
end

quiver3(x(1),y(1),z(1),n1(1),n1(2),n1(3));
quiver3(x(2),y(2),z(2),n2(1),n2(2),n2(3));

axis equal;

% determine left or right tetrahedron
if( cross(t12, t13) * t14' > 0 ),
    type = 1;
    K = diag([1 1 1 1]);
else
    type = 2;
    K = diag([-1 -1 -1 -1]);
end

F = [1 1 1 1; x; y; z];
F = F / det(F);

S = diag([S1, S2, S3, S4]);

Mat = - K * inv(S) * inv(F);

[n1; n2; n3; n4]
Mat(:,2:4)
