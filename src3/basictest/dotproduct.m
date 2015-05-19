% this script verifies the equation (7) in D. Sun's paper.

clf;

xtri = randn(1,3);
ytri = randn(1,3);
plot([xtri,xtri(1)],[ytri,ytri(1)]);

% opposite nodes and t, n vectors
for e = 1 : 3,
    tri.edge(e).nodes = oppositenodes(e);
    tri.edge(e).tvec  = [xtri( tri.edge(e).nodes(2) ) - xtri( tri.edge(e).nodes(1) ), ...
                         ytri( tri.edge(e).nodes(2) ) - ytri( tri.edge(e).nodes(1) )];
    tri.edge(e).len   = norm( tri.edge(e).tvec );
    tri.edge(e).nvec  = [tri.edge(e).tvec(2), - tri.edge(e).tvec(1)];
    % normalize
    tri.edge(e).tvec  = tri.edge(e).tvec / norm( tri.edge(e).tvec );
    tri.edge(e).nvec  = tri.edge(e).nvec / norm( tri.edge(e).nvec );
    tri.edge(e).midp  = [ mean( xtri(tri.edge(e).nodes) ), mean( ytri(tri.edge(e).nodes) ) ];
    % assure nvec direction
    basep = [xtri(e), ytri(e)];
    tri.edge(e).nvec = sign( ( tri.edge(e).midp - basep ) * tri.edge(e).nvec' ) * tri.edge(e).nvec;    
end

hold on
% % plot tvec and nvec
% for e = 1 : 3,
%     scatter(tri.edge(e).midp(1), tri.edge(e).midp(2), 50, 'red');
%     quiver(tri.edge(e).midp(1), tri.edge(e).midp(2), ...
%            tri.edge(e).tvec(1), tri.edge(e).tvec(2), 'red');
%     quiver(tri.edge(e).midp(1), tri.edge(e).midp(2), ...
%            tri.edge(e).nvec(1), tri.edge(e).nvec(2), 'black');
% end

axis equal

text(xtri(1), ytri(1), '1');
text(xtri(2), ytri(2), '2');
text(xtri(3), ytri(3), '3');

% T*N tensor (matrix)
TN = zeros(3);
L  = zeros(1,3);
for e1 = 1 : 3,
    for e2 = 1: 3,
        TN(e1, e2) = tri.edge(e1).tvec * tri.edge(e2).nvec';
    end
    L(e1) = tri.edge(e1).len;
end
L = diag(L);
edge1 = [xtri( tri.edge(1).nodes(2) ) - xtri( tri.edge(1).nodes(1) ), ...
         ytri( tri.edge(1).nodes(2) ) - ytri( tri.edge(1).nodes(1) ), 0];
edge2 = [xtri( tri.edge(2).nodes(2) ) - xtri( tri.edge(2).nodes(1) ), ...
         ytri( tri.edge(2).nodes(2) ) - ytri( tri.edge(2).nodes(1) ), 0];
A = norm( cross(edge1, edge2) );    % twice triangle area
S = [0 -1 1; 1 0 -1; -1 1 0];

for e = 1 : 3,
    tri.edge(e).height = A / tri.edge(e).len;
end

TNr = - A * inv(L) * S * inv(L);
TN - TNr
     
     
     