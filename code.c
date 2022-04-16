#include<reg52.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit A1 = P0^0;
sbit A2 = P0^1;//�ҵ������
sbit B1 = P0^3;
sbit B2 = P0^2;//��������

sbit h_l = P0^4;
sbit h_r = P0^5;
sbit h_f = P0^6;//�����ӦоƬ�ӿں� 

struct U_dot{//����㣺2/3������е�
int L,F,R;//��ǰ�� 
int choose;//case��
}; 
struct U_dot u[12];//��������� 
int n=0;//��������0/1/2������  
int l=0;//��ֹƵ��ͬ�� 

void delayms(uint xms){//�������ƣ�void delayms(uint xms)���������ܣ���ʱxms����
	uint x,y;
	for(x=xms;x>0;x--)
		for(y=110;y>0;y--);
}
void car_direction(uchar num){//�������ƣ�void car_direction(uchar num)���������ܣ�С�����߷���
	switch(num){
		case 0:A1 = 0;A2 = 0;B1 = 0;B2 = 0;break;//ֹͣ
		case 1:A1 = 1;A2 = 0;B1 = 1;B2 = 0;break;//��ǰ
		case 2:A1 = 0;A2 = 1;B1 = 0;B2 = 1;break;//���
		case 3:A1 = 0;A2 = 1;B1 = 1;B2 = 0;break;//ת�� 
		case 4:A1 = 1;A2 = 0;B1 = 0;B2 = 1;break;//ת�� 
	}
}
void front(){
	car_direction(0);  delayms(2);
	car_direction(1);  delayms(8);//���ٶ�
	//car_direction(4);  delayms(3);
} 
void turn_l(){//��ת��
	    car_direction(0);
			delayms(300);
			car_direction(3);
			delayms(450);
			car_direction(0);
			delayms(300); 
    while(h_l==1){
		if(h_f==0){
			car_direction(0);
			delayms(300);
			car_direction(3);
			delayms(200);
			//car_direction(0);
			//delayms(50);
		}
		else front();
	}
}
void turn_r(){//��ת����
	    car_direction(0);
			delayms(300);
			car_direction(4);
			delayms(450);
			car_direction(0);
			delayms(300);
    while(h_r==1){
		if(h_f==0){
			car_direction(0);
			delayms(300);
			car_direction(4);
			delayms(200);
			//car_direction(0);
			//delayms(50);
		}
		else front();//!!!
	}
}
void back(){
//!(h_l==1&&h_r==1)&&(a[(n--)-1].L==0&&a[(n--)-1].F==0&&a[n-1].R==0)  
	int i=0,c=0;
  do{
		    if(n==-1)n=11;
				if(i!=0){
					if(c==4){while(h_l==1)car_direction(2);}
					else if(c==3){while(h_r==1)car_direction(2);}
        }
  	    while(h_l==0 && h_r==0){car_direction(2);}//����
			  if(h_l==1 || h_r==1){//��������� 
					car_direction(2); delayms(300);
					if(u[n-1].choose!=1){//��������̽�� 
						if(u[n-1].choose==3){car_direction(3); delayms(600); c=3;}
						else if(u[n-1].choose==4){car_direction(4); delayms(500); c=4;}
						//��������̽��
				  }
				  i=1;	
			  }	
	}while(u[(n--)-1].L==0&&u[(n--)-1].F==0&&u[(n--)-1].R==0);	
} //�˻�����һ�������ԭ״̬ 
void main(){//�������ܣ�������	
  while(1){ //�ȴ������źŲ������ж�����ǰ����	
	if(n==12)n=0;
	if(h_l==0&&h_f==1&&h_r==0){front();}
	else if (h_l==1&&h_f==0&&h_r==0){
			turn_l();
			u[n].L=0; u[n].F=0; u[n].R=0; u[n].choose=4;
		  n++;//choose ����һ�λ���Ӧ��ת��
	}
	else if (h_l==0&&h_f==0&&h_r==1){
			turn_r();
			u[n].L=0;u[n].F=0; u[n].R=0; u[n].choose=3;n++;
	}
	else if (h_l==1&&h_f==1&&h_r==0){
			front();
			u[n].L=1; u[n].F=0; u[n].R=0; u[n].choose=1;n++;
	}
	else if (h_l==0&&h_f==1&&h_r==1){
		  front(); 
		  u[n].L=0; u[n].F=0; u[n].R=1; u[n].choose=1;n++;
	}
	else if (h_l==1&&h_f==0&&h_r==1){
			u[n].F=0;
			if(l==0){
			turn_l(); u[n].L=0; u[n].R=1; l++; u[n].choose=4; n++; 
			}
			else{
			turn_r(); u[n].L=1; u[n].R=0; l--; u[n].choose=3; n++; 	
			}
	}
	else if (h_l==1&&h_f==1&&h_r==1){
			front(); 
			u[n].L=1; u[n].F=0; u[n].R=1; u[n].choose=1;n++;
	}
	else if (h_l==0&&h_f==0&&h_r==0){
		  back(); 
		  if(u[n].L==1){
		    turn_l(); u[n].L=0; u[n].choose=4; n++;
		}
		  else if(u[n].R==1){
		    turn_r(); u[n].R=0; u[n].choose=3; n++;
		}
	}
  }
}
//��������μ�¼�����ų� 
