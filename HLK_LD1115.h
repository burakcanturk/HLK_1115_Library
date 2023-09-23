#ifndef _HLK_LD1115_
#define _HLK_LD1115_

#define HLK_LD1115_BAUD 115200

#define ld1115_occ_txt "occ,"
#define ld1115_mov_txt "mov,"

#define ld1115_conf_vals_len 6

#define ld1115_get_all_str "get_all"

#define ld1115_save_str "save"
#define ld1115_save_suc_str "all vars have been saved\r"

#include <Arduino.h>
#ifndef _BOARD_GENERIC_STM32F103C_H_
#include <SoftwareSerial.h>
#endif

class HLK_LD1115 {

  public:
#ifndef ESP32
#ifndef _BOARD_GENERIC_STM32F103C_H_
    HLK_LD1115(SoftwareSerial *ssUart);
#endif
#else
    HLK_LD1115(EspSoftwareSerial::UART *ssEspUart);
    HLK_LD1115(uint8_t rx, uint8_t tx, EspSoftwareSerial::UART *ssEspUart);
    HLK_LD1115(uint8_t rx, uint8_t tx, HardwareSerial *hsUart);
#endif
    HLK_LD1115(HardwareSerial *hsUart);
    HLK_LD1115(uint8_t rx, uint8_t tx);
    void begin();
    void read();
    String getDisType();
    uint8_t getOccDis();
    uint8_t getMovDis();
    uint16_t getOccStr();
    uint16_t getMovStr();
    void getAllSettings();
    int32_t getTh1();
    int32_t getTh2();
    int32_t getThIn();
    bool getOutputMode();
    int32_t getTons();
    uint16_t getUtons();
    bool saveAllSettings();
    bool setTh1(int32_t th1); // 130
    bool setTh2(int32_t th2); // 250
    bool setThIn(int32_t th_in); // 300
    bool setOutputMode(bool output_mode); // 0
    bool setTons(int32_t tons); // 30
    bool setUtons(uint16_t utons); // 100

  private:

    bool is_soft;

#ifndef ESP32
#ifndef _BOARD_GENERIC_STM32F103C_H_
    SoftwareSerial *SS;
#endif
#else
    EspSoftwareSerial::UART *SS;
#endif
    HardwareSerial *HS;

    bool with_pins;
    bool with_ser;

    uint16_t rx_pin;
    uint16_t tx_pin;

    struct ld1115_datas {
      String dis_type;
      uint8_t occ_dis;
      uint8_t mov_dis;
      uint16_t occ_str;
      uint16_t mov_str;
    } ld1115_data;

    struct ld1115_conf_datas {
      int32_t th1;
      int32_t th2;
      int32_t th_in;
      bool output_mode;
      int32_t tons;
      uint16_t utons;
    } ld1115_conf_data;
};

#endif
