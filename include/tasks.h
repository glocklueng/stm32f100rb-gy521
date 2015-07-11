void green_on(){
    GPIOC->ODR |= GPIO_ODR_ODR9;
    }
void green_off(){
    GPIOC->ODR &= (~GPIO_ODR_ODR9);
    }
void blue_on(){
    GPIOC->ODR |= GPIO_ODR_ODR8;
    }
void blue_off(){
    GPIOC->ODR &= (~GPIO_ODR_ODR8);
    }

void read_data_acc(){
    char data[10];
    int i=0;

    acc_z=0;
    acc_x=0;
    acc_y=0;

    acc_x |= (read_I2C1(0xD0,0x3B)<<8);
    acc_x |= read_I2C1(0xD0,0x3C);

    acc_y |= (read_I2C1(0xD0,0x3D)<<8);
    acc_y |= read_I2C1(0xD0,0x3E);

    acc_z |= (read_I2C1(0xD0,0x3F)<<8);
    acc_z |= read_I2C1(0xD0,0x40);


    data[0] = 'x';
    data[1] = (acc_x>>8);
    data[2] = (0xff & acc_x);
    data[3] = 'y';
    data[4] = (acc_y>>8);
    data[5] = (0xff & acc_y);

    data[6] = 'z';
    data[7] = (acc_z>>8);

    data[8] = (0xff & acc_z);
    data[9] = 0x03;

    send_string_uart_1(data);
    }

void read_data_gyro()
	{
	char data[9];

	gyro_x=0;
    gyro_y=0;
    gyro_z=0;
	data[0] = (gyro_x |= read_I2C1(0xD0,0x43)<<8);
	data[1] = (gyro_x |= read_I2C1(0xD0,0x44));
	data[2] = 0;
	data[3] = (gyro_y |= read_I2C1(0xD0,0x45)<<8);
	data[4] = (gyro_y |= read_I2C1(0xD0,0x46));
	data[5] = 0;
	data[6] = (gyro_z |= read_I2C1(0xD0,0x47)<<8);
	data[7] = (gyro_z |= read_I2C1(0xD0,0x48));
	data[8] = 0x03;

	send_string_uart_1(data);
	}