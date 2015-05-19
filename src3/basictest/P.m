function result = P(i,n,zeta)
    result = 1;
    if i==0
        return;
    end
    for s = 0:i-1,
        result = result .* (n*zeta-s);
    end
    result = result / prod(1:i);
end