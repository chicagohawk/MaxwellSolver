% post process raw geometry generated from matlab pdetool

%% compute adjacent triangles and detect boundary triangles and types
load '../data/antena_ept.mat';
% plot_raw_geo;

% tri.shrp: list of triangles that share one point with tri
% tri.shre: list of triangles that share one edge  with tri
% tri.bndtype: boundary property of an element
%          i or I: interior element
%          d or D: Dirichlet boundary element
%          n or N: Neumann boudnary element
%          r or R: Robin boundary element
% e.g. use strcmpi(tri.bndtype, 'I') to identify boundary type
% use specify_boundary_type() to initialize boundary type
% use specify_boundary_numerics() to initialize boundary numerics
tri = struct('shrp', 0, 'shre', 0, 'bndtype', 'I');
for i = 1:size(t,1),
    trilist(i) = tri;
end
trilist = trilist';
clear arraye arrayp counte countp i ipnt j jpnt pshare tri

%% compute geometry for points
pnt = struct('tri', [], 'xy', []);
% pnt.tri: triangles that possess a given point
% pnt.xy : coordinates of point, same data as p
for i = 1:size(p, 1),
    cmp = (t(:, 1:3) == i);
    pnt.tri = find( any(cmp') );
    pnt.xy  = p(i,:);
    pntlist(i) = pnt;
end
clear i pnt cmp

%% compute triangle centroids and areas
% store the centroid value x, y in the 5th and 6th cols of t
%   also store in trilist.centxy
% store the area value in the 7th col of t
%   also store in trilist.area
t(:,5:7) = 0;
for i = 1:size(t,1),
    pnt = t(i, 1:3);
    t(i,5:6) = sum(p(pnt,:))/3;
    trilist(i).centxy = t(i,5:6);
    pxy = p(pnt,:);
    a = [pxy(1,:)-pxy(2,:), 0];
    b = [pxy(1,:)-pxy(3,:), 0];
    area = sum(abs(cross(a,b)));
    t(i,7) = area/2;
    trilist(i).area = t(i,7);
end
clear i pnt pxy a b area

%% apply material properties
trilist = specify_material_property( trilist );

%% apply boundary types
interiorlist = [16,19,22,24,25,26,27,28];
for i = 1 : size(e,1),
    if any(abs(e(i,5)-interiorlist)<1e-5),
        pntlist(e(i,1)).bndtype = 'INT';
        pntlist(e(i,2)).bndtype = 'INT';
    else
        pntlist(e(i,1)).bndtype = 'EXT';
        pntlist(e(i,2)).bndtype = 'EXT';
    end
end



