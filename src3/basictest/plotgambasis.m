% plot the vector basis fields associate with each column of Gamma
function plotgambasis(tri, xtri, ytri, A)
    %% natural coordinates
    quivpnt = [ [xtri', ytri']; tri.edge(1).midp; tri.edge(2).midp; ...
                tri.edge(3).midp; [mean(xtri), mean(ytri)] ];
    F = 1 / A * [1 1 1; xtri; ytri];
    Z = 1 / A * inv(F) * [ones(size(quivpnt,1),1), quivpnt]';
    
    %% 0 order vector basis
    
    % plot first vector basis
    G1 = [zeros(1, size(quivpnt,1)); -tri.edge(1).len * Z(3, :); tri.edge(1).len * Z(2, :)];
    vecx1 = - 1 / A * [0, 1, 0] * inv(F') * G1;
    vecy1 = - 1 / A * [0, 0, 1] * inv(F') * G1;
    quiver(quivpnt(:,1), quivpnt(:,2), vecx1', vecy1', 'Linestyle', '-.', 'color', 'red');
    
    % plot second vector basis
    G2 = [tri.edge(2).len * Z(3, :); zeros(1, size(quivpnt,1)); -tri.edge(2).len * Z(1, :)];
    vecx2 = - 1 / A * [0, 1, 0] * inv(F') * G2;
    vecy2 = - 1 / A * [0, 0, 1] * inv(F') * G2;
    quiver(quivpnt(:,1), quivpnt(:,2), vecx2', vecy2', 'Linestyle', '-.', 'color', 'black');
    
    % plot third vector basis
    G3 = [-tri.edge(3).len * Z(2, :); tri.edge(3).len * Z(1, :); zeros(1, size(quivpnt,1))];
    vecx3 = - 1 / A * [0, 1, 0] * inv(F') * G3;
    vecy3 = - 1 / A * [0, 0, 1] * inv(F') * G3;
    quiver(quivpnt(:,1), quivpnt(:,2), vecx3', vecy3', 'Linestyle', '-.', 'color', 'green');
    
    % plot mixture vector
    e = [0.2,0.4,0.3];
    vecxmix = vecx1 * e(1) + vecx2 * e(2) + vecx3 * e(3);
    vecymix = vecy1 * e(1) + vecy2 * e(2) + vecy3 * e(3);
%    quiver(quivpnt(:,1), quivpnt(:,2), vecxmix', vecymix', 'Linestyle', '-.', 'color', 'cyan');
    
    % curl of the three gamma basis
    FTinv = inv(F');
    
    curl1 =    FTinv(2,2) * tri.edge(3).len * tri.edge(3).nvec(2) ...
             - FTinv(2,3) * tri.edge(2).len * tri.edge(2).nvec(2) ...
             - FTinv(3,2) * tri.edge(3).len * tri.edge(3).nvec(1) ...
             + FTinv(3,3) * tri.edge(2).len * tri.edge(2).nvec(1);
    curl1 = curl1 / A^2;  curl1
    
    curl2 =  - FTinv(2,1) * tri.edge(3).len * tri.edge(3).nvec(2) ...
             + FTinv(2,3) * tri.edge(1).len * tri.edge(1).nvec(2) ...
             + FTinv(3,1) * tri.edge(3).len * tri.edge(3).nvec(1) ...
             - FTinv(3,3) * tri.edge(1).len * tri.edge(1).nvec(1);
    curl2 = curl2 / A^2;  curl2
    
    curl3 =    FTinv(2,1) * tri.edge(2).len * tri.edge(2).nvec(2) ...
             - FTinv(2,2) * tri.edge(1).len * tri.edge(1).nvec(2) ...
             - FTinv(3,1) * tri.edge(2).len * tri.edge(2).nvec(1) ...
             + FTinv(3,2) * tri.edge(1).len * tri.edge(1).nvec(1);
    curl3 = curl3 / A^2;  curl3
    
    % div of the three gamma basis
    div1 =    FTinv(2,2) * tri.edge(3).len * tri.edge(3).nvec(1) ...
            - FTinv(2,3) * tri.edge(2).len * tri.edge(2).nvec(1) ...
            + FTinv(3,2) * tri.edge(3).len * tri.edge(3).nvec(2) ...
            - FTinv(3,3) * tri.edge(2).len * tri.edge(2).nvec(2);
    div1 = div1 / A^2;  div1
    
    div2 =  - FTinv(2,1) * tri.edge(3).len * tri.edge(3).nvec(1) ...
            + FTinv(2,3) * tri.edge(1).len * tri.edge(1).nvec(1) ...
            - FTinv(3,1) * tri.edge(3).len * tri.edge(3).nvec(2) ...
            + FTinv(3,3) * tri.edge(1).len * tri.edge(1).nvec(2);
    div2 = div2 / A^2;  div2
   
    div3 =    FTinv(2,1) * tri.edge(2).len * tri.edge(2).nvec(1) ...
            - FTinv(2,2) * tri.edge(1).len * tri.edge(1).nvec(1) ...
            + FTinv(3,1) * tri.edge(2).len * tri.edge(2).nvec(2) ...
            - FTinv(3,2) * tri.edge(1).len * tri.edge(1).nvec(2);
    div3 = div3 / A^2;  div3
    
    
    
%     %% 1 order vector basis, only plot two added bases for unisolvence
%     
%     G1unis = [4 * Z(2, :) .* Z(3, :); zeros(2, size(quivpnt,1))];
%     vecx = - 1 / A * [0, 1, 0] * inv(F') * G1unis;
%     vecy = - 1 / A * [0, 0, 1] * inv(F') * G1unis;
%     quiver(quivpnt(:,1), quivpnt(:,2), vecx', vecy', 'Linestyle', '-.', 'color', 'red');
%     
%     G2unis = [zeros(1, size(quivpnt,1)); 4 * Z(1, :) .* Z(3, :); zeros(1, size(quivpnt,1))];
%     vecx = - 1 / A * [0, 1, 0] * inv(F') * G2unis;
%     vecy = - 1 / A * [0, 0, 1] * inv(F') * G2unis;
%     quiver(quivpnt(:,1), quivpnt(:,2), vecx', vecy', 'Linestyle', '-.', 'color', 'black');
    
end