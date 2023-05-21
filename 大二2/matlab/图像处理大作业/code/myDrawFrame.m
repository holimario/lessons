function image=myDrawFrame(facepos,input)
image=input;

for i=1:size(facepos,1)
    if(~isempty(facepos))
        image(facepos(i,1):facepos(i,1)+facepos(i,3)-1,facepos(i,2),1)=255;
        image(facepos(i,1):facepos(i,1)+facepos(i,3)-1,facepos(i,2),2)=0;
        image(facepos(i,1):facepos(i,1)+facepos(i,3)-1,facepos(i,2),3)=0;
        image(facepos(i,1):facepos(i,1)+facepos(i,3)-1,facepos(i,2)+facepos(i,4)-1,1)=255;
        image(facepos(i,1):facepos(i,1)+facepos(i,3)-1,facepos(i,2)+facepos(i,4)-1,2)=0;
        image(facepos(i,1):facepos(i,1)+facepos(i,3)-1,facepos(i,2)+facepos(i,4)-1,3)=0;
        image(facepos(i,1),facepos(i,2):facepos(i,2)+facepos(i,4)-1,1)=255;
        image(facepos(i,1),facepos(i,2):facepos(i,2)+facepos(i,4)-1,2)=0;
        image(facepos(i,1),facepos(i,2):facepos(i,2)+facepos(i,4)-1,3)=0;
        image(facepos(i,1)+facepos(i,3)-1,facepos(i,2):facepos(i,2)+facepos(i,4)-1,1)=255;
        image(facepos(i,1)+facepos(i,3)-1,facepos(i,2):facepos(i,2)+facepos(i,4)-1,2)=0;
        image(facepos(i,1)+facepos(i,3)-1,facepos(i,2):facepos(i,2)+facepos(i,4)-1,3)=0;
    end
end
end