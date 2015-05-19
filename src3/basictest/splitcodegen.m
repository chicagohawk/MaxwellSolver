% all combinations that put n numbers into m bits
%   e.g. n = 3, m = 3, returns
%     003 300 030 102 012 201 111 021 210 120
function bits = splitcodegen(n, m)
    if n == 0,
        bits = zeros(1,m);
        return;
    end
    
    if m == 1,
        bits = n;
        return;
    end
    
    bits = [];
    for ii = 0 : n,    % number put in first bit
        subcode = splitcodegen(n-ii, m-1);
        num = size(subcode,1);
        combcode = [ii * ones(num,1), subcode];
        bits = [bits; combcode];
    end
    
    return;
end