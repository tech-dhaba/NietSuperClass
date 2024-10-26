unsigned char EEPROM_read(uint16_t uiAddress) {
  while(EECR & (1<<EEPE));
  EEAR = uiAddress;
  EECR |= (1<<EERE);
  return EEDR;
}

void EEPROM_write(unsigned int uiAddress, unsigned char ucData) {
  while(EECR & (1<<EEPE));
  EEAR = uiAddress;
  EEDR = ucData;
  EECR |= (1<<EEMPE);
  EECR |= (1<<EEPE); 
}

int main(void){
  char *name="shivam";
  for(int i=0;i<sizeof(name);i++){
    EEPROM_write(0x11+i, name[i]);
    _delay_ms(10);
  } 
  char read[10];
  DDRB|=(1<<PB5);
  for(int i=0;i<sizeof(name);i++){
    read[i]=EEPROM_read(0x11+i);
    _delay_ms(10);
  }
  uint8_t flag=0;
  for(int i=0;i<sizeof(name);i++){
    if(name[i]!=read[i])flag=1;
  }
  if(flag)PORTB&=~(1<<PB5);
  else PORTB|=(1<<PB5);
}
