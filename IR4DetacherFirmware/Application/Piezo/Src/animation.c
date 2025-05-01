#include "animation.h"


static void stop_and_reset(struct animation_params_mutable *m) // m for mutable!
{
    m->repeats_remaining     = 0;
    m->time_until_next_frame = 0;
    m->current_frame         = ANIMATION_END;
}


uint8_t animation_next_frame(struct animation_params_mutable *m, // m for mutable!
                             uint16_t time_since_previously_called,
                             enum animation_command command)
{
    // decrement, saturating at 0
    const uint16_t decremented_time_until_next_frame = m->time_until_next_frame > time_since_previously_called ?
                                                       m->time_until_next_frame - time_since_previously_called : 0;


    // Perform some sanity checks here in case the caller (incorrectly and 
    // dangerously) switched animations in the middle of a currently running 
    // animation without first doing an ANIM_CMD_STOP_AND_RESET.  Otherwise, if 
    // the new animation has fewer repeats or shorter time per frame, it might 
    // be distorted.  Or heaven forbid, if it has fewer frames, we might be 
    // accessing elements off the end of an array of frames!  Effectively, this 
    // code inserts a "silent" ANIM_CMD_STOP_AND_RESET on behalf of the caller.
    if ((m->c->num_repeats     < m->repeats_remaining)     ||
       (m->c->time_per_frame  < m->time_until_next_frame) ||
       (m->c->max_frame_index < m->current_frame))
    {
        stop_and_reset(m);
    }

    if (ANIM_CMD_STOP_AND_RESET == command)
    {
        // reset these values for the next time we decide to play this animation
        stop_and_reset(m);

        return ANIMATION_END;
    }
    else if (ANIM_CMD_START_OR_CONTINUE == command)
    {
        // if it had previously ended or stopped (which is the only reason m->time_until_next_frame would be 0)
        if (0 == m->time_until_next_frame)
        {
            // The values of m->repeats_remaining and m->current_frame would 
            // already have been reset to the appropriate values, either by the 
            // .data section initialization at boot, or by the last time this  
            // function ended or stopped the animation.  However, check the 
            // mutable values anyway, in case the caller decided to override 
            // them for whatever reason.
            m->repeats_remaining     = ((m->c->num_repeats <= m->repeats_remaining) || (0 == m->repeats_remaining)) ?
                                         m->c->num_repeats : m->repeats_remaining;

            m->time_until_next_frame = m->c->time_per_frame;

            m->current_frame         = (ANIMATION_END == m->current_frame) ? 0 : m->current_frame;

            return m->current_frame;
        }
    }
    else // i.e. ANIM_CMD_CONTINUE_UNTIL_END
    {
        if ((0 == m->time_until_next_frame) || (ANIMATION_END == m->current_frame))
        {
            return ANIMATION_END;
        }
    }

    // if the time remaining for this frame JUST transitioned to 0
    if ((0 == decremented_time_until_next_frame) && (0 < m->time_until_next_frame))
    {
        if (m->c->max_frame_index > m->current_frame)
        {
            // if there are more frames in the animation, increment to the next frame
            m->current_frame++;
        }
        else
        {
            // if there are no more frames, then wrap back to the first frame
            m->current_frame = 0;

            // if this animation isn't on infinite repeat
            if (ANIMATION_INFINITE_REPEATS != m->repeats_remaining)
            {
                if (0 < m->repeats_remaining)
                {
                    // and if there are repeats remaining, decrement the number of repeats available
                    m->repeats_remaining--;
                }
                else
                {
                    // but if there are no repeats remaining, reset the entire 
                    // animation (note that m->current_frame was already reset 
                    // to 0)
                    m->repeats_remaining     = m->c->num_repeats;

                    // reset this too, and also note that we use m->time_until_next_frame == 0
                    // as a proxy earlier in this function to determine that the animation had
                    // previously ended or been stopped
                    m->time_until_next_frame = 0;

                    m->current_frame         = ANIMATION_END;

                    return ANIMATION_END;
                }
            }
        }

        // the time had previously decremented all the way to 0, so we need to reset this up to max
        m->time_until_next_frame = m->c->time_per_frame;
    }
    else
    {
        m->time_until_next_frame = decremented_time_until_next_frame;
    }

    return m->current_frame;
}

