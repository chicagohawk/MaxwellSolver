% 1 -> (2,3)
% 2 -> (3,1)
% 3 -> (1,2)
function opp_pair = oppositenodes(e)
    opp_pair = [mod(e,3)+1 , mod(e+1,3)+1];
end