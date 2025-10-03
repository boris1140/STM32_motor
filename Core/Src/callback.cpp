//
// Created by zbxboris on 10/3/2025.
//
#include "main.c"

/*
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    if (hcan->Instance == CAN1) {
        HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&rx_header,rx_data);
        if (rx_header.StdId == 0x201) {
            Motor.canRxMsgCallback(rx_data);
        }
    }
}
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == htim5.Instance) {
        HAL_CAN_AddTxMessage(&hcan1, &tx_header, tx_data,CAN_FilterFIFO0);
    }
}
