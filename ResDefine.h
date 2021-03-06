#define WAVEFORM     0x01  //24bits
#define AENERGY     0x02  //24bits
#define RAENERGY    0x03  //24bits
#define LAENERGY    0x04  //24bits
#define VAENERGY    0x05  //24bits
#define RVAENERGY   0x06  //24bits
#define LVAENERGY   0x07  //24bits
#define LVARENERGY  0x08  //24bits

#define MODE        0x09
#define IRQEN       0x0A
#define STATUS      0x0B
#define RSTSTATUS   0x0C

#define CH1OS       0x0D
#define CH2OS       0x0E
#define GAIN        0x0F
#define PHCAL       0x10

#define APOS        0x11
#define WGAIN       0x12  //12bits
#define WDIV        0x13
#define CFNUM       0x14  //12bits
#define CFDEN       0x15
#define IRMS        0x16
#define VRMS        0x17
#define IRMSOS      0x18
#define VRMSOS      0x19
#define VAGAIN      0x1A
#define VADIV       0x1B
#define LINECYC     0x1C
#define ZXTOUT      0x1D
#define SAGCYC      0x1E
#define SAGLVL      0x1F
#define IPKLVL      0x20
#define VPKLVL      0x21
#define IPEAK       0x22
#define RSTIPEAK    0x23
#define VPEAK       0x24
#define RSTVPEAK    0x25
#define TEMP        0x26
#define PERIOD      0x27

#define TMODE       0x3D
#define CHKSUM      0x3E
#define DIEREV      0x3F

#define SPI_MOSI    11  //MOSI
#define SPI_MISO    12  //MISO 
#define SPI_CLK     13  //SCK
#define SPI_SS      10  //SS

//opcodes
#define WREN  6
#define WRDI  4
#define RDSR  5
#define WRSR  1
#define READ  3
#define WRITE 2

//SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPOL)|(1<<CPHA)|(1<<SPR1)|(1<<SPR0); //set clock rate to 1/16th system

byte eeprom_output_data;
byte multi_byte_data[3];
byte eeprom_input_data = 0;
long long_eeprom_data = 0;
byte clr;
