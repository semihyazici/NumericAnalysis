#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define size 20

void ust_ucgen(float arr[size][size],int row,float sbt[size]){
	
	int i,j,k,count,count1;
	float cofac,tmp;
	static float x[size];

	
	for(i=0;i<row;i++){
		count=0;
		while(count!=i){
			cofac=arr[i][count]/arr[count][count];
			for(j=0;j<row;j++){
				if(arr[i][j]!=0) {
					 arr[i][j]=arr[i][j]-(cofac*arr[count][j]);				///çalýþýyor 0 olmadýðý takdirde düzelt onu
				}
				
			}
			sbt[i]=sbt[i]-(cofac*sbt[count]);
			count++;
		}
		cofac=arr[i][i];
		for(k=count;k<row;k++){				//k=count
			
			arr[i][k]=arr[i][k]/cofac;
		}
		sbt[i]/=cofac;
	}
}
void yer_degistirme(float arr[size][size],int row,float sbt[size]){
	static int i,j,max[size],k;
	float tmp,fake_arr[size][size],fake_sbt[size];	
	for(i=0;i<row;i++){
		tmp=arr[i][0];
		for(j=0;j<row;j++){	
			if(tmp<arr[i][j]) {
				max[i]=j;	
				tmp=arr[i][j];
			}
		}
		if(tmp==arr[i][0]) max[i]=0;
	}
		
	for(i=0;i<row;i++){
		for(j=0;j<row;j++){
			fake_arr[max[i]][j]=arr[i][j];
			fake_sbt[max[i]]=sbt[i];
		}
	}
	
	for(i=0;i<row;i++){
		for(j=0;j<row;j++){
			arr[i][j]=fake_arr[i][j];
		}
	}
	printf("\n");
	for(i=0;i<row;i++) sbt[i]=fake_sbt[i];
	
		
}
float rt(float arr[size][size],int row,float sbt[size],float num[size],int loc){
	int i;
	float root=0;									//gelen x1 x2leri ayný kabul ettim düzeltme yap!!
	for(i=0;i<row;i++){								//gelecek baþ deðerler için dizi yap
		if(i!=loc) root+=((arr[loc][i])*(num[i]));	//tek tarafa atma
	}
	root=(-1)*root;
	root=root+sbt[loc];
	root/=arr[loc][loc];
	return root;
}
float determinant(float arr[size][size],int row){
	int i,j,k,i1,i2;
	float fake_arr[size][size];
	float value=0;
	int factor=1,tmp=0;
	if(row == 1) {
		value=arr[0][0];
		return value;			
	}
	if(row == 2){
		value=(arr[0][0]*arr[1][1])-(arr[0][1]*arr[1][0]);
		return value;
	}
	
	if(row == 3){
							//sarrus kuralý
		value=(arr[0][0]*arr[1][1]*arr[2][2])+(arr[0][1]*arr[2][0]*arr[1][2])+(arr[0][2]*arr[1][0]*arr[2][1])-(arr[0][0]*arr[1][2]*arr[2][1])-(arr[0][1]*arr[1][0]*arr[2][2])-(arr[0][2]*arr[2][0]*arr[1][1]);																	
		return value;
	}
	
	else{
		for(i=0;i<row;i++){
			i1=0,i2=0;
			for(j=1;j<row;j++){
				for(k=0;k<row;k++){
					
					if(k!=i){
						fake_arr[i1][i2]=arr[j][k];
						if(i2==row-2){
							i1++;
							i2=0;
						}
						else i2++;	
					}
				}
			}
			value=value+(arr[0][i]*factor*determinant(fake_arr,row-1));
			factor=-1*(factor);
		}
		
	}
	
	
	return value;
}
void cramer(float arr[size][size],int row,float sbt[size]){
	float det=determinant(arr,row);
	int i,j,k,tmp=0;
	float x[size];
	float fake_arr[size][size];
	for(i=0;i<row;i++){
		for(j=0;j<row;j++){
			for(k=0;k<row;k++){
					
				if(j==tmp){
					fake_arr[k][j]=sbt[k];
				}
				else fake_arr[k][j]=arr[k][j];
			}
		}
		tmp++;
		x[i]=determinant(fake_arr,row)/det;
		printf("x%d=%.f\n",i+1,x[i]);
	}	
}
void gauss_eli(float arr[size][size],int row,float sbt[size]){
	int i,j,k,count;
	float cofac,tmp;
	static float x[size];
	
		////buraya kadar üst üçgen haline getirdi
	ust_ucgen(arr,row,sbt);
	
	for(i=row-1;i>=0;i--){
		
		for(j=row-1;arr[i][j]!=0;j--){
			count=0;
			if(i==row-1){
				x[i]=sbt[i];
			} 	
			else{
				if(arr[i][j]!=1){
				cofac=x[j];
				x[i]+=arr[i][j]*cofac;
				}
				else 	x[i]=sbt[i]-x[i];
				
				
			}
			
		}
		
	}
	
	for(i=0;i<row;i++){
		printf("x%d=%.3f\t",i+1,x[i]);
	}

	
}
void gauss_jordan_eli(float arr[size][size],int row,float sbt[size]){
	int i,j,count;
	float cofac;
	ust_ucgen(arr,row,sbt);
	for(i=row-1;i>=0;i--){
		for(j=i-1;j>=0;j--){
			cofac=arr[j][i];
			arr[j][i]=0;
			sbt[j]=sbt[j]-(sbt[i]*cofac);
		}

	}

	for(i=0;i<row;i++){
		printf("x%d=%.3f  ",i+1,sbt[i]);
	}
	

	
}
void jacobi(float arr[size][size],int row,float sbt[size],float eps,float num){
	yer_degistirme(arr,row,sbt);
	int i,iter=1;
	float x[size],tmp[size];
	int cont=0,cont1;
	for(i=0;i<row;i++)	tmp[i]=num;
	while(cont==0){
		if (tmp[1]==num){					//tmp[1]di önceden hata olabilir
			for(i=0;i<row;i++){
				x[i]=rt(arr,row,sbt,tmp,i);
			} 
		}
		else{
			for(i=0;i<row;i++){
				x[i]=rt(arr,row,sbt,tmp,i);
			} 			
		}
			
		for(i=0;i<row;i++){
			if(fabs(x[i]-tmp[i])>eps){
				cont1=1;
				break;
			}
			else if(fabs(x[i]-tmp[i])<=eps&&i!=row) cont1=2;
		}
	 if(cont1==1) cont=0;
	 else cont=1;
	 int sayac=1;
	 printf("%d ",iter);
	 for(i=0;i<row;i++){
	 	printf("x%d=%.3f\t",sayac,x[i]);
	 	sayac++;
	 } 
	 
	 printf("\n");
	 for(i=0;i<row;i++){
			tmp[i]=x[i];
			} 
			iter++;
	}
}
void gauss_seidal(float arr[size][size],int row,float sbt[size],float eps,float num){
	yer_degistirme(arr,row,sbt);
	
	int i,iter=1;
	float x[size],tmp[size],tmp1[size];
	int cont=0,cont1;
	for(i=0;i<row;i++){
		tmp[i]=num;
		tmp1[i]=num;
	}
	while(cont==0){
		if (tmp[0]==num){
			for(i=0;i<row;i++){
				x[i]=rt(arr,row,sbt,tmp1,i);
				tmp1[i]=x[i];
			} 
		}
		else{
			for(i=0;i<row;i++){
				x[i]=rt(arr,row,sbt,tmp1,i);
				tmp1[i]=x[i];
			} 			
		}
			
		for(i=0;i<row;i++){
			if(fabs(x[i]-tmp[i])>eps){
				cont1=1;
				break;
			}
			else if(fabs(x[i]-tmp[i])<=eps&&i!=row) cont1=2;
		}
	 if(cont1==1) cont=0;
	 else cont=1;
	 int sayac=1;
	 

	 
	 printf("%d ",iter);
	 for(i=0;i<row;i++){
	 	printf("x%d=%.3f\t",sayac,x[i]);
	 	sayac++;
	 } 
	 
	 printf("\n");
	 for(i=0;i<row;i++){
			tmp[i]=x[i];
			} 
			iter++;
	}
	
	
}
/*
void cholesky(float arr[size][size],int row,float sbt[size]){
	static float upper[size][size],lower[size][size];
	int i,j,k;
	int count=0;
	for(i=0;i<row;i++) {
	lower[i][0]=arr[i][0];
	upper[i][i]=1;
	}
	for(i=1;i<row;i++) upper[0][i]=arr[0][i]/lower[0][0];
	
	for(i=0;i<row;i++){
		for(k=0;k<row;k++){										//top = arr[i][j]*arr1[j][k]
			for(j=0;j<row;j++){									//matris3 e ata
				
				
			if()
				
			}
		}
	}
	
	
	
	
	
}
*/
int main(){
	//gauss eli/jacobi/üst üçgen/cramer/det/tek köþeye atma/gauss jordan/yer degistirme/gauss seidal/
	//
	//
	float eps=0.02;
	int i,j;
	int row=3;
	float arr[size][size]={{3,2,-1},{1,-1,5},{2,1,0}};			
	float arr1[size][size]={{2,3,5},{1,0,1},{2,1,0}};		//9     3*3 doru
	float arr2[size][size]={{1,2},{2,5}};
	float arr3[size][size]={{1,2,3,-4,5},{6,-7,8,9,10},{-1,2,3,4,5},{6,7,8,9,-10},{10,5,1,0,-4}};
	float arr4[size][size]={{2,-3,2},{1,1,-2},{3,-2,-1}};
	float sbt[size]={9,-8,1};
	float arr5[size][size]={{3.6,2.4,-1.8},{4.2,-5.8,2.1},{0.8,3.5,6.5}};
	float arr6[size][size]={{3,1,-2},{-1,4,-3},{1,-1,4}};
	float arr7[size][size]={{10,-1,2,0},{-1,11,-1,3},{2,-1,10,-1},{0,3,-1,8}};
	float arr8[size][size]={{1,6,3},{2,1,4},{5,-2,1}};
	int ar[size]={1,2};
	float sbt1[size]={20,14,8};
//	jacobi(arr6,row,sbt,eps,1);
	jacobi(arr6,row,sbt,eps,1);
	float arr10[size][size]={{1,4,-1},{1,1,-6},{3,-1,-1}};
//	gauss_jordan_eli(arr10,row,sbt);
//	yer_degistirme(arr8,row,sbt);
	
	

	
	

	
	
	return 0;
}
