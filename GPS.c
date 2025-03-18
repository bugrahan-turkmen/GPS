/*
 * GPS.c
 *
 *  Created on: Mar 5, 2025
 *      Author: bugrahan
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>



extern volatile float gps_irtifa;
extern volatile float enlem;
extern volatile float boylam;

float gps_enlem_isle(uint8_t* buffer) {
	int index = 0;
	char dumb[20];
	float veri1;
	float veri2;
	for (int i = 0; i < 2; i++) {
		dumb[index] = (char)buffer[i];
		index++;
		}
	dumb[index] = '\0';
	veri1 = atof(dumb);
	index=0;

	for (int i = 0; i < 8; i++) {
			dumb[index] = (char)buffer[i+2];
			index++;
			}
		dumb[index] = '\0';
		veri2 = atof(dumb)/60;
		return (veri1+veri2);
}
float gps_boylam_isle(uint8_t* buffer) {
	int index = 0;
	char dumb[20];
	float veri1;
	float veri2;
	for (int i = 0; i < 3; i++) {
		dumb[index] = (char)buffer[i];
		index++;
		}
	dumb[index] = '\0';
	veri1 = atof(dumb);
	index=0;

	for (int i = 0; i < 8; i++) {
			dumb[index] = (char)buffer[i+3];
			index++;
			}
		dumb[index] = '\0';
		veri2 = atof(dumb)/60;
		return (veri1+veri2);
}
float gps_irtifa_isle(uint8_t* buffer) {
	int index = 0;
	char dumb[20];
	for (int i = 0; i < 10; i++) {
		dumb[index] = (char)buffer[i];
		index++;
		}
	dumb[index] = '\0';
		return atof(dumb);
}

static uint8_t GPSValue[80];
void GPS_veri_al(uint8_t* GPSBuffer){
	uint8_t veri1[12];
	uint8_t veri2[12];
	uint8_t veri3[12];


	int flag=0;

	 for(int i=0;i<400;i++){
    if(GPSBuffer[i]=='$' && GPSBuffer[i+4]=='G' && GPSBuffer[i+5]=='A'){
    	if(i>325) return;
    	for(int j=0;j<80;j++){
    		GPSValue[j] = GPSBuffer[i+j];
    		if(GPSBuffer[i+j+1] == '$') break;
   	 	 	 }
    	break;
    	 }
	 }

	 int cnt=0;
	 int EBB;	//Enlem baslangic Bit
	 int BBB;	//Boylam baslangic bit
	 int IBB;	//GPS irtifa baslangic bit
	 for(int i=0;i<80;i++){
		 if(GPSValue[i] == ',') cnt++;

		if(cnt == 2 && flag==0){
			EBB = (i+1);
			int j=0;
			while(GPSValue[EBB+j] != ','){
				if(j==12) break;
				veri1[j] = GPSValue[EBB+j];
				j++;

			}
			enlem = gps_enlem_isle(veri1);
			flag=1;
		}
		if(cnt == 4 && flag==1){
			BBB=i+1;
			int k=0;
			while(GPSValue[BBB+k] != ','){
				if(k==12) break;
				veri2[k] = GPSValue[BBB+k];
				k++;
			}

			boylam = gps_boylam_isle(veri2);
			flag=2;
		}
		if(cnt == 9 && flag==2){
			IBB = i+1;
			int l=0;
			while(GPSValue[IBB+l] != ','){
				if(l==12) break;
				veri3[l] = GPSValue[IBB+l];
				l++;

			}
			gps_irtifa = gps_irtifa_isle(veri3);
			flag=3;
		}
	 }

}
