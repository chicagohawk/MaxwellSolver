syms x1 x2 x3 x4 y1 y2 y3 y4 z1 z2 z3 z4;
F = [1 1 1 1; x1 x2 x3 x4; y1 y2 y3 y4; z1 z2 z3 z4];
F = F / det(F);
inv(F)