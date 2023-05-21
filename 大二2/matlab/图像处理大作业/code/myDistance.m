function dis=myDistance(u,v)
dis=1;

for i=1:size(u,1)
    dis=dis-(u(i,1)*v(i,1))^(0.5);
end
end