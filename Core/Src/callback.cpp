//
// Created by zbxboris on 10/3/2025.
//

#include "main.h"

extern uint8_t rx_data[8];
extern CAN_RxHeaderTypeDef rx_header;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    if (hcan->Instance == CAN1) {
        HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0, &rx_header, rx_data);
        if (rx_header.StdId == 0x201) {
            // Motor.canRxMsgCallback(rx_data);
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
