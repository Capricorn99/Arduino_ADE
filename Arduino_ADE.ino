#include "ResDefine.h"

void spi_init() {
  pinMode(SPI_MOSI, OUTPUT);
  pinMode(SPI_MISO, INPUT);
  pinMode(SPI_CLK, OUTPUT);
  pinMode(SPI_SS, OUTPUT);
  digitalWrite(SPI_SS, HIGH); //disable device
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPHA)|(1<<SPR1)|(1<<SPR0);
  SPSR = (0<<SPI2X);
  clr = SPSR;
  clr = SPDR;
  delay(10);
  Serial.println("spi init complete");
  delay(1000);
}

void fill_buffer() {
  for (int i = 0; i < 128; i++) buffer[i]=i;
}

char spi_transfer(volatile char data) {
  SPDR = data;                    // Start the transmission
  while (!(SPSR & (1<<SPIF)));    // Wait the end of the transmission
  return SPDR;                    // return the received byte
}

void write_to_eeprom(int address, long write_buffer, int bytes_to_write) {
  byte write_cmd = 0x80;
  byte write_data = 0x00;
  address |= write_cmd;
  digitalWrite(SPI_SS, LOW);
  spi_transfer((char) address);      //send address

  //here there should be a t7 delay, however long that is
  for (int i = 0; i < bytes_to_write; i++) {
    write_data = (byte) write_buffer >> (8*((bytes_to_write - 1) - i));
    spi_transfer((char) write_data);      //send data byte
  }
  digitalWrite(SPI_SS, HIGH); //release chip, signal end transfer
}

long read_eeprom(int address, int bytes_to_read) {
//  Serial.println("Data starts: ");
  long data = 0;
  byte reader_buf = 0;
  digitalWrite(SPI_SS, LOW);
  spi_transfer((char) address);      //send LSByte address
  for (int i = 1; i <= bytes_to_read; i++){
    reader_buf = spi_transfer(0xFF); //get data byte
//    Serial.println(reader_buf, BIN);

    data |= reader_buf;
    if (i < bytes_to_read) data = data << 8;
  }
//  Serial.print("completed. data: ");
//  Serial.println(data, BIN);
  digitalWrite(SPI_SS, HIGH); //release chip, signal end transfer
  return data;
}

void setup() {
  Serial.begin(115200);
  spi_init();
  
  // Test write
  address = LINECYC;
  Serial.print(address, HEX);
  eeprom_output_data = read_eeprom(STATUS, 2);

  long TestWrite;
  TestWrite = 0xABCD;
  Serial.println(TestWrite, BIN);
  write_to_eeprom(address, TestWrite, 2);
  Serial.println(eeprom_output_data, BIN);
  eeprom_output_data = read_eeprom(address, 2);
  Serial.println("Completed basic read write test");
  delay(3000);
  write_to_eeprom(GAIN, 0x00, 1);
  eeprom_output_data = read_eeprom(GAIN, 1);
  Serial.print("GAIN: ");
  Serial.println(eeprom_output_data, HEX);
  delay(1000);
//  long_eeprom_data = read_eeprom(VRMS, 3);
//  for (int i = 0; i < MAX_BUF; i++) {
//    vrms_buf[i] = long_eeprom_data;
//  }
}

void loop() {
  double vrms_out = 0;
  
  long_eeprom_data = read_eeprom(VRMS, 3);
//  Serial.println("VRMS CHECK");
//  Serial.println(long_eeprom_data);
//  Serial.println(long_eeprom_data, HEX);
  for (int i = MAX_BUF - 1; i > 0; i--) {
    vrms_buf[i] = vrms_buf[i - 1];
  }
  vrms_buf[0] = long_eeprom_data;
  
  for (int i = 0; i < MAX_BUF; i++) {
    vrms_out += vrms_buf[i];
  }

  vrms_out = (vrms_out - 74240)/2194.3;
  if ((unsigned long) (millis() - time) > 1000) {
    Serial.print(vrms_out/MAX_BUF);
    Serial.println("V");
    time = millis();
  }
  delay(10);
  
}
