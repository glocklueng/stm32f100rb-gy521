u8 read_I2C1(char device_adress, char register_adress)
    {
    char buf;
    I2C1->CR1 |= I2C_CR1_START;
    while(!(I2C1->SR1 & I2C_SR1_SB));
    (void) I2C1->SR1;
    I2C1->DR = device_adress;
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void) I2C1->SR1;  // по даташиту это надо читать...
    (void) I2C1->SR2;
    I2C1->DR = register_adress;
    while (!(I2C1->SR1 & I2C_SR1_TXE));

    I2C1->CR1 |= I2C_CR1_START;
    while(!(I2C1->SR1 & I2C_SR1_SB));
    (void) I2C1->SR1;
    I2C1->DR = (device_adress) | 1;
    while (!(I2C1->SR1 & I2C_SR1_ADDR));    // ожидаем окончания передачи адреса
    (void) I2C1->SR1;                       // по даташиту это надо читать...
    (void) I2C1->SR2;                       //

    while (!(I2C1->SR1 & I2C_SR1_RXNE));    // ожидаем окончания передачи адреса
    buf = I2C1->DR;

    (void) I2C1->SR1;                       // по даташиту это надо читать...
    (void) I2C1->SR2;                       //

    I2C1->CR1 |= I2C_CR1_STOP;
    I2C1->CR1 &= ~I2C_CR1_PE;
    I2C1->CR1 |= I2C_CR1_PE;

    return buf;
    }

void I2C1_tx(char device_adress, char register_adress , char data)
    {
    I2C1->CR1 |= I2C_CR1_START;
    while(!(I2C1->SR1 & I2C_SR1_SB));
    (void) I2C1->SR1;
    I2C1->DR = device_adress;

    while (!(I2C1->SR1 & I2C_SR1_ADDR)); // ожидаем окончания передачи адреса
    (void) I2C1->SR1;  // по даташиту это надо читать...
    (void) I2C1->SR2;  //
    I2C1->DR = register_adress;

    while (!(I2C1->SR1 & I2C_SR1_TXE));
    // (void) I2C1->SR1;                       // по даташиту это надо читать...
    // (void) I2C1->SR2;                       //
    I2C1->DR = data;

    while (!(I2C1->SR1 & I2C_SR1_TXE));

    I2C1->CR1 |= I2C_CR1_STOP;
    I2C2->CR1 &= ~I2C_CR1_PE;
    I2C2->CR1 |= I2C_CR1_PE;
    }