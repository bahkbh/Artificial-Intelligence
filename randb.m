function output = randb(dimension), 
% Binary random variable
% This function returns only a vector. 

y = rand(dimension,1); 
output(find(y>=0.5))=1; 
output(find(y<0.5))=0; 


