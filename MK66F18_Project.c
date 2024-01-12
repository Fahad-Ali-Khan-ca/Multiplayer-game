#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK66F18.h"
#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_uart.h"


#define BASE_SCORE 1000  // Base score if the reaction is instantaneous
#define NUM_ROUNDS 5



volatile uint32_t milliseconds = 0;

// Enumeration for game states
typedef enum {
    GAME_STATE_INIT,
    GAME_STATE_WAIT_START,
    GAME_STATE_DISPLAY_PATTERN,
    GAME_STATE_WAIT_REACTION,
    GAME_STATE_SCORE,
    GAME_STATE_GAME_OVER,
    GAME_STATE_SINGLE_PLAYER,
	GAME_STATE_MULTI_PLAYER
} game_state_t;

volatile game_state_t currentGameState = GAME_STATE_INIT;
volatile game_state_t GameState = GAME_STATE_INIT;
volatile uint32_t reactionStartTime = 0;
volatile bool isGameRunning = false;
volatile int scorePlayer1 = 0, scorePlayer2 = 0;
volatile uint32_t Reaction_time_Player1 = 0;
volatile uint32_t Reaction_time_Player2 = 0;
volatile int roundCount = 0;
volatile int BUTTON_PRESSED=0;

void SysTick_Handler(void) {
        milliseconds++;

}

void SysTick_Init(void) {
    SysTick_Config(SystemCoreClock / 1000U);
}

uint32_t GetCurrentTime(void) {
    return milliseconds;
}

void custom_delay(void) {
    __asm__(
        ".syntax unified\n"

        // PRNG initialization
        "mov r1, #1\n"            // Seed for PRNG
        "mov r2, #0\n"            // Loop counter

        // Simple PRNG loop
        "prng_loop:\n"
        "lsl r1, r1, #1\n"        // Shift left
        "eor r1, r1, r1, lsr #22\n" // XOR with shifted value
        "eor r1, r1, r1, lsr #17\n" // More XOR operations
        "eor r1, r1, r1, lsr #10\n" // And another one
        "add r2, r2, #1\n"        // Increment loop counter
        "cmp r2, #50\n"           // Check if 50 iterations are done
        "ble prng_loop\n"         // Repeat if not

        // Delay loop based on PRNG result
        "mov r3, r1\n"            // Move PRNG result to r3
        "delay_loop:\n"
        "subs r3, r3, #1\n"       // Decrement the delay counter
        "bne delay_loop\n"        // Loop until counter is zero

        ".syntax divided\n"
    );
}

void delay_ms(uint32_t milliseconds) {
    for (uint32_t i = 0; i < milliseconds * 5000; ++i) {
        __asm("NOP");
    }
}





void startGame(void) {
    PRINTF("Game started\n");
    isGameRunning = true;
    roundCount = 0;
    scorePlayer1 = 0;
    scorePlayer2 = 0;
    currentGameState = GAME_STATE_DISPLAY_PATTERN;
    GameState= GAME_STATE_MULTI_PLAYER;
}

// Function to start single-player mode
void startSinglePlayerGame(void) {
    PRINTF("Single-player game started\n");
    isGameRunning = true;
    roundCount = 0;
    scorePlayer1 = 0;// In single-player mode, only player 1's score is used
    currentGameState = GAME_STATE_DISPLAY_PATTERN;
    GameState= GAME_STATE_SINGLE_PLAYER;

}



void displayPattern(void) {
    // Turn off all LEDs first
    LED_RED_OFF();
    LED_GREEN_OFF();
    LED_BLUE_OFF();

    // Use the round count to determine which LED to turn on
    switch (roundCount % 3) {
        case 0:
            LED_RED_ON();
            break;
        case 1:
            LED_GREEN_ON();
            LED_RED_ON();
            break;
        case 2:
            LED_BLUE_ON();
            LED_GREEN_ON();
            break;
    }

    // Use your custom delay function here
    custom_delay();

    // Turn off all LEDs after the delay
    LED_RED_OFF();
    LED_GREEN_OFF();
    LED_BLUE_OFF();

    reactionStartTime = GetCurrentTime();
    currentGameState = GAME_STATE_WAIT_REACTION;
}


void endRound(void) {
    if (GameState == GAME_STATE_SINGLE_PLAYER) {
        PRINTF("\n Player 1 Score: %d\n", scorePlayer1);
        if (++roundCount >= NUM_ROUNDS) {
            currentGameState = GAME_STATE_GAME_OVER;
        } else {
            currentGameState = GAME_STATE_WAIT_START;
        }
    } else {
        PRINTF("\n Player 1 Score: %d, Player 2 Score: %d\n", scorePlayer1, scorePlayer2);
        if (++roundCount >= NUM_ROUNDS) {
            currentGameState = GAME_STATE_GAME_OVER;
        } else {
            currentGameState = GAME_STATE_WAIT_START;
        }
    }
}




void SW2_GPIOD_IRQHANDLER(void) {
    GPIO_PortClearInterruptFlags(GPIOD, 1U << 11U);

    if (GameState == GAME_STATE_SINGLE_PLAYER) {
        if (currentGameState == GAME_STATE_WAIT_REACTION) {
            uint32_t reactionTime = GetCurrentTime() - reactionStartTime;
            if (reactionTime < 1000) { // Check if the reaction time is less than 1 second
                scorePlayer1++;  // Increment score for successful reaction
                PRINTF("\n Reaction Time: %d ms - Successful!\n", reactionTime);
            } else {
                PRINTF("\n Reaction Time: %d ms - Too slow!\n", reactionTime);
            }
            endRound(); // End the round after Player 1 reacts
        }
    } else if (GameState == GAME_STATE_MULTI_PLAYER) {
        // Existing multi-player logic
        if (currentGameState == GAME_STATE_WAIT_REACTION) {
            scorePlayer1++;
            Reaction_time_Player1 = GetCurrentTime() - reactionStartTime;
            PRINTF("\n Player 1 pressed first:\n Reaction Time: %d", Reaction_time_Player1);
            endRound();
        }
    }
}


void SW3_GPIOA_IRQHANDLER(void) {
    GPIO_PortClearInterruptFlags(GPIOA, 1U << 10U);

    if (GameState == GAME_STATE_MULTI_PLAYER) {
        if (currentGameState == GAME_STATE_WAIT_REACTION) {
            scorePlayer2++;
            Reaction_time_Player2 = GetCurrentTime() - reactionStartTime;
            PRINTF("\n Player 2 pressed first: Reaction Time: %d \n", Reaction_time_Player2);
            endRound();
        }
    }
    // In single-player mode, SW3 (Player 2) input can be ignored or used for a different purpose
}


int main(void) {
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif
    SysTick_Init();
    disco_lights();
    PRINTF("Welcome: Press 1 for SinglePlayer, Press 2 for Multiplayer\n");
    char gamestate = GETCHAR();

    // Use the game state to determine which function to call
    if (gamestate == '1') {
        startSinglePlayerGame();
    } else if (gamestate == '2') {
        startGame();
    }

    while (1) {
        switch (currentGameState) {
            case GAME_STATE_WAIT_START:
                // Wait for a random time before starting the pattern
            	custom_delay();
                currentGameState = GAME_STATE_DISPLAY_PATTERN;
                break;
            case GAME_STATE_DISPLAY_PATTERN:
                displayPattern();
                break;
            case GAME_STATE_WAIT_REACTION:
                // Game is waiting for player reactions
                break;
            case GAME_STATE_GAME_OVER:
            	if(gamestate==GAME_STATE_MULTI_PLAYER){
                PRINTF("\n Game Over. Player 1 Total Score: %d, Player 2 Total Score: %d\n",
                        scorePlayer1, scorePlayer2);}
            	else{
                    PRINTF("\n Game Over. Player 1 Total Score: %d ", scorePlayer1);}

                while (1);  // Stop here or reset the game
                break;
            default:
                break;
    	}

        }

    return 0;
}


