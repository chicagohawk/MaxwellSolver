% FEM Solver Assembly
% first demo case, homogeneous Dirichlet eigenvalue problem
load '../data/antena_postGeo_v2.mat'
%% memory allocation
% preprequisite: geometry post processed by initialize.m
A  =  zeros( numel(pntlist) );      % bilinear matrix
V  =  zeros( numel(pntlist), 1 );   % load vector
nablaL =  [1  0  -1;
           0  1  -1];
JTI = zeros(2);
       
%% bilinear matrix assembly elementwise
for tri = 1 : numel(trilist),
    % aa = trilist(tri).a;        % material property
    aa = 1;
    xy = p( t(tri,1:3), : );  % x, y coordinates of cell's 3 nodes, 3-by-2 matrix
    area = trilist(tri).area;
    JTI  = [ xy(2,2)-xy(3,2) , -xy(1,2)+xy(3,2); ...    % inverse of transpose of J      
            -xy(2,1)+xy(3,1) ,  xy(1,1)-xy(3,1)] / 2 / area ;
    for i = 1:3,
        for j = 1:3,
            % contribution from the JTI term
            intconst = aa * ( JTI * nablaL(:,i) )' * ( JTI * nablaL(:,j) ) * area;
            A( t(tri, i), t(tri, j) )  =  A(t(tri, i), t(tri, j)) + intconst;
        end
    end
end

% contribution from the k2 term
A2 = zeros( numel(pntlist) );
for tri = 1 : numel(trilist),
    for i = 1:3,
        for j = 1:3,
            if i == j,
                A2( t(tri, i), t(tri, j) )  =  A2(t(tri, i), t(tri, j)) + area / 6;
            else
                A2( t(tri, i), t(tri, j) )  =  A2(t(tri, i), t(tri, j)) + area / 12;
            end
        end
    end
end


%% explicit elimination
% A = A(33:end,33:end);
% A2 = A2(33:end,33:end);