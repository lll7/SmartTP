/* 
 * File:   bt.h
 * Author: LLL
 *
 * Created on 2 lipiec 2013, 20:06
 */

#ifndef BT_H
#define	BT_H

#ifdef	__cplusplus
extern "C" {
#endif

    void BTInit(void);
    void BTSendDataFFlash(const rom char * apString);
    void BTSendData(char * apString);
    void BTEmulateKeyboard(unsigned char u8Key);

#ifdef	__cplusplus
}
#endif

#endif	/* BT_H */

