% specify boundary types (D, N, R) and visualize
% very case dependent, ready to modify
function trilist = specify_boundary_type(trilist, t, p)
    figure(1);  hold on;
    for i = 1 : numel( trilist ),
        if numel( trilist(i).shre ) == 2,
            pnts = t(trilist(i).shre, 1:3);
            offpnt = intersect(pnts(1,:), pnts(2,:));
            edgepnt = setdiff(t(i,1:3), offpnt);
            edge = [p(edgepnt(1), :); p(edgepnt(2), :)];
            meanxy = mean(edge);
            % specify boundary type (testcase, ready to modify)
            if meanxy(1) > 0
                plot(edge(:,1), edge(:,2), 'lineWidth', 3,'color','black');
                trilist(i).bndtype = 'D';
            elseif meanxy(2) > 0
                plot(edge(:,1), edge(:,2), 'lineWidth', 3,'color','red');
                trilist(i).bndtype = 'N';
            else
                plot(edge(:,1), edge(:,2), 'lineWidth', 3,'color','green');
                trilist(i).bndtype = 'R';
            end
        end
    end
    axis equal;
    title('black: D   red: N   green: R');
end