//
// Created by zbxboris on 10/3/2025.
//
#include "main.h"
#include "can.h"
#include "../Inc/motor.h"
#include "tim.h"

CAN_RxHeaderTypeDef rx_header;
CAN_TxHeaderTypeDef tx_header = {
    .StdId = 0x200,
    .ExtId = 0,
    .IDE = CAN_ID_STD,
    .RTR = CAN_RTR_DATA,
    .DLC = 8,
    .TransmitGlobalTime = DISABLE
};


uint8_t rx_data[8];
uint8_t tx_data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD6};
uint32_t count = 0;

M3508_Motor Motor(19.2);

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    if (hcan->Instance == CAN1) {
        HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rx_header, rx_data);
        if (rx_header.StdId == 0x206) {
            Motor.canRxMsgCallback(rx_data);
        }
    }
}

uint32_t ptr;
HAL_StatusTypeDef status;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == htim5.Instance) {
        status = HAL_CAN_AddTxMessage(&hcan1, &tx_header, tx_data, &ptr);
    }
    count++;
}

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan) {
};

void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan) {
};

void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan) {
};
