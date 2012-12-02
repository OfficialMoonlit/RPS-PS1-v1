#include <psx.h>
#include <stdio.h>

unsigned int prim_list[0x4000];
unsigned short pad1;
unsigned short pad2;

volatile int display_is_old = 1;
volatile int time_counter = 0;
volatile int button_counter = 0;
int  dbuf=0;

void prog_vblank_handler() {
	display_is_old = 1;
	time_counter++;
}

int main() {
	PSX_Init();
	GsInit();
	GsSetList(prim_list);
	GsClearMem();
	GsSetVideoMode(320, 240, EXAMPLES_VMODE);
	GsLoadFont(768, 0, 768, 256);
	SetVBlankHandler(prog_vblank_handler);
	volatile int player1_score = 0;
	volatile int player2_score = 0;
	volatile int weapon1 = 0;
	volatile int weapon2 = 0;
	volatile int pause = 0;
	volatile int newround = 0;
	
	while(1) {
		if(display_is_old)	{
			dbuf=!dbuf;
			GsSetDispEnvSimple(0, dbuf ? 0 : 256);
			GsSetDrawEnvSimple(0, dbuf ? 256 : 0, 320, 240);
			
			//if(newround == 1)	{
				newround = 0;
			//	while(time_counter <= (pause + 180)){
					
			//	};
			//};

			GsSortCls(0,0,255);
			GsDrawList();
			while(GsIsDrawing());

			GsPrintFont(5, 5, "   Rock, Paper, Scissors by Moonlit");
			GsPrintFont(5, 12, "  ----------------------------------");
			
			GsPrintFont(5, 25, " Choose your weapon:          Scores: ");
			GsPrintFont(5, 32, "---------------------        ---------");
			GsPrintFont(5, 40, "   SQUARE = Rock              P1: %d", player1_score);
			GsPrintFont(5, 50, "   CROSS  = Paper             P2: %d", player2_score);
			GsPrintFont(5, 60, "   CIRCLE = Scissors ");
			
			GsPrintFont(5, 80, " Take 10 paces and draw your weapons!");
			
			
			if(weapon1 == 0 || weapon2 == 0)	{
				
				PSX_ReadPad(&pad1, &pad2);
				
				if(pad1 & PAD_SQUARE)	{
					//GsPrintFont(5, 120, "P1 ROCK");
					weapon1 = 1;
				}
				else if(pad1 & PAD_CROSS)	{
					//GsPrintFont(5, 120, "P1 PAPER");
					weapon1 = 2;
				}
				else if(pad1 & PAD_CIRCLE)	{
					//GsPrintFont(5, 120, "P1 SCISSORS");
					weapon1 = 3;
				};
							
				if(pad2 & PAD_SQUARE)	{
					//GsPrintFont(5, 130, "P2 ROCK");
					weapon2 = 1;
				}
				else if(pad2 & PAD_CROSS)	{
					//GsPrintFont(5, 130, "P2 PAPER");
					weapon2 = 2;
				}
				else if(pad2 & PAD_CIRCLE)	{
					//GsPrintFont(5, 130, "P2 SCISSORS");
					weapon2 = 3;
				};
			}
			else {
				
				pause = time_counter;
				
				if(weapon1 == 1) GsPrintFont(5, 120, " Player 1 chose rock...");;
				if(weapon1 == 2) GsPrintFont(5, 120, " Player 1 chose paper...");;
				if(weapon1 == 3) GsPrintFont(5, 120, " Player 1 chose scissors...");;
				if(weapon2 == 1) GsPrintFont(5, 130, " Player 2 chose rock...");;
				if(weapon2 == 2) GsPrintFont(5, 130, " Player 2 chose paper...");;
				if(weapon2 == 3) GsPrintFont(5, 130, " Player 2 chose scissors...");;

				if(weapon1 == 1 && weapon2 == 1)	{
				GsPrintFont(5, 150, " Thick as two bricks.");
				GsPrintFont(5, 160, " Surely there's so much mortar life..?");
				};
				if(weapon1 == 2 && weapon2 == 2)	{
				GsPrintFont(5, 150, " Two sheets to the wind.");
				GsPrintFont(5, 160, " Paper cuts for all.");
				};
				if(weapon1 == 3 && weapon2 == 3)	{
				GsPrintFont(5, 150, " Neither of you are the sharpest in the drawer,");
				GsPrintFont(5, 160, " are you?");
				};

				
				newround = 1;				
			};
					
			GsPrintFont(5, 180, " TEST1");
			while(pause <= (time_counter + 180)){};
			GsDrawList();
			while(GsIsDrawing());
			GsPrintFont(5, 190, " TEST2");
			//newround = 0;
			display_is_old=1;
			GsPrintFont(5, 200, " TEST3");
		}
	}

	return 0;
}
