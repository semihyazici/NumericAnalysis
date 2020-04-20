#include<stdio.h>
#include<math.h>
#define e 2,71828182
double g(double x){
	return x;														//basit iterasyon gibi kurallar için
}
double f(double x){													//kök kullanmak gerekirse sqrt fonk kullan
	return  log(x);														
}
double diff(double x){
	return 3*x*x-5;														//türevi yaz
}
double bisection(double x1 ,double x2,double eps){
	double mid=(x1+x2)/2;
	double y1=f(x1);												//bisection,fixed point,newton raphson,regula falsi,kiris tamam
	double y2=f(x2);
	double y3=f(mid);
	int iter=1;	
	while(fabs(y3)>eps){
		printf("%d->x1=%lf f(x1)=%lf  x2=%lf f(x2)=%lf  x3=%lf f(x3)=%lf \n",iter,x1,f(x1),x2,f(x2),mid,f(mid));
		if(y3==0){
			return mid;
		}
		if(y3<0&&y2<0){
			x2=mid;
		}
		else if(y3<0&&y1<0){
			x1=mid;
		}
		else if(y3>0&&y2>0){
			x2=mid;
		}
		else if(y3>0&&y1>0){
			x1=mid;
		}
		if(fabs(y3)<=eps) return mid;
		mid =(x1+x2)/2;
		y1=f(x1);
		y2=f(x2);
		y3=f(mid);
		iter++;	
	}
//	return x1;
}
double fixed_point(double x0,double eps){
	double y0=g(x0);
	double y1=f(x0);
	double x1=f(x0);
	int iter=1;
	while(eps<fabs(y0-y1)){
		printf("x%d=%lf  %lf\n",iter,y1,fabs(y0-y1));
		y0=g(x1);
		y1=f(x1);
		x1=f(x1);
		iter++;
	}
	
	return y1;
}
double newton_raphson(double x0,double eps){
	double x1=x0-(f(x0)/diff(x0));
	int iter=1;
	
	
	while(eps<fabs(x1-x0)){
		x0=x1;	
		x1=x0-(f(x0)/diff(x0));
		printf("x%d=%lf  %lf\n",iter,x0,fabs(x1-x0));
		iter++;
	}
	
	return x1;
}
double regula_falsi(double a,double b,double eps){
	
	double c=b-((f(b)*(b-a))/(f(b)-f(a)));
	int iter=1;														//sorunlu
	
	while(fabs(f(c))>eps){
		
		if(f(a)<0&&f(c)<0){
			a=c;
		}
		else if(f(a)>0&&f(c)>0){
			a=c;
		}
		else if(f(b)<0&&f(c)<0){
			b=c;
		}
		else if(f(b)>0&&f(c)>0){
			b=c;
		}
		/*
		else{
			return c;
		}*/
		c=b-((f(b)*(b-a))/(f(b)-f(a)));
		printf("x%d=%lf  %lf\n",iter,c,fabs(f(c)));
		iter++;
	}	
	return c;
}
double kiris(double x0,double x1,double eps){
	double y0=f(x0);
	double y1=f(x1);
	double x2=x1-((x1-x0)/(y1-y0))*y1;
	double y2=f(x2);
	printf("when x is %lf equal is %lf\n",x2,f(x2));
	//double tmp;
	while(fabs(y2)>eps){
		if(y2==0) return x2; 
		x0=x1;
		x1=x2;
		y0=f(x0);
		y1=f(x1);
		x2=x1-((x1-x0)/(y1-y0))*y1;
		y2=f(x2);
		printf("when x is %lf equal is %lf\n",x2,f(x2));
	}
	
	return x2;
}
double graph(double x0,double varia,double eps){
	float x1=x0+varia;
	int iter=0;
	while(fabs(f(x1)-f(x0))>eps){
		printf("x%d:%.3f  f(x)=%.3f\t%f\n",iter,x0,f(x0),fabs(f(x1)-f(x0)));
		iter++;
		if(f(x1)==0.000) return x1;
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

int main(){
	double x1,x2,eps;
	
//	double root=bisection(0,10,0.001);

//	double root1=fixed_point(4,0.005);					//log e tabanýnda olduðu zaman graphda artýþ miktarýný düþük tutmak gerek yoksa ýraksar
//	double root2=newton_raphson(-2.5,0.0001);
//	double root3=regula_falsi(1,4,0.001);
//	double root4=kiris(2.5,3,0.01);
//	printf("",graph(1,0.0001,0.001));	
//	printf("root is %lf",f(3.996));
	printf("",graph(0.1,100,0.0047));	
	
	
	return 0;
}
