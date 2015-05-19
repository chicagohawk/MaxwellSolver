%% plot pdetool's raw mesh ---- boundary
for i = 1:size(e,1),
    edge = e(i, 1:2);
    edge = [p(edge(1), :); p(edge(2), :)];
    plot(edge(:,1),edge(:,2), 'lineWidth', 2);
    midp =  sum(edge)/2;    % midpoint of edge
%   text(midp(1), midp(2), sprintf('%d',i), 'color', 'red');
    hold on;
end


%% plot pdetool's raw mesh ---- triangles
for i = 1:size(t,1),
    
    edge = t(i, [1,2]);
    edge = [p(edge(1), :); p(edge(2), :)];
    plot(edge(:,1),edge(:,2));
    hold on
    
    edge = t(i, [2,3]);
    edge = [p(edge(1), :); p(edge(2), :)];
    plot(edge(:,1),edge(:,2));
    hold on
    
    edge = t(i, [3,1]);
    edge = [p(edge(1), :); p(edge(2), :)];
    plot(edge(:,1),edge(:,2));
    hold on
    
    midp = sum(p(t(i,1:3),:))/3;    % midpoint of triangle
%   text(midp(1)-0.02, midp(2), sprintf('%d', i));
end

%%
axis equal
clear edge i midp