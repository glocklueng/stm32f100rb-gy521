void addTask( void (*pf)())     // добавление задачи на выполнение
   {
   buffer_of_tasks[tail_of_tasks]=pf;
   tail_of_tasks++;
   if(tail_of_tasks==MAX_TASKS)
      tail_of_tasks=0;

   number_of_tasks++;
   }

void deleteTask()             // удаление задачи
    {
    buffer_of_tasks[head_of_tasks]=0;
    head_of_tasks++;
    number_of_tasks--;
    if(head_of_tasks==MAX_TASKS)
        head_of_tasks=0;
    }
// обертки для i2c_tx
void i2c1_tx(char adress, char data, char tx_or_rx);
void i2c_tx_0xA_9_0()
    {
    i2c1_tx(0xA,9,0);
    }