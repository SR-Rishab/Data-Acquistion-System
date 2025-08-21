#include<functions.h>


void Manual() {
    while(1) {
        TransmitString(motor_select_message);

        char OP_c[] = "000";
        char choice = USART_Receive();
        USART_Flush();
        if(choice == '\0') {
            StartDCMotor();
            TransmitString(dc_speed);
            ReceiveString(OP_c);
            int speed = atoi(OP_c);
            dc_pwm(speed);
        }
        else {
            StartStepperMotor();
            TransmitString(stepper_rot);
            ReceiveString(OP_c);
            int speed = atoi(OP_c);
            RotateStepperMotor(speed);
        }
    }
}

void Auto() {
    TransmitString(sensor_select);
    char choice = ReceiveString();
    switch(choice) {
        case('0'): DHTFunction(); break;
        case('1'): GasFunction(); break;
        case('2'): InfraredFunction(); break;
    }
}

void StartDCMotor()
{
    DDRD = 0x50; // make the DC motor pins as output
    PORTD &= ~(0xFF >> 0); // Clear the data pins
}

void StartStepperMotor {
    DDRD = 0x0F;
    PORTD &= ~(0xFF >> 0); // Clear the data pins
}

void AdjustStepperMotor(int angle) {
    for(i=0;i<angle/7;i++) {
        PORTD=(1<<0)|(1<<3);  //step1 sequence
        _delay_ms(100);
        PORTD&=~(1<<1)|(1<<2)|(1<<0)|(1<<3);
        _delay_ms(100);

        PORTD=(1<<0);   //Step2 sequence
        _delay_ms(100);
        PORTD&=~(1<<1)|(1<<2)|(1<<3);
        _delay_ms(100);

        PORTD=(1<<0)|(1<<1);   //Step3 sequence
        _delay_ms(100);
        PORTD&=~(1<<1)|(1<<2)|(1<<0)|(1<<3);
        _delay_ms(100);

        PORTD=(1<<1);   //Step4 sequence
        _delay_ms(100);
        PORTD&=~(1<<1)|(1<<2)|(1<<0)|(1<<3);
        _delay_ms(100);

        PORTD=(1<<1)|(1<<2);   //Step5 sequence
        _delay_ms(100);
        PORTD&=~(1<<1)|(1<<2)|(1<<0)|(1<<3);
        _delay_ms(100);

        PORTD=(1<<2);   //Step6 sequence
        _delay_ms(100);
        PORTD&=~(1<<1)|(1<<2)|(1<<0)|(1<<3);
        _delay_ms(100);

        PORTD=(1<<2)|(1<<3);   //Step7 sequence
        _delay_ms(100);
        PORTD&=~(1<<1)|(1<<2)|(1<<0)|(1<<3);
        _delay_ms(100);

        PORTD=(1<<3);   //Step8 sequence
        _delay_ms(100);
        PORTD&=~(1<<1)|(1<<2)|(1<<0)|(1<<3);
        _delay_ms(100);
    }
}

void TransmitString(char* string) {
    char *c = string;
    while(*c != '\0') {
        USART_Transmit(*c);
        c++;
    }
    USART_Flush();
}

char* ReceiveString(char* string) {
    char *c = string;
    for(int i = 0; i < 3; i++) {
        c[i] = USART_Receive();
        USART_Flush();
    }
    return string;
}

void DHTFunction() {
    ADMUX &= ~(0xf<<0); // Select ADC[0] as input channel
    ADMUX |= (1<<6);  //
    ADCSRA = (1<<7); //3. Enable ADC : ADCSRA
    ADCSRA |= (7<<0); //4. Configure the prescale value : ADCSRA
    char temp;
    char tab[] = "\t";
    while(1) {
        for(i=0;a[i]!='\0';i++) {
            data_fun(a[i]);
            _delay_ms(100);
        }
        ADCSRA|=(1<<6); //5. Start the conversion : ADCSRA
        while((ADCSRA &(1<<4))==0); //6. wait till conversion complete: ADCSRA
        temp=ADC;//7. Read the result :
        temp=(temp*5*100)/1024;   //Temp
        //temp=(temp*100/1024);   //GAS
        TransmitString(dht_output);
        TransmitString(*temp);
        TransmitString(tab);
    }
}
void GasFunction() {
    ADMUX = (1<<0); // Select ADC[1] as input channel
    ADMUX |= (1<<6);  // Configure reference voltage
    ADCSRA = (1<<7); //3. Enable ADC : ADCSRA
    ADCSRA |= (7<<0); //4. Configure the prescale value : ADCSRA
    char temp;
    char tab[] = "\t";
    while(1) {
        for(i=0;a[i]!='\0';i++) {
                data_fun(a[i]);
                _delay_ms(100);
        }
        ADCSRA|=(1<<6); //5. Start the conversion : ADCSRA
        while((ADCSRA &(1<<4))==0); //6. wait till conversion complete: ADCSRA
        temp=ADC;//7. Read the result :
        temp=(temp*100/1024);   //GAS
        TransmitString(gas_output);
        TransmitString(*temp);
        TransmitString(tab);
    }
}

void InfraredFunction() {
    while(1) {
        byte temp = PINC & (1<<2);
        while(temp)
            TransmitString(infra_detected);
        TransmitString(infra_not);
    }
}
