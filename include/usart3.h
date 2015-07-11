void sendUART3(u8 data){
	while( !(USART3->SR & USART_SR_TXE));
	USART3->DR = data;
}

void send_string_uart_1(u8 *data){
	while( (*data)++ != 0x03){
		while( !(USART3->SR & USART_SR_TXE));
		USART3->DR = *data;
	}
}