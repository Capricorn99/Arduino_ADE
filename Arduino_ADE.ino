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
    write_data = (byte) (write_buffer >> (8*((bytes_to_write - 1) - i)));
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
  while(!Serial) delay(50);
  spi_init();
  
  write_to_eeprom(GAIN, 0x00, 1);
  Serial.print("GAIN: ");
  Serial.println(read_eeprom(GAIN, 1), HEX);
  delay(1000);
  
  Serial.print("MODE: ");
  Serial.println(read_eeprom(MODE, 2), HEX);
  delay(1000);

  //write_to_eeprom(MODE,0x000C,2);
}

void loop() {
  
  Serial.print("VRMS: ");
  Serial.println(read_eeprom(VRMS, 3));
  delay(1000);

}
