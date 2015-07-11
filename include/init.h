void initRCC(){
    // в stm32f100 после старта в регистрах RCC какой-то мусор, не соотв. даташиту
    // поэтому скидывать всё в 0 и настраивать вручную
    RCC->CR = 0x00;
    RCC->CFGR = 0x00;
    RCC->CR |= RCC_CR_HSION;

    RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;     // тактирование порт А
    RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;     // тактирование порт B
    RCC->APB2ENR|=RCC_APB2ENR_IOPCEN;     // тактирование порт С
    RCC->APB2ENR|=RCC_APB2ENR_AFIOEN;     // вкл альтернативных функций
    RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;     // тактирование таймера_2
    RCC->APB1ENR|=RCC_APB1ENR_USART3EN;   // USART3 EN
    RCC->APB1ENR|=RCC_APB1ENR_I2C1EN;     // тактирование I2C1
}
void initGPIO(){
    // ------------------------  PORT_C  --------------------------------
    GPIOC->CRH = 0x00;
    GPIOC->CRH |= GPIO_CRH_MODE8_1 | GPIO_CRH_MODE9_1;
    GPIOC->CRH &=~ (GPIO_CRH_CNF8_0 | GPIO_CRH_CNF9_0);

    // UART3
    // PORT_C10 TX
    // PORT_C11 RX
    GPIOC->CRH &= ~(GPIO_CRH_MODE10_0 | GPIO_CRH_CNF10_0 | GPIO_CRH_CNF11_0);
    GPIOC->CRH |= GPIO_CRH_MODE10_1 | GPIO_CRH_CNF10_1 | GPIO_CRH_CNF11_1;

    AFIO->MAPR |= AFIO_MAPR_USART3_REMAP_0; // set uart3 remap function
    // ------------------------  PORT_B  --------------------------------
    // I2C1
    // PORT_B6 SCL
    // PORT_B7 SDA
    GPIOB->CRL |= GPIO_CRL_CNF6_0 | GPIO_CRL_CNF6_1 | GPIO_CRL_CNF7_1 | GPIO_CRL_CNF7_0;
    GPIOB->CRL |= GPIO_CRL_MODE6_0 | GPIO_CRL_MODE7_0;
    // GPIOB->CRL &= ~(GPIO_CRL_MODE6_1 | GPIO_CRL_MODE7_1);
    // NVIC_EnableIRQ (USART1_IRQn);         // разрешаем прерывание по USART1
    }

// ------------ USART1
void initUSART3(){
    USART3->CR1 |= USART_CR1_TE;
    USART3->BRR = (SYS_CLK + BAUDRATE_USART3/16)/BAUDRATE_USART3;
    USART3->CR1 |= USART_CR1_UE;
}

void initI2C1(){
    I2C1->CR1 = I2C_CR1_SWRST;  // по-идее это очистка регистра
    I2C1->CR1 = 0;              //

    I2C1->CR2 |= 8;
    I2C1->CCR |= 20;
    I2C1->TRISE = 12;  // задержка импульса

    I2C1->CR1 |= I2C_CR1_PE;  // enable i2c1

    // NVIC_EnableIRQ(I2C1_EV_IRQn); // interrupt I2C2 on
    while (!(I2C1->CR1 & I2C_CR1_PE)){}
    }

void initTIM2(){
    TIM2->CR1 |= TIM_CR1_CEN | TIM_CR1_ARPE;
    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_CEN;
    TIM2->PSC = 8000;
    TIM2->ARR = 1000;

    NVIC_EnableIRQ(TIM2_IRQn);
}
void initDMA(){
    RCC->AHBENR|=RCC_AHBENR_DMA1EN;
    DMA1_Channel4->CPAR = (uint32_t)&(USART1->DR);
    //DMA1_Channel4->CMAR = (uint32_t)(buffer[0]);
    DMA1_Channel4->CNDTR = 200;
    DMA1_Channel4->CCR |= DMA_CCR4_PL_1  | DMA_CCR4_CIRC | DMA_CCR4_DIR;
    DMA1_Channel4->CCR |= DMA_CCR4_MINC;
    DMA1_Channel4->CCR |= DMA_CCR4_EN;
    }