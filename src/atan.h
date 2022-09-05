#ifndef ATAN_H
#define ATAN_H

const uint16_t CORDICINTTABLE16[] = { 0x2000, 0x12E4, 0x09FB, 0x0511, 0x028B, 0x0146, 0x00A3, 0x0051, 0x0029, 0x0014, 0x000A, 0x0005, 0x0003, 0x0001, 0x0001 };

int16_t atan2Int16(int16_t y, int16_t x)
{
    int16_t k, tx, z = 0, fl = 0;

    if (x < 0) {
        fl = ((y>0) ? +1 : -1);
        x = -x;
        y = -y;
    }

    for (k = 0; k < (16 - 1); k++) {
        tx = x;
        if (y <= 0) {
            x -= (y >> k);
            y += (tx >> k);
            z -= CORDICINTTABLE16[k];
        } else {
            x += (y >> k);
            y -= (tx >> k);
            z += CORDICINTTABLE16[k];
        }
    }

    if (fl != 0) {
        z += fl * (1 << (16 - 1));
    }

    return z;
}

#endif
