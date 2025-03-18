/*
 * GPS.h
 *
 *  Created on: Mar 5, 2025
 *      Author: bugra
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_



void GPS_veri_al(uint8_t* GPSBuffer);
float gps_enlem_isle(uint8_t* buffer);
float gps_boylam_isle(uint8_t* buffer);
float gps_irtifa_isle(uint8_t* buffer);


#endif /* INC_GPS_H_ */
