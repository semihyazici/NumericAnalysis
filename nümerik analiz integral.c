#include<stdio.h>
#include<math.h>
float f(float x){
	return 3*x*x*x+5*x;
}
float graph(float x0,float varia,float eps){
	float x1=x0+varia;
	int iter=0;	
	while(fabs(f(x1)-f(x0))>eps){
		printf("x%d:%.3f  f(x)=%.3f\t%f\n",iter,x0,f(x0),fabs(f(x1)-f(x0)));
		iter++;
		if(f(x1)==0) return x1;
		if(f(x0)>0&&f(x1)<0){
			varia=varia/2;
			x1=x0+varia;
		}
		if(f(x0)<0&&f(x1)>0){
			varia=varia/2;
			x1=x0+varia;
		}
		
		else{
			x0=x1;	
			x1=x0+varia;
		}
	}
	printf("x%d:%.3f  f(x)=%.3f\t%f\n",iter,x0,f(x0),fabs(f(x1)-f(x0)));
	printf("kok %.3f ile %.3f arasinda\n",x0,x1);
	return x1;
}

float trapes(float n,float x1,float x2){
	float root,i;
	float h,value,tmp;							//- durumunu dene
	/*
	if(f(x1)<0&&f(x2)>0){
		root=graph(x1,0.00001,0.00000001);
		system("cls");
		h=(x1-root)/n;
		for(i=x1+h;i!=root;i=i+h){
			if(i==x1) i+=h;
			tmp=fabs(f(i));
			value+=tmp;
		}
		value*=h;
		value+=((h/2)*(f(x1)+f(root)));
		h=(x2-root)/n;
		for(i=root+h;i!=x2;i=i+h){
			if(i==root) i+=h;
			tmp=fabs(f(i));
			value+=tmp;
		}
		value*=h;
		value+=((h/2)*(f(x2)+f(root)));
	}
	
	*/
	
	
	
	
	
	
		h=(x2-x1)/(n);
	
		for(i=x1+h;i<=x2-h;i=i+h){
			if(i==x1) i+=h;
			tmp=fabs(f(i));
			value+=tmp;
		}
		value*=h;
		value+=((h/2)*(f(x2)+f(x1)));
	
	return value;
}
float simpson(float n,float x1,float x2){
	float h,i,value2=0,tmp,value1=0;
	
	if(f(x1)<0&&f(x2)>0 || f(x1)>0 && f(x2)<0){
		float value=0,value3=0,root;
		root=graph(x1,0.5,0.00001);
		system("cls");
		h=fabs(fabs(root)-fabs(x1))/n;
		for(i=x1+h;i<=root-h;i=i+2*h){
			tmp=fabs(f(i));
			value+=tmp;
		}
		value=4*value;
		for(i=x1+2*h;i<=root-h;i=i+2*h){
			tmp=fabs(f(i));
			value1+=tmp;
		}
		value1=2*value1;
		value1+=fabs(f(x1))+fabs(f(root))+value;
		value1=(value1*h)/3;
		//////
		h=fabs(fabs(root)-fabs(x2))/n;
		for(i=root+h;i<=x2-h;i=i+2*h){
			tmp=fabs(f(i));
			value2+=tmp;
		}
		value2=4*value2;
		for(i=root+2*h;i<=x2-h;i=i+2*h){
			tmp=fabs(f(i));
			value3+=tmp;
		}
		value3=2*value3;
		value2+=fabs(f(x2))+fabs(f(root))+value3;
		value2=(value2*h)/3;
		return value1+value2;
	}
		
		
		if(fabs(x1)==fabs(x2)) h=(2*fabs(x1))/n;
		 
			
		
		else h=fabs(fabs(x1)-fabs(x2))/n;
			
		for(i=x1+h;i<=x2-h;i=i+2*h){
			tmp=fabs(f(i));
			value1+=tmp;
		}
		value1=value1*4;
		for(i=x1+2*h;i<=x2-h;i=i+2*h){
			tmp=fabs(f(i));
			value2+=tmp;
		}
		value2=value2*2;
		value2+=fabs(f(x1))+fabs(f(x2))+value1;
		value2=(value2*h)/3;
		
		return value2;
		


}
int main(){
	//simpson tamam trapes  -durum kontrol et tekrardan
//	printf("%f",trapes(4,0,1));
	printf("%.3lf",simpson(5,-2,4));
	

	
	
	
	return 0;
}
