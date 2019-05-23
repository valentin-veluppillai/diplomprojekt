# `[COMPLETED]`
# Module: uart
a simple uart module providing a function called `stprint()`, which can use format input (like `printf()`) to print to a uart bus sepciefied in its header. This requires freertos and was built using CubeIDE.
## changes
### CubeMX
* activate your uart (make sure to set the ST_USART and ST_USART_LL in uart.h accordingly)
* activate freertos
* activate the usart interrupt in the nested vector interrupt contoller (nvic)
* generate code
### code
* drop the files/dirs in this directory in your toplevel project folder.
* set ST_USART and ST_USART_LL in uart.h accordingly
* delete the line declaring huartx in main.c/main.h (x is an number, default is 3)
* include uart.h in your main.h
* add this to your variable declaration:
```
#ifdef UART_H_
extern SemaphoreHandle_t mutexSerialCom;
extern SemaphoreHandle_t mutexUART3;
extern QueueHandle_t queueRxST, queueTxST;
extern UART_HandleTypeDef huart3;
#endif
```

* add the following code to USARTx_IRQ_Handler() in stm32xxxx_it.c:
```
if(LL_USART_IsActiveFlag_RXNE(ST_USART_LL) && LL_USART_IsEnabledIT_RXNE(ST_USART_LL))
        UART_CharReception_Callback();
HAL_UART_IRQHandler(&huart3);
```

* add the following code to your startup task
```
uartInit();
stprint("\r\033cBOOTED\n------\n");
```
