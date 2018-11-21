#include "../../protocol/headers/definitions.h"

unsigned short crc16(const unsigned char* data_p, unsigned char length);
int check_integrity(MESSAGE * message);