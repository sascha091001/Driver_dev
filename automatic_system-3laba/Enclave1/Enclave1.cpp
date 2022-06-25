#include "Enclave1_t.h"
#include "sgx_trts.h"
#include <string.h>

//�������� ������, ������� ���������� ��������, � ���� �������
const char table[5][31] = { "000000000000000000000000000000",
                            "111111111111111111111111111111",
                            "222222222222222222222222222222",
                            "333333333333333333333333333333",
                            "444444444444444444444444444444" };

//������� ������� � ���� �������
void getElementByIndex(char* buffer, size_t len, size_t index) {

    if (index >= 0 && index < 5) {
        const char* data_ptr = table[index];
        memcpy(buffer, data_ptr, strlen(data_ptr + 1));
    }
    else {
        //������� ������� ������, ���� ������ ������� � ������� �� �������
        memset(buffer, 0, strlen(table[0]));
    }
    return;
}