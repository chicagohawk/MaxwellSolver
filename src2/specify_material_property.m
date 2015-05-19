% specify material properties elementwise
% very case dependent, ready to modify
function trilist = specify_material_property( trilist )
    for i = 1 : numel(trilist),
        trilist(i).a = sin( 3*trilist(i).centxy(1) ) + 1.2;
    end
end