#include <stdio.h>
#include <stdint.h>


#define TXE  0  // Bit 0: Transmit Data Register Empty
#define RXNE 1  // Bit 1: Read Data Register Not Empty


uint8_t UART_SR = 0x01; 
uint8_t UART_DR = 0x00; 

void check_transmitter_status() {
    if (UART_SR & (1 << TXE)) {
        printf("Virtual Hardware: Transmitter is EMPTY. Ready to send data!\n");
    } else {
        printf("Virtual Hardware: Transmitter is BUSY. Please wait...\n");
    }
}

void check_receiver_status() {
    if (UART_SR & (1 << RXNE)) {
        printf("Virtual Hardware: DATA RECEIVED! Ready to read from UART_DR.\n");
    } else {
        printf("Virtual Hardware: No data has arrived yet.\n");
    }
}

int main() {
    printf("--- Booting Virtual Microcontroller ---\n");
    check_transmitter_status();
    check_receiver_status();
    
    printf("\n--- Simulating an Incoming Message Packet ---\n");
    
    UART_DR = 'A'; 
    
    UART_SR |= (1 << RXNE); 
    
    check_receiver_status();
    
    if (UART_SR & (1 << RXNE)) {
        printf("CPU Read: Successfully retrieved data: '%c'\n", UART_DR);
        
        UART_SR &= ~(1 << RXNE);
    }
    
    printf("\n--- Post-Read Cleanup Check ---\n");
    check_receiver_status();

    return 0;
} 
