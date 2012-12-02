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
	GsSetVideoMode(320, 240, COMPILE_VMODE);
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
			
			if(newround == 1)	{
				while((pause + 240) > time_counter)	{
				};
				newround = 0;
			};

			GsSortCls(0,0,255);	

			if(player1_score == 10)	{
				GsPrintFont(5, 100, " Player 1 wins. Take that, Player 2.");
				player1_score = 0;
				player2_score = 0;
				newround = 1;
			}
			else if(player2_score == 10)	{
				GsPrintFont(5, 100, " Player 2 wins. Hah, Player 1 fails.");
				player1_score = 0;
				player2_score = 0;
				newround = 1;
			}
			else	{
				GsPrintFont(5, 100, " Take 10 paces and draw your weapons!");
			};

			GsPrintFont(5, 15, "   Rock, Paper, Scissors by Moonlit");
			GsPrintFont(5, 22, "  ----------------------------------");
			GsPrintFont(5, 45, " Choose your weapon:          Scores: ");
			GsPrintFont(5, 52, "---------------------        ---------");
			GsPrintFont(5, 60, "   SQUARE = Rock              P1: %d", player1_score);
			GsPrintFont(5, 70, "   CROSS  = Paper             P2: %d", player2_score);
			GsPrintFont(5, 80, "   CIRCLE = Scissors ");
						
			PSX_ReadPad(&pad1, &pad2);

			if(pad1 & PAD_SQUARE)	{
				//P1 ROCK
				weapon1 = 1;
			}
			else if(pad1 & PAD_CROSS)	{
				//P1 PAPER
				weapon1 = 2;
			}
			else if(pad1 & PAD_CIRCLE)	{
				//P1 SCISSORS
				weapon1 = 3;
			};
						
			if(pad2 & PAD_SQUARE)	{
				//P2 ROCK
				weapon2 = 1;
			}
			else if(pad2 & PAD_CROSS)	{
				//P2 PAPER
				weapon2 = 2;
			}
			else if(pad2 & PAD_CIRCLE)	{
				//P2 SCISSORS
				weapon2 = 3;
			};
		
			pause = time_counter;
			
			if(weapon1 > 0 && weapon2 > 0)	{
				if(weapon1 == 1) GsPrintFont(5, 130, " Player 1 chose rock...");;
				if(weapon1 == 2) GsPrintFont(5, 130, " Player 1 chose paper...");;
				if(weapon1 == 3) GsPrintFont(5, 130, " Player 1 chose scissors...");;
				if(weapon2 == 1) GsPrintFont(5, 140, " Player 2 chose rock...");;
				if(weapon2 == 2) GsPrintFont(5, 140, " Player 2 chose paper...");;
				if(weapon2 == 3) GsPrintFont(5, 140, " Player 2 chose scissors...");;

				
				// It's a draw.
				if(weapon1 == 1 && weapon2 == 1)	{
					GsPrintFont(5, 170, " Thick as two bricks.");
					GsPrintFont(5, 180, " Surely there's mortar life..?");
				};
				if(weapon1 == 2 && weapon2 == 2)	{
					GsPrintFont(5, 170, " Two sheets to the wind.");
					GsPrintFont(5, 180, " It's blowing up in here.");
				};
				if(weapon1 == 3 && weapon2 == 3)	{
					GsPrintFont(5, 170, " Neither of you are the ");
					GsPrintFont(5, 180, " sharpest in the drawer, are you?");
				};
				
				// Player 1 wins.
				if(weapon1 == 1 && weapon2 == 3)	{
					GsPrintFont(5, 160, " Careful Player 2... ");
					GsPrintFont(5, 170, " You'll ruin those scissors.");
					GsPrintFont(5, 180, " That's a point for Player 1.");
					player1_score++;
				};
				if(weapon1 == 2 && weapon2 == 1)	{
					GsPrintFont(5, 160, " Aw, gift wrapped rocks.");
					GsPrintFont(5, 170, " Really, Player 2.");
					GsPrintFont(5, 180, " You shouldn't have.");
					player1_score++;
				};
				if(weapon1 == 3 && weapon2 == 2)	{
					GsPrintFont(5, 160, " Player 2 gets the chop.");
					GsPrintFont(5, 170, " A ticker tape parade for Player 1.");
					GsPrintFont(5, 180, " What other use for shredded paper?");
					player1_score++;
				};

				// Player 2 wins.
				if(weapon2 == 1 && weapon1 == 3)	{
					GsPrintFont(5, 160, " Stab in the back for Player 1.");
					GsPrintFont(5, 170, " At least those blades");
					GsPrintFont(5, 180, " are safer now.");
					player2_score++;
				};
				if(weapon2 == 2 && weapon1 == 1)	{
					GsPrintFont(5, 160, " +1 for Player 2.");
					GsPrintFont(5, 170, " Player 1 gets stoned.");
					GsPrintFont(5, 180, " Too wrapped up in the game.");
					player2_score++;
				};
				if(weapon2 == 3 && weapon1 == 2)	{
					GsPrintFont(5, 160, " Player 1's all cut up.");
					GsPrintFont(5, 170, " It's twice as nice when ");
					GsPrintFont(5, 180, " the paper's sliced.");
					player2_score++;
				};
				
				newround = 1;
				weapon1 = 0;
				weapon2 = 0;
			};
			
					
			GsDrawList();
			while(GsIsDrawing());

			display_is_old=1;
		}
	}

	return 0;
}
