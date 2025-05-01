// This module iterates with configurable timing and repetitions through 
// elements of an array, each element representing one "frame" of "animation."  
// You can animate anything: for example, a sequence of RGB LED patterns, or a 
// sequence of piezo frequencies, etc.  This module operates on array indices, 
// but doesn't ever actually come in contact with the array itself, so the 
// array can be of any type.



#ifndef _ALREADY_SEEN_ANIMATION_H_
#define _ALREADY_SEEN_ANIMATION_H_



#include <stdint.h>



// special sentinel value for num_repeats and repeats_remaining
#define ANIMATION_INFINITE_REPEATS UINT16_MAX

// special sentinel value returned by animation_next_frame() to indicate the 
// completion of the animation
#define ANIMATION_END UINT8_MAX


// Intended to be const to save RAM.  Can be shared by multiple instances of 
// struct animation_mutable_params to also save FLASH.
struct animation_params_const
{
    uint16_t num_repeats; // Set to ANIMATION_INFINITE_REPEATS for infinite repeats.
    uint16_t time_per_frame; // Units must match that of time_since_previously_called.
    uint8_t  max_frame_index; // Presumably there's an array of frames, and this is the last element's index (number of elements - 1).
};


// Mutable data in RAM.
struct animation_params_mutable
{
    const struct animation_params_const* c; // Pointer to constant data (c for const!).  Initialize to point to an appropriately initialized struct.
    uint16_t repeats_remaining;  // typically initialize to 0
    uint16_t time_until_next_frame; // Units must match that of time_since_previously_called.  Initialize to 0.
    uint8_t  current_frame; // Likely an index into an array of frames.  Typically initialize to 0.
};


enum animation_command
{
    ANIM_CMD_STOP_AND_RESET,    // Useful to stop an animation that has infinite repeats.
    ANIM_CMD_START_OR_CONTINUE, // Starts from beginning if previously stopped/reset/ended, or where it left off otherwise.
    ANIM_CMD_CONTINUE_UNTIL_END // Continues where it left off, and stops when it reaches the end.
};


// Returns the number (likely an index into an array) of the desired frame of 
// the animation.  Returns ANIMATION_END if the animation is done, with no more 
// repeats remaining; you can then decide to either stop calling this function, 
// or if you must continue calling it, call it with enum animation_command set 
// to ANIM_CMD_STOP_AND_RESET, or if it's not an animation with infinite 
// repeats, you can also call it with ANIM_CMD_CONTINUE_UNTIL_END and the 
// animation will remain done.
uint8_t animation_next_frame(struct animation_params_mutable*,
                             uint16_t time_since_previously_called, // in whatever units you want
                             enum animation_command);



#endif // _ALREADY_SEEN_ANIMATION_H_

