% specify numerics on boundaries
% Dirichlet: u^D;    Neumann: f;    Robin: gam, g;
% very case dependent, ready to modify
function trilist = specify_boundary_numerics(trilist, t, p)

    for i = 1 : numel(trilist)
        
        % Dirichlet u^D
        if     strcmpi( trilist(i).bndtype , 'D' ),
            trilist(i).uD  = 1;
        % Neumann f
        elseif strcmpi( trilist(i).bndtype, 'N' ),
            trilist(i).f   = 1;
        % Robin gam, g
        elseif strcmpi( trilist(i).bndtype, 'R' ),
            trilist(i).gam = 1;
            trilist(i).g   = 1;
        end
        
    end
    
end