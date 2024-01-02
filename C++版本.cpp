///*********************************
// * [基于医院分诊系统的排队策略].CPP.B.0.M
// *********************************/
//#define _CRT_SECURE_NO_WARNINGS
//#include <sstream>
//#include <iostream>
//#include <ctime>
//#include <time.h>
//#include <windows.h>
//
//using namespace std;
//typedef int QElemType;
//const int k = 100;
//char stick[k];
//int n;
//
//class Basic
//{
//public:
//    string data;
//    char Rsequence; // 挂号序列
//    char grade;     // 医生等级
//    Basic* next;
//};
//
//class Queue
//{
//public:
//    Basic* front, * rear;     // 定义头尾指针
//    void Iniqueue(Queue& s); // 初始化一个初始链队列（便于每次进行入队列前操作）
//    void Enqueue0(Queue& s, char b);
//    void Enqueue(Queue& s, char b); // 病人挂号
//    void Enqueue(Queue& s, string a, char b);
//    void Enqueue1(Queue& s, string a, char b);
//    void Enqueue2(Queue& s, string a, char b);
//    void DLqueue(Queue& s);    // 出队列
//    string Gethead1(Queue& s); // 返回data
//    char Gethead2(Queue& s);   // 返回Rsequence
//    char Gethead3(Queue& s);   // 返回grade
//    string Gethead4(Queue& s);
//    int Empty(Queue& s);  // 判空
//    void Print(Queue& s); // 输出
//    friend class Custom;
//};
//
//class Custom // 患者类
//{
//public:
//    void ProductStick(int n);
//    void WaitList(Queue& custom1, int n);
//    void WaitList1(Queue& custom2, Queue& Q, Queue& Q3, int n);
//};
//
//class Doctor // 医生类
//{
//public:
//    void PDoctor(Queue& doctoren);
//    void ServeStick(Queue& doctoren, Queue& customque);
//    void ServestickFinish(Queue& doctoren, Queue& customque);
//    char grade1; // 储存输入医生等级 便于入表操作
//};
//
//class Total
//{
//public:
//    void Strategy1(Queue& customque, Queue& doctorque, Custom& customren, Doctor& doctorman, Queue& checkstick);           // 一级就诊医生模式
//    void Strategy2(Queue& customque, Queue& Q, Queue& doctorque, Custom& customren, Doctor& doctorman, Queue& checkstick); // 二级就诊医生模式
//    void DoctorCheck(Queue& checkstick, Queue& customque);
//    void DoctorCheck1(Queue& checkstick, Queue& cQ2);
//    int Counttime();
//};
//void Queue::Iniqueue(Queue& s) // 初始化一个初始链队列（便于每次进行入队列前操作）***
//{
//    Basic* p;
//    p = new Basic;
//    p->next = NULL;
//    s.front = p;
//    s.rear = p;
//}
//
//void Queue::Enqueue(Queue& s, char b) // 将医生信息入队列***
//{
//    Basic* p;
//    string num;
//    string num1;
//    p = new Basic;
//    if (b == 'A' || b == 'S')
//        p->grade = b;
//    else {
//        cout << "输入错误!重新输入(S为专家号  A为普通号)，本次错误不计入输入次数" << endl;
//    }
//    p->next = s.rear->next;
//    s.rear->next = p;
//    s.rear = p;
//}
//void Queue::Enqueue0(Queue& s, char b) { // 病人挂号***
//    Basic* p;
//    string num;
//    string num1;
//    p = new Basic;
//    cout << "请输入病人挂号序号:" << endl;
//    cin >> num;
//    p->data = num;
//    p->Rsequence = b; // 通过productstick函数对Rsequence进行随机赋‘a’‘b’
//    cout << "病人要挂普通号还是专家号:a(表示普通号) b(表示专家号)" << endl;
//    cin >> p->grade;
//    p->next = s.rear->next;
//    s.rear->next = p;
//    s.rear = p;
//}
//
//void Queue::Enqueue(Queue& s, string a, char b) //***
//{
//    Basic* p;
//    string num;
//    string num1;
//    p = new Basic;
//    if (b == 'C') // 判断是第一次还是第二次诊断（c为第二次，a为第一次）9
//    {
//        p->data = a;
//        p->Rsequence = b;
//        p->next = s.rear->next;
//        s.rear->next = p;
//        s.rear = p;
//    }
//    else if (b == 'A') {
//        p->data = a;
//        p->Rsequence = b;
//        p->next = s.front->next;
//        s.front->next = p;
//    }
//}
//
//void Queue::Enqueue1(Queue& s, string a, char b) {
//    Basic* p;
//    string num;
//    string num1;
//    p = new Basic;
//    p->data = a;
//    p->Rsequence = b;
//    p->next = s.rear->next;
//    s.rear->next = p;
//    s.rear = p;
//}
//void Queue::Enqueue2(Queue& s, string a, char b) // 使体检完的病人回到队头
//{
//    Basic* p;
//    string num;
//    string num1;
//    p = new Basic;
//    p->data = a;
//    p->Rsequence = b;
//    p->next = s.front->next;
//    s.front->next = p;
//    s.rear = p;
//}
//string Queue::Gethead1(Queue& s) {
//    if (s.front == s.rear)
//        return NULL;
//    else
//        return s.front->next->data;
//}
//
//string Queue::Gethead4(Queue& s) {
//    if (s.front == s.rear)
//        return NULL;
//    else
//        return s.front->next->data;
//}
//char Queue::Gethead2(Queue& s) //***
//{
//    if (s.front == s.rear)
//        return NULL;
//    else
//        return s.front->next->Rsequence; // 指向挂号序列Rsequence 得到A或者B类型病人
//}
//
//char Queue::Gethead3(Queue& s) {
//    if (s.front == s.rear)
//        return NULL;
//    else
//        return s.front->next->grade;
//}
//
//void Queue::DLqueue(Queue& s) //  删除队列中元素
//{
//    Basic* p;
//    p = s.front->next;
//    if (p->next == NULL) {
//        s.front->next = NULL;
//        s.front = s.rear;
//    }
//    else
//        s.front->next = p->next;
//    delete p;
//}
//
//int Queue::Empty(Queue& s) // 判断表空***
//{
//    if (s.front == s.rear)
//        return 1;
//    else
//        return 0;
//}
//
//void Custom::ProductStick(int n) // 产生一个随机的stick[i]=A或者B***
//{
//    char stickclass;
//    int x;
//    srand((unsigned int)time(NULL)); // time（NULL）是产生一个自1900年1月1日到现在的时间秒数，srand(time(NULL))可以通过运行时间的不同产生不同随机数
//    for (int i = 1; i <= n; i++) {
//        x = int(rand()) % 2;
//        if (x)
//            stickclass = 'A';
//        else
//            stickclass = 'B';
//        stick[i] = stickclass;
//    }
//}
//
//void Custom::WaitList(Queue& custom1, int n) // 一级就诊模式的创建候诊室***
//{
//    custom1.Iniqueue(custom1); // 调用创建链表函数 创建一个
//    for (int i = 1; i <= n; i++)
//        custom1.Enqueue0(custom1, stick[i]); // 调用随机stick[]
//}
//
//void Custom::WaitList1(Queue& Q1, Queue& Q2, Queue& Q3, int n) // 二级就诊模式的创建候诊室***
//{
//    Q1.Iniqueue(Q1); // 初始化Q1就诊室链队列
//    Q2.Iniqueue(Q2); // 初始化Q2候诊室链队列
//    Q3.Iniqueue(Q3);
//    for (int i = 1; i <= n; i++) {
//        if (i <= 3)
//            Q1.Enqueue0(Q1, stick[i]); // 就诊室最多不超过3个人
//        else
//            Q2.Enqueue0(Q2, stick[i]); // 多余的放入候诊室
//    }
//}
//
//void Doctor::PDoctor(Queue& doctoren) // 从键盘接收医生信息***
//{
//    char x;
//    int n;
//    char m;
//    doctoren.Iniqueue(doctoren); // 初始链表
//    cout << "请输入普通医生和专家人数:（共n人,一个科室只允许有一名专家，剩余n-1名为普通医生）" << endl;
//    cin >> n;
//    m = n;
//    for (int i = 1; i <= n; i++) {
//        cout << "请输入 A 表示普通医生, S 表示专家" << endl;
//        cin >> x;
//        grade1 = x;
//        if (grade1 != 'S' && grade1 != 'A') {
//            n++;
//        }                                   // 若输错再给机会输入
//        doctoren.Enqueue(doctoren, grade1); // 调用入链表操作
//    }
//}
//
//void Doctor::ServeStick(Queue& doctoren, Queue& customque) // 进行诊断***
//{
//    Queue storage;
//    char ch;
//    if (doctoren.Empty(doctoren))
//        cout << "没有空闲医生,请等待!" << endl;
//    else {
//        string x2 = customque.Gethead1(customque);
//        ch = doctoren.Gethead3(doctoren);
//        doctoren.DLqueue(doctoren);
//        storage.Iniqueue(storage);
//        storage.Enqueue(storage, ch);
//        cout << x2 << "号"
//            << "正在诊断之中:请耐心等待!:" << endl;
//    }
//}
//
//void Doctor::ServestickFinish(Queue& doctoren, Queue& customque) // 诊断完成***
//{
//    string x;
//    x = customque.Gethead1(customque);
//    if (customque.Gethead2(customque) == 'A' || customque.Gethead2(customque) == 'C') {
//        cout << x << "号"
//            << "病人诊断完成"
//            << "，该病人为A类型病" << endl;
//    }
//    if (customque.Gethead2(customque) == 'B') {
//        cout << x << "号"
//            << "病人诊断完成"
//            << "，该病人为B类型病（请去体检室体检完毕后返回）" << endl;
//        n = 1;
//    }
//    if (customque.Gethead2(customque) == 'D') {
//        cout << x << "号"
//            << "病人诊断完成" << endl;
//    }
//    customque.DLqueue(customque);
//    doctoren.Enqueue(doctoren, grade1);
//}
//
//int Total::Counttime() // 设置就诊时间 ***
//{
//    int x;
//    time_t now_time;
//    now_time = time(NULL);
//    struct tm now = *localtime(&now_time);
//    x = now.tm_sec;
//    return x;
//}
//
//void Total::Strategy1(Queue& customque, Queue& doctorque, Custom& customren, Doctor& doctorman, Queue& checkstick) // 一级就诊医生模式***
//{
//    string x;
//    static int count1 = 0;
//    int time1, time2;
//    if (!customque.Empty(customque)) {
//        x = customque.Gethead1(customque);
//        time1 = 0;
//        if (customque.Gethead2(customque) == 'A' || customque.Gethead2(customque) == 'C') // 不需要体检的A型病人(productstick 函数对stick进行随机赋a、b，赋a则不需要体检、b则需要体检)
//        {
//            doctorman.ServeStick(doctorque, customque);
//            doctorman.ServestickFinish(doctorque, customque);
//            time2 = Counttime();
//            cout << "诊断花费" << time2 - time1 << "分钟   " << endl;
//            ;
//        }
//        else // 需要体检的B类型病人
//        {
//            doctorman.ServeStick(doctorque, customque);
//            checkstick.Enqueue(checkstick, x, 'C');
//            doctorman.ServestickFinish(doctorque, customque);
//            time2 = Counttime();
//            cout << "诊断花费" << time2 - time1 << "分钟" << endl;
//        }
//    }
//    else {
//        cout << "诊室区没有病人等待!" << endl;
//    }
//}
//
//int stringToInt(const string& s) // string型转int型函数
//{
//    stringstream ss;
//    int result;
//    ss << s;
//    ss >> result;
//    return result;
//}
//
//void Total::Strategy2(Queue& Q1, Queue& Q2, Queue& doctorque, Custom& customren1, Doctor& doctorman, Queue& checkstick) // 二级就诊医生模式
//{
//    string x, num;
//    char ge;
//    static int count2 = 0;
//    int time1, time2;
//    if (!Q1.Empty(Q1)) {
//        x = Q1.Gethead1(Q1);
//        time1 = 0;
//        if (Q1.Gethead2(Q1) == 'A' || Q1.Gethead2(Q1) == 'C') // 不需要体检的A型病人
//        {
//            doctorman.ServeStick(doctorque, Q1);
//            doctorman.ServestickFinish(doctorque, Q1);
//            time2 = Counttime();
//            cout << "诊断花费" << time2 - time1 << "分钟  " << endl;
//        }
//        else // 需要体检的B型病人
//        {
//            doctorman.ServeStick(doctorque, Q1);
//            checkstick.Enqueue(checkstick, x, 'C');
//            doctorman.ServestickFinish(doctorque, Q1);
//            time2 = Counttime();
//            cout << "诊断花费" << time2 - time1 << "分钟" << endl;
//        }
//    }
//    else if (!Q2.Empty(Q2)) {
//        cout << "就诊室(Q1)没有病人等待! 请候诊室(Q2)进入就诊:" << endl;
//        int j;
//        num = Q2.Gethead4(Q2);
//        ge = Q2.Gethead2(Q2);
//        j = stringToInt(num);
//        Q1.Enqueue1(Q1, num, ge);
//        Q2.DLqueue(Q2);
//    }
//    else {
//        cout << "诊室区(Q1)和诊侯区(Q2)都没有病人等待!" << endl;
//    }
//}
//
//void Total::DoctorCheck(Queue& checkstick, Queue& customque) // 一级分诊模式体检模式***
//{
//    string x;
//    if (!checkstick.Empty(checkstick) && n == 1) {
//        x = checkstick.Gethead1(checkstick);
//         //检查病人是否已经在体检队列中
//        if (customque.Gethead2(customque) != 'D') {
//            cout << x << "号"
//                << "检查之中" << endl;
//            customque.Enqueue2(customque, x, 'D'); // 将Rsequence变为D 使体检完后继续诊断的输出结果和之前的第一次不一样
//            Sleep(1000);
//            cout << x << "号"
//                << "检查完成"
//                << "，请返回就诊室继续就诊!" << endl;
//            Sleep(1000);
//        }
//        checkstick.DLqueue(checkstick); // Remove patient from the checkstick queue
//        n = 0;
//    }
//    else
//        cout << "没有病人要进行检查:" << endl;
//}
//
//void Total::DoctorCheck1(Queue& checkstick, Queue& Q2) // 二级分诊模式的体检模式***
//{
//    string x;
//    if (!checkstick.Empty(checkstick)) {
//        x = checkstick.Gethead1(checkstick);
//         //检查病人是否已经在体检队列中
//        if (Q2.Gethead2(Q2) != 'D') {
//            cout << x << "号"
//                << "检查之中" << endl;
//            Q2.Enqueue2(Q2, x, 'D');
//            Sleep(1000);
//            cout << x << "号"
//                << "检查完成"
//                << "，请返回就诊室继续就诊!" << endl;
//            Sleep(1000);
//        }
//        checkstick.DLqueue(checkstick); // Remove patient from the checkstick queue
//    }
//    else
//        cout << "没有病人要进行检查:" << endl;
//}
//int main() // 主函数
//{
//    cout << "\t\t**************************" << endl;
//    cout << "\t\t**\t\t\t**" << endl;
//    cout << "\t\t**   医院分诊系统排队   **" << endl;
//    cout << "\t\t**\t\t\t**" << endl;
//    cout << "\t\t**************************\n"
//        << endl;
//    cout << "\t\t **请输入回车以进入系统**";
//    Queue Q1, Q2, Q3, customque, doctorque, checkstick, checkstick1;
//    Custom customren, customren1;
//    Doctor doctorman;
//    Total k;
//    int n;
//    int m = 1;
//    checkstick.Iniqueue(checkstick);
//    checkstick1.Iniqueue(checkstick1);
//    getchar();
//    system("cls");
//    while (m != 8) {
//        cout << " \t ******|   以下为功能列表，请输入对应的数字以使用功能     " << endl;
//        cout << " \t ******|1. 医生信息创建            " << endl;
//        cout << " \t ******|2. 一级分诊模式的病人挂号  " << endl;
//        cout << " \t ******|3. 二级分诊模式的病人挂号  " << endl;
//        cout << " \t ******|4. 一级分诊模式模拟，每次诊治一名病人        " << endl;
//        cout << " \t ******|5. 二级分诊模式模拟，每次诊治一名病人        " << endl;
//        cout << " \t ******|6. 一级分诊模式 检查系统" << endl;
//        cout << " \t ******|7. 二级分诊模式 检查系统" << endl;
//        cout << " \t ******|8. 退出系统 " << endl;
//        cin >> m;
//        switch (m) {
//        case 1:
//            cout << "医生信息生成:" << endl;
//            doctorman.PDoctor(doctorque);
//            Sleep(1000);
//            break;
//        case 2:
//            cout << "请输入要产生的人数:" << endl;
//            cin >> n;
//            customren.ProductStick(n);
//            cout << "病人入队挂号" << endl;
//            customren.WaitList(customque, n);
//            Sleep(1000);
//            break;
//        case 3:
//            cout << "请输入要产生的人数:" << endl;
//            cin >> n;
//            customren.ProductStick(n);
//            cout << "病人入队挂号" << endl;
//            customren1.WaitList1(Q1, Q2, Q3, n);
//            Sleep(1000);
//
//            break;
//        case 4:
//            k.Strategy1(customque, doctorque, customren, doctorman, checkstick);
//            Sleep(1000);
//            break;
//        case 5:
//            k.Strategy2(Q1, Q2, doctorque, customren1, doctorman, checkstick1);
//            Sleep(1000);
//
//            break;
//        case 6:
//            k.DoctorCheck(checkstick, customque);
//            Sleep(1000);
//            break;
//        case 7:
//            k.DoctorCheck1(checkstick1, Q2);
//            Sleep(1000);
//            break;
//        case 8:
//            cout << "谢谢使用！" << endl;
//        }
//    }
//}