//defines
#define GY521_ADRESS 0xD0
#define WHO_I_AM 0x75
#define SYS_CLK 8000000UL               // ������� ������
#define BAUDRATE_USART3 9600UL          // �������� UASRT_1

typedef u8 bool;
#define false 0
#define true 1

#define delay counter=0; \
              while(!counter);\

#define MAX_TASKS 32	 // ���� ���-�� �����
#define SIZE 30
#define SIZE_MAS 21
#define MID_VAL 10
// ------------ I2C1

// ------------ GLOBAL
u8 counter=0;
// ------------ systemDev.h
u16 tail_of_tasks=0;              // ���� �� ���������� ��������� ������ � ��������� ����� tail �� �������� �����
u16 head_of_tasks=0;              // ������ �� ���� ������ �� ���������� � ��������� ����� head �� �������� �����
void (*buffer_of_tasks[MAX_TASKS])();    // ��� ����� � ��������
u16 number_of_tasks=0;            // ���-�� ������������� �����
// ------------ data ------------------------
u16 acc_x=0;
u16 acc_y=0;
u16 acc_z=0;

u16 gyro_x=0;
u16 gyro_y=0;
u16 gyro_z=0;

u16 last_acc_x[SIZE];
u16 last_acc_y[SIZE];
u16 last_acc_z[SIZE];

u16 counter_filter;

bool start_filter=false;

u16 last_gyro_x[SIZE];
u16 last_gyro_y[SIZE];
u16 last_gyro_z[SIZE];