#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<list>

struct time
{
	int p, art, but, wtt, tat, st;
};

void menu();
int process(struct time a[], int pro, int t);
void ganttchart(struct time a[], int gc[], int pro);
//void monopoly_SJF(int i, int NOP);

void main()
{
	
	int choose;
	do
	{
		menu();
		printf("\nEnter program you want to choose:	");
		scanf_s("%d", &choose);
		switch (choose)
		{
		case 0:
			exit(1);
			break;
		case 1:
		{
			int i, NOP;
			int sum = 0, wt = 0, tat = 0, sum_bt = 0;
			int at[10], bt[10];
			int smallest, time;

			std::list<int> my_list;
			std::list<int> my_list1;
			float avg_wt, avg_tat;
			printf("\nNhap so tien trinh: ");
			scanf_s("%d", &NOP);
			for (int i = 0; i < NOP; i++)
			{
				printf("\n Nhap thoi gian vao va CPU Brust Time[%d]", i + 1);
				printf("\n Thoi gian vao (arrival time): \t");
				scanf_s("%d", &at[i]);
				printf("\nThoi gian CPU BRUST (BRUST TIME):\t");
				scanf_s("%d", &bt[i]);
				sum_bt += bt[i];
			}
			bt[9] = 9999;
			printf("\nTien Trinh \t\t Burst Time \t\t Turn Around Time \t\t Waiting Time ");
			for (time = 0; time < sum_bt;)
			{
				smallest = 9;
				for (i = 0; i < NOP; i++)
				{
					if (at[i] <= time && bt[i] > 0 && bt[i] < bt[smallest])
						smallest = i;
				}
				if (smallest == 9)
				{
					time++;
					continue;
				}
				my_list.push_back(smallest + 1);
				my_list1.push_back(time + bt[smallest]);
				printf("\nTien Trinh [%d] \t\t %d\t\t\t\t %d\t\t\t %d", smallest + 1, bt[smallest], time + bt[smallest], time - at[smallest]);
				wt += time - at[smallest];
				tat += time + bt[smallest];
				time += bt[smallest];
				bt[smallest] = 0;
			}
			avg_wt = wt * 1.0 / NOP;
			avg_tat = tat * 1.0 / NOP;
			printf("\n\n Thoi Gian Xoay Vong Trung Binh (Average Turn Around Time): \t%f", avg_tat);
			printf("\n Thoi Gian Cho Trung Binh (Average Waiting Time): \t%f ", avg_wt);
			printf("\n\n So Do Gantt: \t\n");
			//printf("\n-------------------------------------------------------\n");
			for (int x : my_list) {
				printf("\tP%d\t", x);
			}
			printf("\n");
			printf("0");
			for (int x : my_list1) {
				printf("\t%d\t", x);
			}
			//printf("\n--------------------------------------------------------");
		}break;
		case 2:
		{
			int i, pro, curpro, t = 0, gc[100];
			struct time a[100];
			float avgwt = 0, avgtt = 0;
			printf("Nhap so tien trinh\n");
			scanf_s("%d", &pro);
			for (i = 0; i < pro; i++)
			{
				printf("Nhap Arrival Time & Burst Time cua tien trinh P%d\n", i);
				a[i].p = i;
				scanf_s("%d%d", &a[i].art, &a[i].but);
				a[i].st = 0;
			}

			for (i = 0; i < pro; i++)
			{
				curpro = process(a, pro, t);
				a[curpro].wtt = t - a[curpro].art;
				a[curpro].tat = a[curpro].wtt + a[curpro].but;
				t = t + a[curpro].but;
				avgwt = avgwt + a[curpro].wtt;
				avgtt = avgtt + a[curpro].tat;
				gc[i] = curpro;
			}
			printf("***************************************\n");
			printf("Pro\tArTi\tBuTi\tTaTi\tWtTi\n");
			printf("***************************************\n");
			for (i = 0; i < pro; i++)
			{
				printf("%d\t%d\t%d\t%d\t%d\n", a[i].p, a[i].art, a[i].but, a[i].tat, a[i].wtt);
			}
			printf("***************************************\n");
			ganttchart(a, gc, pro);
			printf("***************************************\n");
			avgwt = avgwt / pro;
			avgtt = avgtt / pro;
			printf("Average Waiting Time : %.2f\n", avgwt);
			printf("Average Turnaround Time : %.2f\n", avgtt);
		}break;
		case 3:
		{
			int i, NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0, at[10], bt[10], temp[10];
			std::list<int> my_list; // chua list P So Do Gantt
			std::list<int> my_list1; // chua list Turn Around Time theo Quatum time So Do Gantt
			// NOP = number of Process
			//quant = quantum time , tat = turn around time , at = arrival time  , bt = CPU burst (Burst time) , wt = waiting time
			float avg_wt, avg_tat;
			printf(" Nhap So Tien Trinh: ");
			scanf_s("%d", &NOP);
			y = NOP;
			for (i = 0; i < NOP; i++)
			{
				printf("\n Nhap Thoi Gian vao Va CPU Burst Time[%d]\n", i + 1);
				printf("Thoi Gian Vao (arrival time): \t");
				scanf_s("%d", &at[i]);
				printf(" \nThoi Gian CPU BURST (Burst time): \t");
				scanf_s("%d", &bt[i]);
				temp[i] = bt[i]; // gan burst time vao temp array  
			}
			printf("Nhap So Vong (Quantum Time): \t");
			scanf_s("%d", &quant);
			printf("\n Tien Trinh \t\t Burst Time \t\t Turn Around Time \t\t Waiting Time ");
			for (sum = 0, i = 0; y != 0; )
			{
				if (temp[i] <= quant && temp[i] > 0)
				{
					sum = sum + temp[i];
					temp[i] = 0;
					count = 1;
					my_list.push_back(i + 1);
					my_list1.push_back(sum);
				}
				else if (temp[i] > 0)
				{
					temp[i] = temp[i] - quant;
					sum = sum + quant;
					my_list.push_back(i + 1);
					my_list1.push_back(sum);
				}
				if (temp[i] == 0 && count == 1)
				{
					y--;
					printf("\nTien Trinh [%d] \t\t %d\t\t\t\t %d\t\t\t %d", i + 1, bt[i], sum - at[i], sum - at[i] - bt[i]);
					wt = wt + sum - at[i] - bt[i];
					tat = tat + sum - at[i];
					count = 0;
				}
				if (i == NOP - 1)
				{
					i = 0;
				}
				else if (at[i + 1] <= sum)
				{
					i++;
				}
				else
				{
					i = 0;
				}
			}

			avg_wt = wt * 1.0 / NOP;
			avg_tat = tat * 1.0 / NOP;
			printf("\n Thoi Gian Xoay Vong Trung Binh (Average Turn Around Time): \t%f", avg_wt);
			printf("\n Thoi Gian Cho Trung Binh (Average Waiting Time): \t%f ", avg_tat);
			printf("\n So Do Gantt: \t\n");
			//printf("\n-------------------------------------------------------\n");
			for (int x : my_list) {
				printf("\tP%d\t", x);
			}
			printf("\n");
			printf("0");
			for (int x : my_list1) {
				printf("\t%d\t", x);
			}
			//printf("\n--------------------------------------------------------");

		}break;
		case 4:
		{
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*int bt[10], at[10], wait_Time_Sum = 0, turn_Time_Sum = 0;
			int time = 0, n, i, smallest, count = 0;
			printf("Nhap so tien trinh : ");
			scanf("%d", &n);
			for (i = 0; i < n; i++)
			{
				printf("Nhap arrival time cho tien trinh P%d : ", i + 1);
				scanf("%d", &at[i]);
				printf("Nhap burst time cho tien trinh P%d : ", i + 1);
				scanf("%d", &bt[i]);
			}

			printf("\n\nProcess\t|Turnaround Time| Waiting Time\n\n");
			at[9] = 9999;

			while (count != n)  
			{
				smallest = 9; 
				for (i = 0; i < n; i++)
				{
					if (at[i] < at[smallest] && bt[i]>0)
					{
						smallest = i;
					}
				}
				
				time += bt[smallest];  
				wait_Time_Sum += time - at[smallest] - bt[smallest];
				turn_Time_Sum += time - at[smallest];

				printf("P[%d]\t|\t%d\t|\t%d\n", smallest + 1, time - at[smallest], time - at[smallest] - bt[smallest]);

				bt[smallest] = 0;  
				count++;
			}

			printf("\n average waiting time = %f", wait_Time_Sum * 1.0 / n);
			printf("\n average turnaround time = %f\n", turn_Time_Sum * 1.0 / n);*/
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			int n, bt[20], wt[20], tat[20], avwt = 0, avtat = 0, i, j;
			printf("Nhap so tien trinh (maximum 20):");
			scanf("%d", &n);
			printf("Enter Process Burst Time\n");
			for (i = 0; i < n; i++)
			{
				printf("P[%d]:", i + 1);
				scanf("%d", &bt[i]);
			}
			wt[0] = 0;
			for (i = 1; i < n; i++)
			{
				wt[i] = 0;
				for (j = 0; j < i; j++)
					wt[i] += bt[j];
			}
			printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time");
			for (i = 0; i < n; i++)
			{
				tat[i] = bt[i] + wt[i];
				avwt += wt[i];
				avtat += tat[i];
				printf("\nP[%d]\t\t%d\t\t%d\t\t%d", i + 1, bt[i], wt[i], tat[i]);
			}
			avwt /= i;
			avtat /= i;
			printf("\n\nThoi gian cho trung binh:%d", avwt);
			printf("\nThoi gian xoay vong trung binh:%d", avtat);
		}break;
		default: printf("\n WRONG!, PLEASE CHOOSE AGAIN");
		}
	} 
	while (choose != 0);
	system("pause");
}

void menu()
{
	printf("\n*MENU*");
	printf("\n*0.Thoat chuong trinh*");
	printf("\n*1.SJF doc quyen*");
	printf("\n*2.SJF khong doc quyen*");
	printf("\n*3.Round Robin*");
	printf("\n*4.FCFS*");
}

int process(struct time a[], int pro, int t)
{
	int i, minpro{}, mintime = 999;
	for (i = 0; i < pro; i++)
	{
		if (a[i].art <= t && a[i].st == 0)
		{
			if (mintime > a[i].but)
			{
				mintime = a[i].but;
				minpro = i;
			}
		}
	}
	a[minpro].st = 1;
	return minpro;
}
void ganttchart(struct time a[], int gc[], int pro)
{
	int i, x = 0;
	printf("Bieu do Grant\n");
	printf("0");
	for (i = 0; i < pro; i++)
	{
		x = x + a[gc[i]].but;
		printf(" -> [P%d] <- %d", a[gc[i]].p, x);
	}
	printf("\n");
	return;
}
