% test inhull function
dotproduct;
xy = [xtri;ytri]';
testpnt = 0.3 * randn(100,2);
inside = inhull(testpnt, xy);
hold on;
for ii = 1: 100,
    if inside(ii),
        scatter(testpnt(ii,1), testpnt(ii,2), 10, 'red');
    else
        scatter(testpnt(ii,1), testpnt(ii,2), 10, 'black');
    end
end