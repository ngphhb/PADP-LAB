#include<stdio.h>
#include<gd.h>
#include<omp.h>

void main(int argc,char* argv[]){
int x,y,w,h,c,r,g,b,t,tid;
t=r=g=b=c=x=w=h=y=0;
gdImagePtr img;
FILE *fp = NULL;
char *in = NULL,*on = NULL;
if(argc!=3){
printf("\nerror argc ! 3\n");
exit(0);
}
else{
in = argv[1]; on = argv[2];
}


if( ( fp = fopen(in,"r")) == NULL){
printf("\n error cant open file \n");
exit(0);
}
else{
img = gdImageCreateFromPng(fp);
w = gdImageSX(img);
h = gdImageSY(img);
}
double time = omp_get_wtime();

omp_set_num_threads(4);


#pragma omp parallel for shared(c,r,g,b,y) schedule(static,50)
for(x=0;x<w;x++)
for(y=0;y<h;y++){
c=gdImageGetPixel(img,x,y);
r=gdImageRed(img,c);
g=gdImageGreen(img,c);
b=gdImageBlue(img,c);
t=(r+g+b)/3;
r = g = b = t;
tid = omp_get_thread_num();
if(tid==0){
c = gdImageColorAllocate(img,r,0,0);
gdImageSetPixel(img,x,y,c);
}
if(tid==1){
c = gdImageColorAllocate(img,0,g,0);
gdImageSetPixel(img,x,y,c);
}
if(tid==2){
c = gdImageColorAllocate(img,0,0,b);
gdImageSetPixel(img,x,y,c);
}
if(tid==3){
c = gdImageColorAllocate(img,0,0,0);
gdImageSetPixel(img,x,y,c);
}
//c = gdImageColorAllocate(img,t,t,t);
//gdImageSetPixel(img,x,y,c);
}

time = omp_get_wtime() - time;

if( (fp = fopen(on,"w")) == NULL){
printf("\n error cant open w file \n");
exit(0);
}
else{
gdImagePng(img,fp);
fclose(fp);
}
gdImageDestroy(img);
printf("%lf",time);

}
