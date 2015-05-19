% plot general eigen value modes
mode = 35;
ufull = zeros(numel(pntlist),1);
ufull(nob_index) = abs(V(:,mode));
figure(1);
for i = 1:size(e,1),
    edge = e(i, 1:2);
    edge = [p(edge(1), :); p(edge(2), :)];
    plot(edge(:,1),edge(:,2), 'lineWidth', 1, 'color', 'black');
    midp =  sum(edge)/2;    % midpoint of edge
%   text(midp(1), midp(2), sprintf('%d',i), 'color', 'red');
    hold on;
end
plotFEM;
ufull(nob_index) = angle(V(:,mode))/3.1415;
figure(2);
for i = 1:size(e,1),
    edge = e(i, 1:2);
    edge = [p(edge(1), :); p(edge(2), :)];
    plot(edge(:,1),edge(:,2), 'lineWidth', 1, 'color', 'black');
    midp =  sum(edge)/2;    % midpoint of edge
%   text(midp(1), midp(2), sprintf('%d',i), 'color', 'red');
    hold on;
end
plotFEM;
caxis([0,1]);