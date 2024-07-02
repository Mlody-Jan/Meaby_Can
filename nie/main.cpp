#include <iostream>
#include <windows.h>
#include "PCANBasic.h"

int main() {
    TPCANStatus status;             //status error: PCAN_ERROR_OK
    TPCANMsg canMessage;            //ramka z kana warotści, długości etc.
    TPCANTimestamp canTimestamp;    //to jest do wskaźnika (tego co sika XDDD) do can read by miał czas ramek do odebrania czy coś takiego

    //ustawianie PCAN-USB kanał(1) i prędkość(250kbit/s)
    status = CAN_Initialize(PCAN_USBBUS1, PCAN_BAUD_250K);
    if (status != PCAN_ERROR_OK) {                                                      //if patrzący czy PCAN działa
        std::cerr << "Nie można zainicjalizować PCAN-USB: " << status << std::endl;
        return -1;
    }

    std::cout << "Urządzenie PCAN-USB zainicjalizowane poprawnie." << std::endl;        //info że działa

    // Główna pętla odbierania
    while (true) {
        while ((status = CAN_Read(PCAN_USBBUS1, &canMessage, &canTimestamp)) == PCAN_ERROR_OK) {
            std::cout << "Odebrano ramke: ID=0x" << std::hex << canMessage.ID<< ", Typ=" << ((canMessage.MSGTYPE & PCAN_MESSAGE_EXTENDED) ? "Rozszerzony" : "Standard") << ", Dlugosc=" << std::dec << (int)canMessage.LEN<< ", Dane=0x";

            for (int i = 0; i < canMessage.LEN; i++)
                std::cout << std::hex << (int)canMessage.DATA[i] << " ";

            std::cout << std::endl;

            // Przykład przypisywania wartości do zmiennych
            if (canMessage.ID == 0x18FFE2EF && canMessage.LEN >= 8) {
                int var1 = canMessage.DATA[0];
                int var2 = canMessage.DATA[1];
                int var3 = canMessage.DATA[2];
                int var4 = canMessage.DATA[3];
                int var5 = canMessage.DATA[4];
                int var6 = canMessage.DATA[5];
                int var7 = canMessage.DATA[6];
                int var8 = canMessage.DATA[7];

                std::cout << "Zmienne przypisane: var1=" << var1 << ", var2=" << var2 << ", var3=" << var3 <<", var4=" << var4 <<", var5=" << var5 <<", var6=" << var6 <<", var7=" << var7 <<", var8=" << var8 << std::endl;
            }
        }

        if (status != PCAN_ERROR_QRCVEMPTY) {
            std::cerr << "Błąd odczytu z PCAN-USB: " << status << std::endl;
            break;
        }

        Sleep(99);  // Odczekanie 99 ms
    }

    // Wyłączenie urządzenia PCAN-USB
    CAN_Uninitialize(PCAN_USBBUS1);
    std::cout << "Urządzenie PCAN-USB wyłączone." << std::endl;

    return 0;
}
