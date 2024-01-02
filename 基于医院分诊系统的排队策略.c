#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>
#include <windows.h>

#define k 100
char sick[k]; //病人生病类型

typedef struct Doctor {
	char Ddata[50];
	char DRsequence;
	char Dgrade;     // 医生等级
	struct Doctor* next;
} Doctor, * DoctorList;

typedef struct DQueue { //医生队列
	DoctorList front, rear;
	int size;
}DQueue;

typedef struct Patient {
	char Ptype; //病人生病类型
	char Pdata[50]; //病人挂号序列
	char Pgrade; //病人挂号的医生等级
	char Finalstatus; //诊断完的状态
	struct Patient* next;
} Patient, * PatientList;

typedef struct PQueue { //患者队列
	PatientList front, rear;
	int size;
}PQueue;


void Iniqueue(PQueue* patientque) { //初始化病人队列
	patientque->front = patientque->rear = NULL;
}

void Enqueue0(PQueue* patientque, char Ptype, int i) { //病人队列进队
	PatientList p = (PatientList)malloc(sizeof(Patient));
	char num[50];
	printf("\t   输入第%d位病人的挂号序号:", i);
	scanf("%s", num);
	strcpy(p->Pdata, num);
	p->Finalstatus = p->Ptype = Ptype;
	printf("   要挂普通号还是专家号 N(普通号) S(专家号):");
	scanf(" %c", &p->Pgrade);
	p->next = NULL; //将元素入队、队尾指针指向新节点
	if (patientque->front == NULL) {
		patientque->front = p;
	}
	else
		patientque->rear->next = p;
	patientque->rear = p;
}

void Enqueue1(PQueue* Q1, PQueue* Q2) {

	PatientList p = (PatientList)malloc(sizeof(Patient));
	p->Finalstatus = Q2->front->Finalstatus;
	strcpy(p->Pdata, Q2->front->Pdata);
	p->Pgrade = Q2->front->Pgrade;
	p->Ptype = Q2->front->Ptype;
	if (Q1->front == NULL) {
		Q1->front = p;
	}
	else
		Q1->rear->next = p;
	Q1->rear = p;
}

char GetPatientHead_type(PQueue* patientque) {
	if (patientque->front == NULL)
		return NULL;
	else
		return patientque->front->Ptype;
}

char* GetPatientHead_data(PQueue* patientque) {
	if (patientque->front == NULL)
		return NULL;
	else
		return patientque->front->Pdata;
}

char GetPatientHead_doctype(PQueue* patientque) {
	if (patientque->front == NULL)
		return NULL;
	else
		return patientque->front->Pgrade;
}

void Enqueue2(PQueue* checksick, PQueue* patientque, char a[], char type) { //体检完病人回到队头
	PatientList p = (PatientList)malloc(sizeof(Patient));
	strcpy(p->Pdata, a);
	p->Ptype = GetPatientHead_type(checksick);
	p->Pgrade = GetPatientHead_doctype(checksick);
	p->Finalstatus = type;
	p->next = patientque->front;
	patientque->front = p;
}

void DLqueue(PQueue* patientque) {
	if (patientque->front == NULL)
		return 0;
	PatientList p = patientque->front;
	patientque->front = p->next;
	free(p);
}

int PEmpty(PQueue* patientque) {
	if (patientque->front == NULL)
		return 1;
	else
		return 0;
}

int DEmpty(DQueue* patientque) { //判断医生队列是否为空
	if (patientque->front == patientque->rear)
		return 1;
	else
		return 0;
}

int DType_Empty(DoctorList doctor, char doctype) { //判断目标类型的医生队列是否为空
	if (doctor == NULL)
		return NULL;
	if (doctor->Dgrade == doctype)
		return 1;
	else
		DType_Empty(doctor->next, doctype);
}

void ProductSick(PQueue* patientque) { //产生病人类型
	char sickclass;
	int x;
	for (int i = 1; i <= (patientque->size); i++) {
		x = rand() % 2;
		if (x)
			sickclass = 'A';
		else
			sickclass = 'B';
		sick[i] = sickclass;
	}
}

void WaitList(PQueue* patientque) { //策略一将病人类型和挂号对应
	Iniqueue(patientque);
	for (int i = 1; i <= (patientque->size); i++)
		Enqueue0(patientque, sick[i], i);
}

void WaitList1(PQueue* Q1, PQueue* Q2, PQueue* patientque) { //策略二将病人类型和挂号对应
	for (int i = 1; i <= (patientque->size); i++) {
		if (i <= 3)
			Enqueue0(Q1, sick[i], i);
		else
			Enqueue0(Q2, sick[i], i);
	}
}

void Inidocqueue(DQueue* doctorque) { //初始化医生队列
	doctorque->front = doctorque->rear = NULL;
}

void Enqueue(DQueue* doctorque) { //医生队列进队
	char Doctype;
	int count = 0;
	int n = doctorque->size;
	for (int i = 1; i <= n; i++) {
		DoctorList p = (DoctorList)malloc(sizeof(Doctor));
		if (p == NULL) {
			printf("内存空间分配失败");
			exit(1);
		}
		printf("请输入 N 表示普通医生，S 表示专家:");
		scanf(" %c", &Doctype);
		if (Doctype != 'S' && Doctype != 'N') {
			printf("非法输入，请输入正确的选择：");
			n++;
		}
		if (Doctype == 'S') {
			count++;
			if (count > 1) {
				n++;
				printf("只允许一名专家，请重新输入：\n");
			}
			else {
				p->Dgrade = Doctype; //将元素压入队列、将队尾指针指向新节点
				p->next = NULL;
				if (doctorque->front == NULL) {
					doctorque->front = p;
				}
				else
					doctorque->rear->next = p;
				doctorque->rear = p;
			}
		}
		else if (Doctype == 'N') {
			p->Dgrade = Doctype; //将元素压入队列、将队尾指针指向新节点
			p->next = NULL;
			if (doctorque->front == NULL) {
				doctorque->front = p;
			}
			else
				doctorque->rear->next = p;
			doctorque->rear = p;
		}
	}
	printf("\n");
}

void PDoctor(DQueue* doctorque) {
	Inidocqueue(doctorque);
	Enqueue(doctorque);
}

int ServeSick(DoctorList doctor, PQueue* patientque, char docgrade) {
	if (!DType_Empty(doctor, docgrade)) {
		printf("\t******************************\n");
		printf("没有目标类型医生,请重新挂号选择医生或重新初始化医生!\n\n");
		return 0;
	}
	else {
		char x2[50];
		strcpy(x2, GetPatientHead_data(patientque));
		printf("%s号正在诊断之中:请耐心等待!:\n", x2);
	}

}

void EnqueuCheck(PQueue* checksick, PQueue* patientque) {
	PatientList p = (PatientList)malloc(sizeof(Patient));
	p->Ptype = GetPatientHead_type(patientque);
	strcpy(p->Pdata, GetPatientHead_data(patientque));
	p->Pgrade = GetPatientHead_doctype(patientque);
	p->next = NULL;//将元素压入队列、将队尾指针指向新节点
	if (checksick->front == NULL) {
		checksick->front = p;
	}
	else
		checksick->rear->next = p;
	checksick->rear = p;
}

void ServesickFinish(PQueue* checksick, PQueue* patientque) {
	char x[50];
	strcpy(x, GetPatientHead_data(patientque));
	if (patientque->front->Finalstatus == 'A') {
		printf("%s号病人诊断完成，该病人为A类型病\n", x);
		DLqueue(patientque);
	}
	else if (patientque->front->Finalstatus == 'B') {
		printf("%s号病人诊断完成，该病人为B类型病，请去体检室体检完毕后返回\n", x);
		EnqueuCheck(checksick, patientque);
		DLqueue(patientque);
	}
	else if (patientque->front->Finalstatus == 'D') {
		printf("%s号病人诊断完成\n", x);
		DLqueue(patientque);
	}
}

int Counttime() { //计算等待时间
	int x = 0;
	time_t now_time;
	now_time = time(NULL);
	struct tm* now = localtime(&now_time);
	x = now->tm_sec;
	return x;
}

void Strategy1(PQueue* patientque, DQueue* doctorque, PQueue* checksick, int* menuchoice) {
	char x[50];
	int begintime, endtime;
	PatientList Patient = patientque->front;
	DoctorList Doctor = doctorque->front;
	if (!PEmpty(patientque)) {
		strcpy(x, GetPatientHead_data(patientque));
		begintime = 0;
		if (GetPatientHead_type(patientque) == 'A') {
			if (!ServeSick(Doctor, patientque, Patient->Pgrade)) {
				return *menuchoice = 1;
			}
			ServesickFinish(checksick, patientque);
			endtime = Counttime();
			printf("诊断花费%d分钟\n", endtime - begintime);
		}
		else {
			if (!ServeSick(Doctor, patientque, Patient->Pgrade)) {
				return *menuchoice = 1;
			}
			ServesickFinish(checksick, patientque);
			endtime = Counttime();
			printf("诊断花费%d分钟\n", endtime - begintime);
		}
	}
	else {
		printf("诊室区没有病人等待!\n");
	}
}

void Strategy2(PQueue* Q1, PQueue* Q2, DQueue* doctorque, PQueue* checksick, int* menuchoice) {
	char x[50];
	int begintime, endtime;
	PatientList Patient = Q1->front;
	DoctorList Doctor = doctorque->front;
	if (!PEmpty(Q1)) {
		strcpy(x, GetPatientHead_data(Q1));
		begintime = 0;
		if (GetPatientHead_type(Q1) == 'A') {
			if (!ServeSick(Doctor, Q1, Patient->Pgrade)) {
				return *menuchoice = 1;
			}
			ServesickFinish(checksick, Q1);
			endtime = Counttime();
			printf("诊断花费%d分钟\n", endtime - begintime);
		}
		else {
			if (!ServeSick(Doctor, Q1, Patient->Pgrade)) {
				return *menuchoice = 1;
			}
			ServesickFinish(checksick, Q1);
			endtime = Counttime();
			printf("诊断花费%d分钟\n", endtime - begintime);
		}
	}
	else if (!PEmpty(Q2)) {
		printf("就诊室(Q1)没有病人等待! 请候诊室(Q2)进入就诊:\n");
		for (int i = 1; i <= 3; i++) {
			if (Q2->front != NULL) {
				Enqueue1(Q1, Q2);
				DLqueue(Q2);
			}
			else break;
		}
		Sleep(300);
		printf("候诊室(Q2)队列已进入就诊室(Q1)，请在系统中继续选择步骤\n");
	}
	else if (!PEmpty(Q2) && !PEmpty(Q1)) {
		printf("就诊室(Q1)和诊侯厅(Q2)都没有病人等待!\n");
	}
}

void DoctorCheck(PQueue* checksick, PQueue* patientque) {
	char x[50];
	if (!PEmpty(checksick)) {
		strcpy(x, GetPatientHead_data(checksick));
		if (GetPatientHead_type(checksick) != 'D') {
			printf("%s号正在检查中\n", x);
			Enqueue2(checksick, patientque, x, 'D');
			Sleep(300);
			printf("%s号检查完成，请返回就诊室继续就诊!\n", x);
			Sleep(300);
		}
		DLqueue(checksick);
	}
	else {
		printf("没有病人要进行检查:\n");
	}
}

int main() {
	srand((unsigned int)time(NULL));
	PQueue Q1, Q2, patientque, checksick, checksick1;
	DQueue doctorque;
	int menuchoice = 1;
	Iniqueue(&Q1); Iniqueue(&checksick1);
	Iniqueue(&Q2); Iniqueue(&checksick);
	Iniqueue(&patientque); Inidocqueue(&doctorque);

	while (menuchoice != 8) {
		printf("=================================================\n");
		printf("=           欢迎来到医院分诊排队系统            =\n");
		printf("=-----------------------------------------------=\n");
		printf("=       请根据一定次序实现下列的分诊功能        =\n");
		printf("=         1. 科室医生序列的信息创建             =\n");
		printf("=         2. 一级分诊模式的病人挂号             =\n");
		printf("=         3. 二级分诊模式的病人挂号             =\n");
		printf("=         4. 一级分诊模拟，每次诊治一名病人     =\n");
		printf("=         5. 二级分诊模拟，每次诊治一名病人     =\n");
		printf("=         6. 一级分诊体检系统                   =\n");
		printf("=         7. 二级分诊体检系统                   =\n");
		printf("=         8. 挂号退出医院分诊排队系统           =\n");
		printf("=-----------------------------------------------=\n");
		printf("=           祝您：早日康复！生活愉快！          =\n");
		printf("=================================================\n");
		printf("        请按照您的需求做出正确的选择：");
		scanf("%d", &menuchoice);
		switch (menuchoice) {
		case 1:
			printf("\n\t*******************************");
			printf("\n\t\t医生信息生成:\n");
			printf("请输入普通医生和专家总人数:（只能有一名专家，剩余为普通医生）\n");
			scanf("%d", &(doctorque.size));
			PDoctor(&doctorque);
			Sleep(200);
			break;
		case 2:
			printf("\n\t*******************************");
			printf("\n\t    一级分诊模式的病人挂号\n");
			printf("\t*******************************");
			printf("\n\t   请输入模拟产生的病人数:");
			scanf("%d", &(patientque.size));
			ProductSick(&patientque);
			printf("\n\t   |      病人挂号入队     |\n");
			printf("\t   *************************     \n");
			WaitList(&patientque);
			Sleep(300);
			break;
		case 3:
			printf("\n\t*******************************");
			printf("\n\t    二级分诊模式的病人挂号\n");
			printf("\t*******************************");
			printf("\n\t   请输入模拟产生的病人数:");
			scanf("%d", &(patientque.size));
			ProductSick(&patientque);
			printf("\n\t   |      病人挂号入队     |\n");
			printf("\t   *************************     \n");
			WaitList1(&Q1, &Q2, &patientque);
			Sleep(300);
			break;
		case 4:
			Strategy1(&patientque, &doctorque, &checksick, &menuchoice);
			Sleep(300);
			break;
		case 5:
			Strategy2(&Q1, &Q2, &doctorque, &checksick1, &menuchoice);
			Sleep(300);
			break;
		case 6:
			DoctorCheck(&checksick, &patientque);
			Sleep(300);
			break;
		case 7:
			DoctorCheck(&checksick1, &Q1);
			Sleep(300);
			break;
		case 8:
			printf("谢谢使用！\n");
			break;
		}
	}
}


