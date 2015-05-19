% explicit elimination for antena
load ../data/antena_assembly.mat;
% bndtype: 0 for no-boundary point, 1 for exterior boundary point, -1 for
% interior boundary point
bndtype = zeros(numel(pntlist),1);
for ii = 1:numel(pntlist),
    if strcmp( pntlist(ii).bndtype, 'EXT' ),
        bndtype(ii) = 1;
    elseif strcmp( pntlist(ii).bndtype, 'INT' ),
        bndtype(ii) = -1;
    end
end

nob_index = find(bndtype==0);
ext_index = find(bndtype==1);
int_index = find(bndtype==-1);

u_int = 0 * ones(numel(int_index),1);
u_ext = 1 * ones(numel(ext_index),1);

A1bar = A(nob_index,nob_index);
A2bar = A2(nob_index,nob_index);

f1_ext = A(nob_index,ext_index) * u_ext;
f1_int = A(nob_index,int_index) * u_int;
f1 = f1_ext+f1_int;

f2_ext = A2(nob_index,ext_index) * u_ext;
f2_int = A2(nob_index,int_index) * u_int;
f2 = f2_ext+f2_int;

count = 1;
for  k2 = linspace(0, 2e3, 200),
    Alin = A1bar - k2*A2bar;
    f = k2*f2 - f1;

    %% solve either eigenvalue or Au=f problems

    % [V,D] = eig(A1bar, A2bar);
    u = Alin \ f;

    ufull = zeros(numel(pntlist),1);
    % ufull(nob_index) = V(:,4);
    ufull(nob_index) = u;
    ufull(ext_index) = u_ext;
    ufull(int_index) = u_int;
    ufull = abs(ufull);
    filename = sprintf('../figs/driven/%01d.mat',count);
    save(filename,'k2','ufull','p');
    % solve Alin * u = f;

    % plotsol;
    count = count+1;
end
