#include "ADBMS1818.hpp"

std::map<std::string, uint16_t> ADBMS1818::commands = {
            {"WRCFGA", 0x0001},
            {"WRCFGB", 0x0024},
            {"RDCFGA", 0x0002},
            {"RDCFGB", 0x0026},
            {"RDCVA", 0x0004},
            {"RDCVB", 0x0006},
            {"RDCVC", 0x0008},
            {"RDCVD", 0x000a},
            {"RDCVE", 0x0009},
            {"RDCVF", 0x000b},
            {"RDAUXA", 0x000c},
            {"RDAUXB", 0x000e},
            {"RDAUXC", 0x000d},
            {"RDAUXD", 0x000f},
            {"RDSTATA", 0x0010},
            {"RDSTATB", 0x0012},
            {"WRSCTRL", 0x0014},
            {"WRPWM", 0x0020},
            {"WRPSB", 0x001c},
            {"RDSCTRL", 0x0016},
            {"RDPWM", 0x0022},
            {"RDPSB", 0x001e},
            {"STSCTRL", 0x0019},
            {"CLRSCTRL", 0x0018},//commands which needs setup. Default setup is 0 for all setting bits
            {"ADCV", 0x0260},
            {"ADOW", 0x0228},
            {"CVST", 0x0207},
            {"ADOL", 0x0201},
            {"ADAX", 0x0460},
            {"ADAXD", 0x0400},
            {"AXOW", 0x0410},
            {"AXST", 0x0407},
            {"ADSTAT", 0x0468},
            {"ADSTATD", 0x0408},
            {"STATST", 0x040f},
            {"ADCVAX", 0x046f},
            {"ADCVSC", 0x0467},//those commands dont any bit setting
            {"CLRCELL", 0x0711},
            {"CLRAUX", 0x0712},
            {"CLRSTAT", 0x0713},
            {"PLADC", 0x0714},
            {"DIAGN", 0x0715},
            {"WRCOMM", 0x0721},
            {"RDCOMM", 0x0722},
            {"STCOMM", 0x0723},
            {"Mute", 0x0028},
            {"Unmute", 0x0029}
        };

std::map<std::string, uint8_t> ADBMS1818::commands_bits = {
    {"MD", 2}, //7kHz
    {"DCP", 1}, //discharge permitted
    {"CH", 0},  //all cells conversion
    {"CHG", 0}, //all gpios conversion
    {"CHST", 0}, //
    {"PUP", 0}, //pull down current
    {"ST", 1} //self test 1
};

void ADBMS1818::u16_to_u8(uint16_t x, uint8_t *y){
    y[0] = x >> 8;
    y[1] = x & 0x00FF;
}


ADBMS1818::ADBMS1818(uint16_t port, uint8_t cspin, uint32_t freq, uint8_t n, uint8_t br): f(freq), cs(cspin), n(n), byte_reg(br){
    spi.begin(port);
    spi.setFrequency(freq);
    this->init();
}
ADBMS1818::ADBMS1818(int8_t spi_pins[4],uint32_t freq, uint8_t n, uint8_t br): f(freq), cs(spi_pins[3]), n(n), byte_reg(br){
    spi.begin(spi_pins[0], spi_pins[1], spi_pins[2], cs);
    spi.setFrequency(freq);
    this->init();
}
ADBMS1818::ADBMS1818(uint8_t cspin, uint32_t freq, uint8_t n, uint8_t br): f(freq), cs(cspin), n(n), byte_reg(br){
    spi.begin();
    
    this->init();
}
void ADBMS1818::init(){
    spi.setFrequency(f);
    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);
    this->init_pec_15_table();
    uint16_t rbuff_size = (this->byte_reg+2)*this->n;
    uint16_t wbuff_size = (this->byte_reg)*this->n;
    this->read_buff = new uint8_t [rbuff_size];
    this->write_buff = new uint8_t [wbuff_size];
    this->vuv = 0;
    this->vov = 0;
    this->dcc = 0;
    this->dcto = 0;
    this->gpiox = 0x01ff;
    this->adcopt = false;
    this->refon = false;
    this->dtmen = true;
    this->mute = false;
    this->fdrf = false;
    this->pladc_timeout = 1000;
}

void ADBMS1818::init_pec_15_table(){
    uint16_t crc_15_poly = 0x4599;
    uint16_t remainder;
    for(unsigned i=0;i<256;i++){
        remainder = i << 7;
        for(unsigned bit=8; bit>0; --bit){
            if (remainder & 0x4000)
            {
                remainder = ((remainder << 1));
                remainder = (remainder ^ crc_15_poly);
            }
            else
            {
                remainder = ((remainder << 1));
            }
            }
        this->pec15Table[i] = remainder&0xFFFF;
    }
}

void ADBMS1818::pec_15(uint8_t *tab, uint8_t len){
    this->pec = 0x0010;
    uint16_t address;
    for(unsigned i=0;i<len;i++){
        address = ((this->pec>>7)^tab[i])&0xff;
        this->pec = (this->pec << 8)^this->pec15Table[address];
    }
}

void ADBMS1818::set_device_count(uint8_t n){
    this->n = n;
    delete[] this->write_buff;
    delete[] this->read_buff;
    uint16_t rbuff_size = (this->byte_reg+2)*this->n;
    uint16_t wbuff_size = (this->byte_reg)*this->n;
    this->read_buff = new uint8_t [rbuff_size];
    this->write_buff = new uint8_t [wbuff_size];
}

void ADBMS1818::poll_command(uint8_t command[2]){
    this->pec_15(command, 2);
    digitalWrite(this->cs, LOW);
    spi.transfer(command, 2);
    spi.transfer16(this->pec);
    digitalWrite(this->cs, HIGH);
}

void ADBMS1818::write_command(uint8_t command[2], uint8_t *data){
    this->pec_15(command, 2);
    digitalWrite(this->cs, LOW);
    spi.transfer(command, 2);
    spi.transfer16(this->pec);
    for(unsigned i = this->n; i>0; i--){
        for(unsigned j=0;j<this->byte_reg;j++){
            spi.transfer(data[j]);
        }
        this->pec_15(data+(this->n - i)*this->byte_reg, this->byte_reg);
        spi.transfer16(this->pec);
    }
    digitalWrite(this->cs, HIGH);
}

bool ADBMS1818::read_command(uint8_t command[2], uint8_t *data){
    this->pec_15(command, 2);
    digitalWrite(this->cs, LOW);
    spi.transfer(command, 2);
    spi.transfer16(this->pec);
    uint16_t test_pec;
    bool test = true;
    for(unsigned i= 0; i<this->n;i++){
        for(unsigned j=i*(this->byte_reg+2); j< (i+1)*(this->byte_reg+2);j++){
            data[j] = spi.transfer(0x00);
        }
        this->pec_15(data+(this->byte_reg+2)*i, this->byte_reg);
        test_pec = data[i*(this->byte_reg+2)+6];
        test_pec <<= 8 ;
        test_pec |= data[i*(this->byte_reg+2)+7];
        if(test_pec != this->pec){
            test =  false;
        }
    }

    return test;
}


void ADBMS1818::wake_up(uint8_t dur){
    digitalWrite(cs, HIGH);
    delay(dur);
    digitalWrite(cs, LOW);
    delay(dur);
    digitalWrite(cs, HIGH);
}

void ADBMS1818::set_bits(std::string bit_key, uint8_t bit_value){
    this->commands_bits[bit_key] = bit_value;
}

void ADBMS1818::set_config_reg_a(){
    for(int i=0;i<this->byte_reg*this->n;i++){
        this->write_buff[i] = 0x00;
    }
    for(int i=0;i<this->byte_reg*this->n;i+=this->byte_reg){
        this->write_buff[i] = (uint8_t)(this->gpiox << 3);
        this->write_buff[i] = this->config_bit(this->write_buff[i], 0, this->adcopt);
        this->write_buff[i] = this->config_bit(this->write_buff[i], 2, this->refon);
        this->write_buff[(i+1)] = (uint8_t) (0x00ff & this->vuv);
        this->write_buff[(i+2)] = (uint8_t) (this->vuv >> 8);
        this->write_buff[(i+2)] |= (uint8_t) ( (this->vov & 0x000f) << 4);
        this->write_buff[(i+3)] = (uint8_t) (this->vov >> 4);
        this->write_buff[(i+4)] = (uint8_t)(this->dcc & 0x00ff);
        this->write_buff[(i+5)] = (uint8_t)(this->dcc >> 8);
        this->write_buff[(i+5)] |= (uint8_t)(this->dcto << 4);
    }
    
    uint8_t command[2];
    command[0] = (uint8_t) this->commands["WRCFGA"] & 0x00FF;
    command[1] = (uint8_t) this->commands["WRCFGA"] >> 8 ;
    this->write_command(command, this->write_buff);
}

void ADBMS1818::set_config_reg_b(){
    for(int i=0;i<this->byte_reg*this->n;i++){
        this->write_buff[i] = 0x00;
    }
    for(int i=0;i<this->byte_reg*this->n;i+=this->byte_reg){
        
    }
    uint8_t command[2];
    command[0] = (uint8_t) this->commands["WRCFGB"] & 0x00FF;
    command[1] = (uint8_t) this->commands["WRCFGB"] >> 8 ;
    this->write_command(command, this->write_buff);
}


void ADBMS1818::begin(){
    this->wake_up();
    this->set_config_reg_a();
    this->set_config_reg_b();
    
}

uint16_t ADBMS1818::config_bit(uint16_t command, uint8_t pos, bool bit){
    uint16_t bit_filter = 1;
    bit_filter <<= pos;
    return bit? command | bit_filter: command & (~bit_filter);
}

uint16_t ADBMS1818::config_md_bits(uint16_t command){
    uint8_t bits = this->commands_bits["MD"];
    for(int i=0;i<2;i++){
        bool b = bits & 0x0001;
        bits >>= 1;
        command = this->config_bit(command, (uint8_t)(7+i), b);
    }
    return command;
}
uint16_t ADBMS1818::config_dcp_bit(uint16_t command){
    command = this->config_bit(command, 4, (this->commands_bits["DCP"]&0x0001));
    return command;
}
uint16_t ADBMS1818::config_ch_bits(uint16_t command, std::string key){
    uint8_t bits = this->commands_bits[key];
    for(int i=0;i<3;i++){
        bool b = bits & 0x0001;
        bits >>= 1;
        command = this->config_bit(command, (uint8_t)i, b);
    }
    return command;
}
uint16_t ADBMS1818::config_st_bits(uint16_t command){
    uint8_t bits = this->commands_bits["ST"];
    for(int i=0;i<2;i++){
        bool b = bits & 0x0001;
        bits >>= 1;
        command = this->config_bit(command, (uint8_t)(5+i), b);
    }
    return command;
}
uint16_t ADBMS1818::config_pup_bit(uint16_t command){
    command = this->config_bit(command, 6, (this->commands_bits["PUP"]&0x0001));
    return command;
}
void ADBMS1818::start_cv_adc_conversion(){
    uint16_t command = this->commands["ADCV"];
    command = this->config_md_bits(command);
    command = this->config_dcp_bit(command);
    command = this->config_ch_bits(command, "CH");
    uint8_t command2[2];
    this->u16_to_u8(this->commands["Mute"], command2);
    this->poll_command(command2);
    this->u16_to_u8(command, command2);
    this->poll_command(command2);
    this->u16_to_u8(this->commands["Unmute"], command2);
    this->poll_command(command2);
}
void ADBMS1818::start_open_wire_conversion(){
    uint16_t command = this->commands["ADOW"];
    command = this->config_md_bits(command);
    command = this->config_dcp_bit(command);
    command = this->config_ch_bits(command, "CH");
    command = this->config_pup_bit(command);
    uint8_t command2[2];
    this->u16_to_u8(this->commands["Mute"], command2);
    this->poll_command(command2);
    this->u16_to_u8(command, command2);
    this->poll_command(command2);
    this->u16_to_u8(this->commands["Unmute"], command2);
    this->poll_command(command2);
}

void ADBMS1818::start_self_test_conversion(){
    uint16_t command = this->commands["CVST"];
    command = this->config_md_bits(command);
    command = this->config_st_bits(command);
    uint8_t command2[2];
    this->u16_to_u8(this->commands["Mute"], command2);
    this->poll_command(command2);
    this->u16_to_u8(command, command2);
    this->poll_command(command2);
    this->u16_to_u8(this->commands["Unmute"], command2);
    this->poll_command(command2);
}

void ADBMS1818::start_overlap_conversion(){
    uint16_t command = this->commands["ADOL"];
    command = this->config_md_bits(command);
    command = this->config_dcp_bit(command);
    uint8_t command2[2];
    this->u16_to_u8(this->commands["Mute"], command2);
    this->poll_command(command2);
    this->u16_to_u8(command, command2);
    this->poll_command(command2);
    this->u16_to_u8(this->commands["Unmute"], command2);
    this->poll_command(command2);
}

void ADBMS1818::start_gpio_adc_conversion(){
    uint16_t command = this->commands["ADAX"];
    command = this->config_md_bits(command);
    command = this->config_ch_bits(command, "CHG");
    uint8_t command2[2];
    this->u16_to_u8(this->commands["Mute"], command2);
    this->poll_command(command2);
    this->u16_to_u8(command, command2);
    this->poll_command(command2);
    this->u16_to_u8(this->commands["Unmute"], command2);
    this->poll_command(command2);
}
void ADBMS1818::start_gpio_adc_conversion_dr(){
    uint16_t command = this->commands["ADAXD"];
    command = this->config_md_bits(command);
    command = this->config_ch_bits(command, "CHG");
    uint8_t command2[2];
    this->u16_to_u8(this->commands["Mute"], command2);
    this->poll_command(command2);
    this->u16_to_u8(command, command2);
    this->poll_command(command2);
    this->u16_to_u8(this->commands["Unmute"], command2);
    this->poll_command(command2);
}
void ADBMS1818::start_gpio_open_wire_conversion(){
    uint16_t command = this->commands["AXOW"];
    command = this->config_md_bits(command);
    command = this->config_ch_bits(command, "CHG");
    command = this->config_pup_bit(command);
    uint8_t command2[2];
    this->u16_to_u8(this->commands["Mute"], command2);
    this->poll_command(command2);
    this->u16_to_u8(command, command2);
    this->poll_command(command2);
    this->u16_to_u8(this->commands["Unmute"], command2);
    this->poll_command(command2);
}
void ADBMS1818::start_self_test_gpio_conversion(){
    uint16_t command = this->commands["AXST"];
    command = this->config_md_bits(command);
    command = this->config_st_bits(command);
    uint8_t command2[2];
    this->u16_to_u8(this->commands["Mute"], command2);
    this->poll_command(command2);
    this->u16_to_u8(command, command2);
    this->poll_command(command2);
    this->u16_to_u8(this->commands["Unmute"], command2);
    this->poll_command(command2);
}
void ADBMS1818::start_status_adc_conversion(){
    uint16_t command = this->commands["ADSTAT"];
    command = this->config_md_bits(command);
    command = this->config_ch_bits(command, "CHST");
    uint8_t command2[2];
    this->u16_to_u8(this->commands["Mute"], command2);
    this->poll_command(command2);
    this->u16_to_u8(command, command2);
    this->poll_command(command2);
    this->u16_to_u8(this->commands["Unmute"], command2);
    this->poll_command(command2);
}
void ADBMS1818::start_status_adc_dr_conversion(){
    uint16_t command = this->commands["ADSTATD"];
    command = this->config_md_bits(command);
    command = this->config_ch_bits(command, "CHST");
    uint8_t command2[2];
    this->u16_to_u8(this->commands["Mute"], command2);
    this->poll_command(command2);
    this->u16_to_u8(command, command2);
    this->poll_command(command2);
    this->u16_to_u8(this->commands["Unmute"], command2);
    this->poll_command(command2);
}

void ADBMS1818::start_self_test_status_conversion(){
    uint16_t command = this->commands["STATST"];
    command = this->config_md_bits(command);
    command = this->config_st_bits(command);
    uint8_t command2[2];
    this->u16_to_u8(this->commands["Mute"], command2);
    this->poll_command(command2);
    this->u16_to_u8(command, command2);
    this->poll_command(command2);
    this->u16_to_u8(this->commands["Unmute"], command2);
    this->poll_command(command2);
}
void ADBMS1818::start_cv_gpio12_conversion(){
    uint16_t command = this->commands["ADCVAX"];
    command = this->config_md_bits(command);
    command = this->config_dcp_bit(command);
    uint8_t command2[2];
    this->u16_to_u8(this->commands["Mute"], command2);
    this->poll_command(command2);
    this->u16_to_u8(command, command2);
    this->poll_command(command2);
    this->u16_to_u8(this->commands["Unmute"], command2);
    this->poll_command(command2);
}
void ADBMS1818::start_cv_sc_conversion(){
    uint16_t command = this->commands["ADCVSC"];
    command = this->config_md_bits(command);
    command = this->config_dcp_bit(command);
    uint8_t command2[2];
    this->u16_to_u8(this->commands["Mute"], command2);
    this->poll_command(command2);
    this->u16_to_u8(command, command2);
    this->poll_command(command2);
    this->u16_to_u8(this->commands["Unmute"], command2);
    this->poll_command(command2);
}

uint16_t** ADBMS1818::read_cv_adc(){
    uint16_t **cells_voltage = new uint16_t *[this->n];
    for(int i=0;i<this->n;i++){
        cells_voltage[i] = new uint16_t [18];
    }
    uint16_t command;
    uint8_t command2[2];
    std::vector<std::string> comm_keys {"RDCVA", "RDCVB", "RDCVC", "RDCVD", "RDCVE", "RDCVF"};
    int j = 0;
    for(std::string key: comm_keys){
        command = this->commands[key];
        this->u16_to_u8(command, command2);
        this->read_command(command2, this->read_buff);
        for(int i=0;i<this->n;i++){
            for(int k=0;k<6;k+=2){
                    cells_voltage[i][(k/2+j)] = this->read_buff[(i*8+ k+1)];
                    cells_voltage[i][(k/2+j)] <<= 8;
                    cells_voltage[i][(k/2+j)] |= this->read_buff[i*8+k];
                }
            
        }
        j += 3;
    }
    
    return cells_voltage;
}
uint16_t ** ADBMS1818::read_aux_adc(){
    uint16_t **aux_voltage = new uint16_t *[this->n];
    for(int i=0;i<this->n;i++){
        aux_voltage[i] = new uint16_t [9];
    }
    std::vector<std::string> comm_keys = {"RDAUXA", "RDAUXC"};
    std::string last_command = "RDAUXD", second_command = "RDAUXB";
    uint16_t command;
    uint8_t command2[2];
    int j = 0;
    for(std::string key: comm_keys){
        command = this->commands[key];
        this->u16_to_u8(command, command2);
        this->read_command(command2, this->read_buff);
        for(int i=0;i<this->n;i++){
            for(int k=0;k<6;k+=2){
                aux_voltage[i][(k/2+j)] = this->read_buff[i*8+ k+1];
                aux_voltage[i][(k/2+j)] <<= 8;
                aux_voltage[i][(k/2+j)] |= this->read_buff[i*8+ k];
            }
        }
        j += 3;
    }
    command = this->commands[second_command];
    this->u16_to_u8(command, command2);
    this->read_command(command2, this->read_buff);
    for(int i=0;i<this->n;i++){
        for(int k=0;k<4;k+=2){
            aux_voltage[i][(k/2+j)] = this->read_buff[i*8+ k+1];
            aux_voltage[i][(k/2+j)] <<= 8;
            aux_voltage[i][(k/2+j)] |= this->read_buff[i*8+ k];
        }
    }
    j+= 2;
    command = this->commands[last_command];
    this->u16_to_u8(command, command2);
    this->read_command(command2, this->read_buff);
    for(int i=0;i<this->n;i++){
        aux_voltage[i][j] = this->read_buff[i*8+1];
        aux_voltage[i][j] <<= 8;
        aux_voltage[i][j] |= this->read_buff[i*8];
    }
    return aux_voltage;
}

float ADBMS1818::convert_voltage(uint16_t voltage){
    return 0.000001 * (float)voltage;
}

bool ADBMS1818::pladc_rdy(){
    uint16_t command = this->commands["PLADC"];
    uint8_t command2[2];
    this->u16_to_u8(command, command2);
    this->pec_15(command2, 2);
    digitalWrite(this->cs, LOW);
    spi.transfer(command2, 2);
    spi.transfer16(this->pec);
    uint8_t result=0;
    unsigned long time = micros();
    while((micros()-time)<=this->pladc_timeout&&(result==0)){
        result = spi.transfer(0x00);
    }
    digitalWrite(this->cs, HIGH);
    return result != 0;
}