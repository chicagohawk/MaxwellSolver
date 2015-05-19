% plot 2D FEM data
X = zeros(3,numel(pntlist));
Y = zeros(3,numel(pntlist));
absu_t = zeros(1,size(t,1));
for ii = 1:size(t,1),
    X(:,ii) = p(t(ii,1:3),1);
    Y(:,ii) = p(t(ii,1:3),2);
    absu_t(ii) = abs(mean(ufull(t(ii,1:3))));
end
C = absu_t / max(absu_t);

patchplot = patch(X,Y,C,'linestyle','none');
set(patchplot,'FaceColor','flat');
colorbar();