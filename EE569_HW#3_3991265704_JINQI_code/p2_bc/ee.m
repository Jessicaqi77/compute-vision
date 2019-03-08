EE=imread('2_a_1.png');
EE(EE==0) = 1;  
EE(EE==255) = 0; 
EE=single(EE);
save EE.mat