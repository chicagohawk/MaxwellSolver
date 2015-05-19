%% plot real time trilist.cct
% convert nodal values to triangle values
absu = abs(ufull);
angu = angle(ufull);
absu_t = zeros(size(t,1),1);
angu_t = zeros(size(t,1),1);

for ii = 1:size(t,1),
    absu_t(ii) = mean(absu(t(ii,1:3)));
    angu_t(ii) = mean(angu(t(ii,1:3)));
end

%% plot abs value
figure(1);
% plot mesh boundary
for i = 1:size(e,1),
    edge = e(i, 1:2);
    edge = [p(edge(1), :); p(edge(2), :)];
    plot(edge(:,1),edge(:,2), 'lineWidth', 2,'color','black');
    hold on;
end
axis equal
clear edge i midp

%F = TriScatteredInterp(t(:,5:6), cell2mat({trilist.cct})');
scalars = absu_t;
F = TriScatteredInterp(t(:,5:6), scalars);
[qx,qy] = meshgrid(-1:0.01:1, -1:0.01:1);
qz = F(qx,qy);
contourf(qx,qy,qz, 'edgecolor', 'none');
colormap(jet);  axis equal;  colorbar
alpha(0.5);
drawnow
clear F qx qy qz cct

%% plot angle value
figure(2);
% plot mesh boundary
for i = 1:size(e,1),
    edge = e(i, 1:2);
    edge = [p(edge(1), :); p(edge(2), :)];
    plot(edge(:,1),edge(:,2), 'lineWidth', 2,'color','black');
    hold on;
end
axis equal
clear edge i midp

%F = TriScatteredInterp(t(:,5:6), cell2mat({trilist.cct})');
scalars = angu_t;
F = TriScatteredInterp(t(:,5:6), scalars);
[qx,qy] = meshgrid(-1:0.01:1, -1:0.01:1);
qz = F(qx,qy);
contourf(qx,qy,qz, 'edgecolor', 'none');
colormap(jet);  axis equal;  colorbar
alpha(0.5);
drawnow
clear F qx qy qz cct


