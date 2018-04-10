/* Author: Romain "Artefact2" Dalmaso <artefact2@gmail.com> */
/* Contributor: Dan Spencer <dan@atomicpotato.net> */
/* Contributor: Peter "Projectitis" Vullings <peter@projectitis.com> */

/* This program is free software. It comes without any warranty, to the
 * extent permitted by applicable law. You can redistribute it and/or
 * modify it under the terms of the Do What The Fuck You Want To Public
 * License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
 
/**
 * Teensy microprocessor board support by Peter "Projectitis" Vullings.
 **/

#ifndef __has_xm_t3_h_
#define __has_xm_t3_h_

#include <Arduino.h>
extern "C" {
	#include "xm.h"
}

// Teensy 3.1 and 3.2 have only 1 DAC pin and will support mono output only
#if defined(__MK20DX128__) || defined(__MK20DX128__)
	#define XM_PIN_L		A14
	#define XM_SAMPLE_RATE	24000

// teensy 3.5 and 3.6 have 2 DAC pins and will support stereo output
#elif defined(__MK64FX512__) || defined(__MK66FX1M0__)
	#define XM_STEREO		1
	#define XM_PIN_L		A21
	#define XM_PIN_R		A22
	#define XM_SAMPLE_RATE	48000

#endif

/**
 * Initialise the mod player
 * Still need to call start after this to start actual playback.
 * @param	moddata		The mod data as a libxmized format (non-delta coded)
 **/
void xm_player_init( const char* moddata );

/**
 * Free the mod player (destructor equivalent)
 **/
void xm_player_exit( void );

/**
 * Start or unpause the player
 * @param	frombeginning		If true, will start again from the
 *								beginning. If false, will continue
 *								from last stop()
 */
void xm_player_start( bool frombeginning = false );

/**
 * Stop or pause the player and discontinue audio output
 **/
void xm_player_stop( void );

/**
 * Called during the update loop to step the player. This is typically done
 * even while the player is stopped, though it is safe not to call update
 * if you know the player is stopped.
 */
void xm_player_update( void );

/**
 * Jump to a specific location in the file.
 *
 * This is intended to change music mid-game depending on what is happening.
 * Recommended to have un-reachable parts of the song that the player can
 * jump to for different areas of the game.
 * 
 * @param	location	Location to jump to
 * @param	wait		If true will wait for the current pattern to end
 *						first before jumping, otherwise will jump immediately
 */
void xm_player_jump( uint8_t location, bool wait = true );

#endif