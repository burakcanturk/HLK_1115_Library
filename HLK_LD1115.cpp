#include "HLK_LD1115.h"

#ifndef ESP32

#ifndef _BOARD_GENERIC_STM32F103C_H_

HLK_LD1115::HLK_LD1115(SoftwareSerial *ssUart) {
  is_soft = true;
  with_pins = false;
  with_ser = true;
  SS = ssUart;
}

#endif

#else

HLK_LD1115::HLK_LD1115(EspSoftwareSerial::UART *ssEspUart) {
  is_soft = true;
  with_pins = false;
  with_ser = true;
  SS = ssEspUart;
}

HLK_LD1115::HLK_LD1115(uint8_t rx, uint8_t tx, EspSoftwareSerial::UART *ssEspUart) {
  is_soft = true;
  with_pins = true;
  with_ser = true;
  rx_pin = rx;
  tx_pin = tx;
  SS = ssEspUart;
}

HLK_LD1115::HLK_LD1115(uint8_t rx, uint8_t tx, HardwareSerial *hsUart) {
  is_soft = false;
  with_pins = true;
  with_ser = true;
  rx_pin = rx;
  tx_pin = tx;
  HS = hsUart;
}

#endif

HLK_LD1115::HLK_LD1115(HardwareSerial *hsUart) {
  is_soft = false;
  with_pins = false;
  with_ser = true;
  HS = hsUart;
}

HLK_LD1115::HLK_LD1115(uint8_t rx, uint8_t tx) {
  is_soft = true;
  with_pins = true;
  with_ser = false;
  rx_pin = rx;
  tx_pin = tx;
}

void HLK_LD1115::begin() {

#ifndef ESP32

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {
    if (not with_pins)
      SS->begin(HLK_LD1115_BAUD);
    else {
      SoftwareSerial ssUart(rx_pin, tx_pin);
      SS = &ssUart;
      SS->begin(HLK_LD1115_BAUD);
    }
  }

#endif

  if (not is_soft)
    HS->begin(HLK_LD1115_BAUD);

#else

  if (is_soft) {
    if (not with_pins)
      SS->begin(HLK_LD1115_BAUD);
    else {
      if (with_ser)
        SS->begin(HLK_LD1115_BAUD, EspSoftwareSerial::SWSERIAL_8N1, rx_pin, tx_pin);
      else {
        EspSoftwareSerial::UART ssUart(rx_pin, tx_pin);
        SS = &ssUart;
        SS->begin(HLK_LD1115_BAUD);
      }
    }
  }

  else {
    if (not with_pins)
      HS->begin(HLK_LD1115_BAUD);
    else
      HS->begin(HLK_LD1115_BAUD, SERIAL_8N1, rx_pin, tx_pin);
  }

#endif
}

void HLK_LD1115::read() {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String data_str = SS->readStringUntil('\n');

    String data_type = data_str.substring(0, data_str.indexOf(' '));

    if (data_type == ld1115_mov_txt) {

      ld1115_data.dis_type = "mov";

      String data_vals = data_str.substring(data_str.indexOf(' ') + 1, data_str.length());

      String dis_val_str = data_vals.substring(0, data_vals.indexOf(' '));
      ld1115_data.mov_dis = dis_val_str.toInt();

      String str_val_str = data_vals.substring(data_vals.indexOf(' ') + 1, data_vals.length());
      ld1115_data.mov_str = str_val_str.toInt();
    }

    else if (data_type == ld1115_occ_txt) {

      ld1115_data.dis_type = "occ";

      String data_vals = data_str.substring(data_str.indexOf(' ') + 1, data_str.length());

      String dis_val_str = data_vals.substring(0, data_vals.indexOf(' '));
      ld1115_data.occ_dis = dis_val_str.toInt();

      String str_val_str = data_vals.substring(data_vals.indexOf(' ') + 1, data_vals.length());
      ld1115_data.occ_str = str_val_str.toInt();
    }
  }

#endif

  if (not is_soft) {

    String data_str = HS->readStringUntil('\n');

    String data_type = data_str.substring(0, data_str.indexOf(' '));

    if (data_type == ld1115_mov_txt) {

      ld1115_data.dis_type = "mov";

      String data_vals = data_str.substring(data_str.indexOf(' ') + 1, data_str.length());

      String dis_val_str = data_vals.substring(0, data_vals.indexOf(' '));
      ld1115_data.mov_dis = dis_val_str.toInt();

      String str_val_str = data_vals.substring(data_vals.indexOf(' ') + 1, data_vals.length());
      ld1115_data.mov_str = str_val_str.toInt();
    }

    else if (data_type == ld1115_occ_txt) {

      ld1115_data.dis_type = "occ";

      String data_vals = data_str.substring(data_str.indexOf(' ') + 1, data_str.length());

      String dis_val_str = data_vals.substring(0, data_vals.indexOf(' '));
      ld1115_data.occ_dis = dis_val_str.toInt();

      String str_val_str = data_vals.substring(data_vals.indexOf(' ') + 1, data_vals.length());
      ld1115_data.occ_str = str_val_str.toInt();
    }
  }
}

String HLK_LD1115::getDisType() {
  return ld1115_data.dis_type;
}

uint8_t HLK_LD1115::getOccDis() {
  return ld1115_data.occ_dis;
}

uint8_t HLK_LD1115::getMovDis() {
  return ld1115_data.mov_dis;
}

uint16_t HLK_LD1115::getOccStr() {
  return ld1115_data.occ_str;
}

uint16_t HLK_LD1115::getMovStr() {
  return ld1115_data.mov_str;
}

void HLK_LD1115::getAllSettings() {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    SS->println(ld1115_get_all_str);

    for (int i = 0; i < ld1115_conf_vals_len; i++) {

      String conf_data_str = SS->readStringUntil('\n');

      String conf_data_type = conf_data_str.substring(0, conf_data_str.indexOf(' '));

      String conf_data_type_split = conf_data_str.substring(conf_data_str.indexOf(' ') + 1, conf_data_str.length());

      String conf_data_type_split_suc = conf_data_type_split.substring(0, conf_data_type_split.indexOf(' '));

      if (conf_data_type_split_suc == "is") {

        String conf_data_type_split_val = conf_data_type_split.substring(conf_data_type_split.indexOf(' '), conf_data_type_split.length());

        if (conf_data_type == "th1")
          ld1115_conf_data.th1 = conf_data_type_split_val.toInt();

        else if (conf_data_type == "th2")
          ld1115_conf_data.th2 = conf_data_type_split_val.toInt();

        else if (conf_data_type == "th_in")
          ld1115_conf_data.th_in = conf_data_type_split_val.toInt();

        else if (conf_data_type == "output_mode")
          ld1115_conf_data.output_mode = conf_data_type_split_val.toInt();

        else if (conf_data_type == "tons")
          ld1115_conf_data.tons = conf_data_type_split_val.toInt();

        else if (conf_data_type == "utons")
          ld1115_conf_data.utons = conf_data_type_split_val.toInt();
      }
    }
  }

#endif

  if (not is_soft) {

    HS->println(ld1115_get_all_str);

    for (int i = 0; i < ld1115_conf_vals_len; i++) {

      String conf_data_str = HS->readStringUntil('\n');

      String conf_data_type = conf_data_str.substring(0, conf_data_str.indexOf(' '));

      String conf_data_type_split = conf_data_str.substring(conf_data_str.indexOf(' ') + 1, conf_data_str.length());

      String conf_data_type_split_suc = conf_data_type_split.substring(0, conf_data_type_split.indexOf(' '));

      if (conf_data_type_split_suc == "is") {

        String conf_data_type_split_val = conf_data_type_split.substring(conf_data_type_split.indexOf(' '), conf_data_type_split.length());

        if (conf_data_type == "th1")
          ld1115_conf_data.th1 = conf_data_type_split_val.toInt();

        else if (conf_data_type == "th2")
          ld1115_conf_data.th2 = conf_data_type_split_val.toInt();

        else if (conf_data_type == "th_in")
          ld1115_conf_data.th_in = conf_data_type_split_val.toInt();

        else if (conf_data_type == "output_mode")
          ld1115_conf_data.output_mode = conf_data_type_split_val.toInt();

        else if (conf_data_type == "tons")
          ld1115_conf_data.tons = conf_data_type_split_val.toInt();

        else if (conf_data_type == "utons")
          ld1115_conf_data.utons = conf_data_type_split_val.toInt();
      }
    }
  }
}

int32_t HLK_LD1115::getTh1() {
  return ld1115_conf_data.th1;
}

int32_t HLK_LD1115::getTh2() {
  return ld1115_conf_data.th2;
}

int32_t HLK_LD1115::getThIn() {
  return ld1115_conf_data.th_in;
}

bool HLK_LD1115::getOutputMode() {
  return ld1115_conf_data.output_mode;
}

int32_t HLK_LD1115::getTons() {
  return ld1115_conf_data.tons;
}

uint16_t HLK_LD1115::getUtons() {
  return ld1115_conf_data.utons;
}

bool HLK_LD1115::saveAllSettings() {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    SS->println(ld1115_save_str);

    String save_suc = "";

    while (save_suc != ld1115_save_suc_str)
      save_suc = SS->readStringUntil('\n');

    return save_suc == ld1115_save_suc_str;
  }

#endif

  if (not is_soft) {

    String save_suc = "";

    HS->println(ld1115_save_str);

    while (save_suc != ld1115_save_suc_str)
      save_suc = HS->readStringUntil('\n');

    return save_suc == ld1115_save_suc_str;
  }
}

bool HLK_LD1115::setTh1(int32_t th1) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_th1_suc_str = "th1 is " + String(th1) + "\r";

    String set_th1_suc = "";

    SS->println("th1=" + String(th1));

    while (set_th1_suc != set_th1_suc_str)
      set_th1_suc = SS->readStringUntil('\n');

    return set_th1_suc == set_th1_suc_str;
  }

#endif

  if (not is_soft) {

    String set_th1_suc_str = "th1 is " + String(th1) + "\r";

    String set_th1_suc = "";

    HS->println("th1=" + String(th1));

    while (set_th1_suc != set_th1_suc_str)
      set_th1_suc = HS->readStringUntil('\n');

    return set_th1_suc == set_th1_suc_str;
  }
}

bool HLK_LD1115::setTh2(int32_t th2) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_th2_suc_str = "th2 is " + String(th2) + "\r";

    String set_th2_suc = "";

    SS->println("th2=" + String(th2));

    while (set_th2_suc != set_th2_suc_str)
      set_th2_suc = SS->readStringUntil('\n');

    return set_th2_suc == set_th2_suc_str;
  }

#endif

  if (not is_soft) {

    String set_th2_suc_str = "th2 is " + String(th2) + "\r";

    String set_th2_suc = "";

    HS->println("th2=" + String(th2));

    while (set_th2_suc != set_th2_suc_str)
      set_th2_suc = HS->readStringUntil('\n');

    return set_th2_suc == set_th2_suc_str;
  }
}

bool HLK_LD1115::setThIn(int32_t th_in) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_th_in_suc_str = "th_in is " + String(th_in) + "\r";

    String set_th_in_suc = "";

    SS->println("th_in=" + String(th_in));

    while (set_th_in_suc != set_th_in_suc_str)
      set_th_in_suc = SS->readStringUntil('\n');

    return set_th_in_suc == set_th_in_suc_str;
  }

#endif

  if (not is_soft) {

    String set_th_in_suc_str = "th_in is " + String(th_in) + "\r";

    String set_th_in_suc = "";

    HS->println("th_in=" + String(th_in));

    while (set_th_in_suc != set_th_in_suc_str)
      set_th_in_suc = HS->readStringUntil('\n');

    return set_th_in_suc == set_th_in_suc_str;
  }
}

bool HLK_LD1115::setOutputMode(bool output_mode) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_output_mode_suc_str = "output_mode is " + String(output_mode) + "\r";

    String set_output_mode_suc = "";

    SS->println("output_mode=" + String(output_mode));

    while (set_output_mode_suc != set_output_mode_suc_str)
      set_output_mode_suc = SS->readStringUntil('\n');

    return set_output_mode_suc == set_output_mode_suc_str;
  }

#endif

  if (not is_soft) {

    String set_output_mode_suc_str = "output_mode is " + String(output_mode) + "\r";

    String set_output_mode_suc = "";

    HS->println("output_mode=" + String(output_mode));

    while (set_output_mode_suc != set_output_mode_suc_str)
      set_output_mode_suc = HS->readStringUntil('\n');

    return set_output_mode_suc == set_output_mode_suc_str;
  }
}

bool HLK_LD1115::setTons(int32_t tons) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_tons_suc_str = "tons is " + String(tons) + "\r";

    String set_tons_suc = "";

    SS->println("tons=" + String(tons));

    while (set_tons_suc != set_tons_suc_str)
      set_tons_suc = SS->readStringUntil('\n');

    return set_tons_suc == set_tons_suc_str;
  }

#endif

  if (not is_soft) {

    String set_tons_suc_str = "tons is " + String(tons) + "\r";

    String set_tons_suc = "";

    HS->println("tons=" + String(tons));

    while (set_tons_suc != set_tons_suc_str)
      set_tons_suc = HS->readStringUntil('\n');

    return set_tons_suc == set_tons_suc_str;
  }
}

bool HLK_LD1115::setUtons(uint16_t utons) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_utons_suc_str = "utons is " + String(utons) + "\r";

    String set_utons_suc = "";

    SS->println("utons=" + String(utons));

    while (set_utons_suc != set_utons_suc_str)
      set_utons_suc = SS->readStringUntil('\n');

    return set_utons_suc == set_utons_suc_str;
  }

#endif

  if (not is_soft) {

    String set_utons_suc_str = "utons is " + String(utons) + "\r";

    String set_utons_suc = "";

    HS->println("utons=" + String(utons));

    while (set_utons_suc != set_utons_suc_str)
      set_utons_suc = HS->readStringUntil('\n');

    return set_utons_suc == set_utons_suc_str;
  }
}
