// Base addresses for UART4 and GPIOA
#define UART4_BASE 0x40004C00
#define GPIOA_BASE 0x40020000
#define GPIOB_BASE 0x40020400
#define GPIOC_BASE 0x40020800
#define GPIOG_BASE 0x40021800
#define SPI1_BASE  0x40013000
#define RCC_BASE   0x40023800
#define ADC1_BASE  0x40012000
#define DAC_BASE   0x40007400
#define TIM6_BASE  0x40001000
#define NVIC_ISER_BASE 0xE000E100
#define NVIC_ICER_BASE 0xE000E180
#define NVIC_ISPR_BASE 0xE000E200
#define NVIC_ICPR_BASE 0xE000E280
#define NVIC_IABR_BASE 0xE000E300
#define NVIC_IPR_BASE  0xE000E400
#define NVIC_STIR  0xE000EF00
//NVIC Registers
#define NVIC_ISER0  *((volatile unsigned int*)(NVIC_ISER_BASE + 0x00))
#define NVIC_ISER1  *((volatile unsigned int*)(NVIC_ISER_BASE + 0x04))
#define NVIC_ISER2  *((volatile unsigned int*)(NVIC_ISER_BASE + 0x08))
#define NVIC_ISER3  *((volatile unsigned int*)(NVIC_ISER_BASE + 0x0C))
#define NVIC_ICER0  *((volatile unsigned int*)(NVIC_ICER_BASE + 0x00))
#define NVIC_ICER1  *((volatile unsigned int*)(NVIC_ICER_BASE + 0x04))
#define NVIC_ICER2  *((volatile unsigned int*)(NVIC_ICER_BASE + 0x08))
#define NVIC_ICER3  *((volatile unsigned int*)(NVIC_ICER_BASE + 0x0C))
#define NVIC_IPR(x) *((volatile unsigned int*)(NVIC_IPR_BASE + x/4))

//ADC1 Registers
#define ADC1_SR    *((volatile unsigned int *)(ADC1_BASE + 0x00))
#define ADC1_CR1   *((volatile unsigned int *)(ADC1_BASE + 0x04))
#define ADC1_CR2   *((volatile unsigned int *)(ADC1_BASE + 0x08))
#define ADC1_DR    *((volatile unsigned int *)(ADC1_BASE + 0x4C))
#define ADC1_SMPR2 *((volatile unsigned int *)(ADC1_BASE + 0x10))

//DAC1
#define DAC_CR     		*((volatile unsigned int *)(DAC_BASE + 0x00))
#define DAC_SWTRIGR     *((volatile unsigned int *)(DAC_BASE + 0x04))
#define DAC_DHR12R1     *((volatile unsigned int *)(DAC_BASE + 0x08))
#define DAC_DHR12L1     *((volatile unsigned int *)(DAC_BASE + 0x0C))
#define DAC_DHR8R1    	*((volatile unsigned int *)(DAC_BASE + 0x10))
#define DAC_DHR12R2     *((volatile unsigned int *)(DAC_BASE + 0x14))
#define DAC_DHR12L2     *((volatile unsigned int *)(DAC_BASE + 0x18))
#define DAC_DHR8R2     	*((volatile unsigned int *)(DAC_BASE + 0x1C))
#define DAC_DHR12RD     *((volatile unsigned int *)(DAC_BASE + 0x20))
#define DAC_DHR12LD     *((volatile unsigned int *)(DAC_BASE + 0x24))
#define DAC_DOR1    	*((volatile unsigned int *)(DAC_BASE + 0x2C))
#define DAC_DOR2     	*((volatile unsigned int *)(DAC_BASE + 0x30))
#define DAC_SR    		*((volatile unsigned int *)(DAC_BASE + 0x34))

// UART4 Register Offsets
#define USART_SR     *((volatile unsigned int *)(UART4_BASE + 0x00)) // Status Register
#define USART_DR     *((volatile unsigned int *)(UART4_BASE + 0x04)) // Data Register
#define USART_BRR    *((volatile unsigned int *)(UART4_BASE + 0x08)) // Baud Rate Register
#define USART_CR1    *((volatile unsigned int *)(UART4_BASE + 0x0C)) // Control Register 1

// GPIOA Register Offsets
#define GPIOA_MODER  *((volatile unsigned int *)(GPIOA_BASE + 0x00)) // Mode Register
#define GPIOB_MODER  *((volatile unsigned int *)(GPIOB_BASE + 0x00)) // Mode Register
#define GPIOC_MODER  *((volatile unsigned int *)(GPIOC_BASE + 0x00)) // Mode Register
#define GPIOG_MODER  *((volatile unsigned int *)(GPIOG_BASE + 0x00)) // Mode Register
#define GPIOG_ODR    *((volatile unsigned int *)(GPIOG_BASE + 0x14)) // Mode Register
#define GPIOB_IDR    *((volatile unsigned int *)(GPIOB_BASE + 0x10)) // Mode Register
#define GPIOA_IDR    *((volatile unsigned int *)(GPIOA_BASE + 0x10)) // Mode Register
#define GPIOA_AFRL   *((volatile unsigned int *)(GPIOA_BASE + 0x20)) // Alternate Function Low Register
#define GPIOC_AFRL   *((volatile unsigned int *)(GPIOC_BASE + 0x20)) // Alternate Function Low Register

// RCC Register Offsets
#define RCC_AHB1ENR  *((volatile unsigned int *)(RCC_BASE + 0x30)) // AHB1 Peripheral Clock Enable Register
#define RCC_APB1ENR  *((volatile unsigned int *)(RCC_BASE + 0x40)) // APB1 Peripheral Clock Enable Register
#define RCC_APB2ENR  *((volatile unsigned int *)(RCC_BASE + 0x44)) // APB1 Peripheral Clock Enable Register

// SPI Register Offsets
#define SPI_CR1      *((volatile unsigned int *)(SPI1_BASE + 0x0))
#define SPI_CR2      *((volatile unsigned int *)(SPI1_BASE + 0x4))
#define SPI_SR       *((volatile unsigned int *)(SPI1_BASE + 0x8))
#define SPI_DR       *((volatile unsigned int *)(SPI1_BASE + 0x0C))
#define SPI_CRCPR    *((volatile unsigned int *)(SPI1_BASE + 0x10))
#define SPI_RXCRCR   *((volatile unsigned int *)(SPI1_BASE + 0x14))
#define SPI_TXCRCR   *((volatile unsigned int *)(SPI1_BASE + 0x18))
#define SPI_I2SCFGR  *((volatile unsigned int *)(SPI1_BASE + 0x1C))
#define SPI_I2SPR    *((volatile unsigned int *)(SPI1_BASE + 0x20))

//TIMER Register Offsets
#define TIM6_CR1     *((volatile unsigned int *)(TIM6_BASE + 0x00))
#define TIM6_CR2     *((volatile unsigned int *)(TIM6_BASE + 0x04))
#define TIM6_DIER    *((volatile unsigned int *)(TIM6_BASE + 0x0C))
#define TIM6_SR   	 *((volatile unsigned int *)(TIM6_BASE + 0x10))
#define TIM6_EGR     *((volatile unsigned int *)(TIM6_BASE + 0x14))
#define TIM6_CNT     *((volatile unsigned int *)(TIM6_BASE + 0x24))
#define TIM6_PSC     *((volatile unsigned int *)(TIM6_BASE + 0x28))
#define TIM6_ARR     *((volatile unsigned int *)(TIM6_BASE + 0x2C))


void delay(void){
	for(volatile int i=0;i<200000;i++){
		continue;
	}
}

void spi_init(void){
  RCC_APB2ENR |= (1<<12);
  RCC_AHB1ENR |= (1<<0);
  GPIOA_MODER |= (2<<4*2)|(2<<5*2)|(2<<6*2)|(2<<7*2);
  GPIOA_AFRL |= (5<<4*4)|(5<<5*4)|(5<<6*4)|(5<<7*4);
  SPI_CR1 |= (1<<2)|(7<<3);
  SPI_CR2 |= (1<<2);
  SPI_CR1 |= (1<<6);
}

void spi_send(unsigned char c){
  while(!(SPI_SR & (1<<1)));
  SPI_DR = c;
  delay();
  while(!(SPI_SR & (1<<0)));
  unsigned char x=SPI_DR;
  (void)x;
}

unsigned char spi_receive(void){
  while(!(SPI_SR & (1<<0)));
  unsigned char c = SPI_DR;
  return c;
}

void spi_send_string(const unsigned char* str){
  while(*str)spi_send(*str++);
}

void adc_init(void){
	RCC_AHB1ENR |= (1<<0);
	RCC_APB2ENR |= (1<<8);
	GPIOA_MODER |= (3<<0);
	ADC1_CR1 |= (2<<24);
	ADC1_SMPR2 |= (7<<0);
	ADC1_CR2 |= (1<<0);
}

unsigned char adc_read(void){
	ADC1_CR2 |= (1<<30);
	while(!(ADC1_SR & (1<<1)));
	return ADC1_DR;
}

void dac_init(void){
	RCC_APB1ENR |= (1<<29);
	RCC_AHB1ENR |= (1<<0);
	GPIOA_MODER |= (3<<(4*2));
	DAC_CR 		|= (1<<0);
	DAC_DHR12R1  =  2048;
}

void tim_init(void){
	RCC_APB1ENR |= (1<<4);
	TIM6_PSC = 64000-1;
	TIM6_ARR = 250-1;
	TIM6_DIER |= (1<<0);
	TIM6_CR1  |= (1<<0);
}

void led_init(){
	RCC_AHB1ENR |= (1<<6);
	GPIOG_MODER |= (1<<(13*2))|(1<<(14*2));
	GPIOG_ODR |= (1<<13);
}

void toggle_led(void){
	GPIOG_ODR ^= ((1<<13)|(1<<14));
}

void TIM6_DAC_IRQHandler(void){
	toggle_led();
	TIM6_SR &= ~(1<<0);
}

void tim_nvic_init(void){
	NVIC_ISER1 |= (1<<(54%32));
}

int main(void) {
   // spi_init();
   // char * msg="hi this is a message sent via spi1\n";
   // spi_send_string(msg);
//   RCC_AHB1ENR |= (1<<6);
//   GPIOG_MODER |= (1<<(13*2));
//	adc_init();
//	dac_init();
	tim_nvic_init();
	led_init();
	tim_init();
    while (1) {
//    	GPIOG_ODR |= 1<<13;
//	volatile unsigned char x= adc_read();
//    if(x)GPIOG_ODR |=(1<<13);
//    else GPIOG_ODR &= ~(1<<13);
//        GPIOG_ODR &= ~(1<<13);
//        delay();
//        unsigned char x = GPIOA_IDR & 1;
//        if(x)GPIOG_ODR^=(1<<13);
//        delay();
    }
}

