/*��N ̨��������i ̨�����Ĺ�������ΪAi���ƻ�һЩ������ʹ�ù���Ч�ʱ�͡�����ѡȡһ�α�������Ļ�����ʹ����ֹͣ������
�������ƻ�һ�Σ������޷��ƻ���һ̨�����һ̨������������ʣ�»����Ĺ���Ч�ʵ�ƽ������С�����ٱ����ƻ�һ̨������
�������ʽ��
���ļ�sabotage. in �ж������ݡ��������ݵ�һ����1 ������N�ڶ���N ����������i ����Ai
�������ʽ��
������ļ�sabotage. out �С��������Ϊһ�У���Сƽ��Ч�ʣ�������С�����3 λ
������1 ���롿
5
5 1 7 8 2
������1 �����
2.667
Ps:����40% �����ݣ�N<=1000,����100% ���ݣ�N<=100000 Ai <= 10000*/
#include<bits/stdc++.h>
#define rg register
using namespace std;
int n,a[100001];
double ba(int x,int y)
{
	double sum=0;
	for(rg int i=1;i<x;i++) sum+=a[i];
	for(rg int i=y+1;i<=n;i++) sum+=a[i];
	return sum/(n-(y-x+1));
}
int main()
{
	freopen("sabotage.in","r",stdin);
	freopen("sabotage.out","w",stdout);
	double ans=10001;
	scanf("%d",&n);
	for(rg int i=1;i<=n;i++) scanf("&d",&a[i]);
	for(rg int i=2;i<n;i++)
	for(rg int j=i;j<n;j++) if(ba(i,j)<ans) ans=ba(i,j);
	printf("%.3lf\n",ans);
}
