% make movie
fig1=figure(1);
winsize = get(fig1,'Position');
winsize(1:2) = [0 0];
movies=moviein(30,fig1,winsize);
set(fig1,'NextPlot','replacechildren');
frame = 1;

for ii = 1:200,
    filename = sprintf('../figs/driven/%01d.mat',ii);
    load(filename);
    plotFEM; drawnow;
    movies(:,frame)=getframe(fig1);
    hold off;
    frame = frame + 1;
end

movie(fig1,movies,1,1,winsize);
movie2avi(movies,'../figs/driven/movie.avi','fps',18);