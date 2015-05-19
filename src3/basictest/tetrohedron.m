% tetrohedron
clf;

xtet = [0   0     sqrt(3)/2     1/(2*sqrt(3)) ];
ytet = [0   1       .5                .5      ];
ztet = [0   0        0         sqrt(2)/sqrt(3)];
tet.edge(1).nodes = [1 2];
tet.edge(2).nodes = [1 3];
tet.edge(3).nodes = [1 4];
tet.edge(4).nodes = [2 3];
tet.edge(5).nodes = [2 4];
tet.edge(6).nodes = [3 4];
tet.center = [mean(xtet), mean(ytet), mean(ztet)];
for ii = 1 : 6,
    tet.edge(ii).midp = [ mean(xtet(tet.edge(ii).nodes)), ...
                          mean(ytet(tet.edge(ii).nodes)), ...
                          mean(ztet(tet.edge(ii).nodes))];
    tet.edge(ii).vec  = [ diff( xtet( tet.edge(ii).nodes ) ), ...
                          diff( ytet( tet.edge(ii).nodes ) ), ...
                          diff( ztet( tet.edge(ii).nodes ) )];
end

for ii = 1 : 6,
    plot3(xtet( tet.edge(ii).nodes ), ytet( tet.edge(ii).nodes ), ...
          ztet( tet.edge(ii).nodes ), 'black');
    text(tet.edge(ii).midp(1), tet.edge(ii).midp(2), ...
         tet.edge(ii).midp(3), sprintf('%d',ii), 'FontSize', 16);
    hold on;
end

for ii = 1 : 4,
    text(xtet(ii), ytet(ii), ztet(ii), sprintf('%d',ii), 'FontSize', 16, ...
         'color', 'red');
end

axis equal

volume = - tet.edge(1).vec * cross(tet.edge(2).vec, tet.edge(3).vec)' / 6;

% X = F Z (conversion between xy coord and natural coord)
% dX = F^{-T} dZ (differential operator relations) (3.21)
F = [ones(1,4); xtet; ytet; ztet];
FTinv = inv(F');

% verify J.P Webb paper equation (4)
Z = [0.4 0.6 0 0]';
X = F * Z;
% evaluate ( dX Z )
temp = FTinv * [1 0 0 0]';
dXZ{1} = temp(2:4);
temp = FTinv * [0 1 0 0]';
dXZ{2} = temp(2:4);
temp = FTinv * [0 0 1 0]';
dXZ{3} = temp(2:4);
temp = FTinv * [0 0 0 1]';
dXZ{4} = temp(2:4);

e{1} = Z(1) * dXZ{2} - Z(2) * dXZ{1};
e{2} = Z(1) * dXZ{3} - Z(3) * dXZ{1};
e{3} = Z(1) * dXZ{4} - Z(4) * dXZ{1};
e{4} = Z(2) * dXZ{3} - Z(3) * dXZ{2};
e{5} = Z(2) * dXZ{4} - Z(4) * dXZ{2};
e{6} = Z(3) * dXZ{4} - Z(4) * dXZ{3};

plot_e = 1;
quiver3(X(2), X(3), X(4), ...
        e{plot_e}(1), e{plot_e}(2), e{plot_e}(3));



