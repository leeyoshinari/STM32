#ifndef __PROTOCOL_H
#define __PROTOCOL_H
#include <stdint.h>

//��������ѧϰָ�����
uint16_t IR_Learn_Pack(uint8_t *data, uint8_t index);

//�������뷢��ָ�����
uint16_t IR_Send_Pack(uint8_t *data, uint8_t index);
#endif
