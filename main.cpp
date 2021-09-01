#include <Windows.h>
#include <cstdint>
#include <iostream>
#include "rzctl.h"
#include <Psapi.h>
#include <random>


#define gundetect 1


int rand_range(int min, int max) {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(min, max);
	return distrib(gen);
}


// AR: 11
// SMG: 9
// PLASMA and pistol: 4


int main() {
	HDC GameDC = NULL;
	HWND hWndGame = NULL;
	int distance = 0;
	int guns[4] = { 0,4,9,11 };
	int pos = 0;

	COLORREF AR_1;
	COLORREF AR_2;
	COLORREF SMG_1;
	COLORREF SMG_2;
	COLORREF PLAS_1;
	COLORREF PLAS_2;
	COLORREF PIS_1;
	COLORREF PIS_2;



	if (!rzctl::init()) {
		printf("Failed to initalize rzctl");
		return 1;
	}
	


	printf("Press CTRL + C to exit\n");

	hWndGame = FindWindowA(0, "PortalWars  ");
	GameDC = GetDC(hWndGame);

	
	while (true) {
		



		if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0) {
#if gundetect

			
			AR_1 = GetPixel(GameDC, 2733, 117);
			AR_2 = GetPixel(GameDC, 2743, 115);
			if (GetRValue(AR_1) == 126 && GetRValue(AR_2) == 126 && GetGValue(AR_1) == 233 && GetGValue(AR_2) == 233 && GetBValue(AR_1) == 255 && GetBValue(AR_2) == 255) {

				if ((GetRValue(GetPixel(GameDC, 2694, 97)) != 255) && (GetGValue(GetPixel(GameDC, 2694, 97)) != 255) && (GetGValue(GetPixel(GameDC, 2638, 93)) != 255)) {
					//printf("OUT OF AMMO!!!!!!\n");
					Sleep(150);
					continue;
				}

				distance = 11;
				//printf("AR\n");
			}
			else {
				SMG_1 = GetPixel(GameDC, 2759, 115);
				SMG_2 = GetPixel(GameDC, 2736, 117);
				if (GetRValue(SMG_1) == 126 && GetRValue(SMG_2) == 126 && GetGValue(SMG_1) == 233 && GetGValue(SMG_2) == 233 && GetBValue(SMG_1) == 255 && GetBValue(SMG_2) == 255 && (GetBValue(GetPixel(GameDC, 2694, 97)) != 255 ) ) {
					
					if ((GetRValue(GetPixel(GameDC, 2694, 97)) != 255) && (GetGValue(GetPixel(GameDC, 2694, 97)) != 255) && (GetGValue(GetPixel(GameDC, 2638, 93)) != 255)) {
						//printf("OUT OF AMMO!!!!!!\n");
						Sleep(150);
						continue;
					}

					distance = 9;
					//printf("smg\n");
				}
				else {
					PLAS_1 = GetPixel(GameDC, 2780, 121);
					PLAS_2 = GetPixel(GameDC, 2785, 117);
					if (GetRValue(PLAS_1) == 126 && GetRValue(PLAS_2) == 126 && GetGValue(PLAS_1) == 233 && GetGValue(PLAS_2) == 233 && GetBValue(PLAS_1) == 255 && GetBValue(PLAS_2) == 255) {
						
						if ((GetRValue(GetPixel(GameDC, 2694, 97)) == 255) && (GetGValue(GetPixel(GameDC, 2694, 97)) == 64)) {
							//printf("OUT OF AMMO!!!!!!\n");
							Sleep(150);
							continue;
						}

						//printf("plasma\n");
						distance = 4;
					}
					else {
						PIS_1 = GetPixel(GameDC, 2745, 117);
						PIS_2 = GetPixel(GameDC, 2758, 110);
						if (GetRValue(PIS_1) == 126 && GetRValue(PIS_2) == 126 && GetGValue(PIS_1) == 233 && GetGValue(PIS_2) == 233 && GetBValue(PIS_1) == 255 && GetBValue(PIS_2) == 255) {

							if ((GetRValue(GetPixel(GameDC, 2694, 97)) != 255) && (GetGValue(GetPixel(GameDC, 2694, 97)) != 255) && (GetGValue(GetPixel(GameDC, 2638, 93)) != 255)) {
								//printf("OUT OF AMMO!!!!!!\n");
								Sleep(150);
								continue;
							}

							//printf("pistol\n");
							distance = 4;
						}
						else {
							//printf("Nothing detected :(, AR_1: %06X AR_2: %06X SMG_1: %06X SMG_2: %06X PLAS_1: %06X PLAS_2: %06X PIS_1: %06X PIS_2: %06X\n", AR_1, AR_2, SMG_1, SMG_2, PLAS_1, PLAS_2, PIS_1, PIS_2);
							distance = 0;
						}
					}
				}
			}
#endif
			rzctl::mouse_move(0, distance);
		}




		if ((GetKeyState(VK_DOWN) & 0x8000) != 0) {
			distance = 0;
			printf("%d\n", distance);
			Sleep(100);

		}

#if gundetect != 1
		if ((GetKeyState(VK_RIGHT) & 0x8000) != 0) {
			distance = 9;
			printf("%d\n", distance);
			Sleep(100);

		}


		if ((GetKeyState(VK_LEFT) & 0x8000) != 0) {
			distance = 4;
			printf("%d\n", distance);
			Sleep(100);

		}


		if ((GetKeyState(VK_UP) & 0x8000) != 0) {
			distance = 11;
			printf("%d\n", distance);
			Sleep(100);

		}
#endif


		Sleep(rand_range(25, 50));
	}

	return 0;
}

