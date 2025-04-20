#include<stdio.h>
void main(){
	int in,out,bkt,n,stord=0,time=0;
	printf("Enter the size of bucket: ");
	scanf("%d",&bkt);
	printf("Enter the output rate: ");
	scanf("%d",&out);
	printf("Enter the number of packets: ");
	scanf("%d",&n);
	while(1){
		if(n==0 && stord==0)break;
		if(stord==0){
			printf("Enter the size of incoming packet: ");
			scanf("%d",&in);
			n--;
				if(in>bkt){
				printf("Packet rejected since packet size is greater than bucket size\n");
				continue;
			}
			stord = in;

		}
		time++;
		printf("---------------------------------------\n");
		printf("\t\t\tAt time %d\n",time);

		if(stord<out){
			printf("Packet of size %d delivered\n",stord);
			printf("---------------------------------------\n");
			stord=0;
			continue;
		}
		printf("Packet of size %d delivered\n",out);
		printf("---------------------------------------\n");
		stord-=out;
	}

}