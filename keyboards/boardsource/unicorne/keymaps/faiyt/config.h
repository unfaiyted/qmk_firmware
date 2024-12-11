#define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define CUSTOM_QUIT_KEY_DELAY 270
#define CUSTOM_POWER_KEY_DELAY 800
#define TMUX(kc) tmux_key(kc)


#define ZELDA_TREASURE \
    Q__NOTE(_A4), \
    Q__NOTE(_A4 ), \
    Q__NOTE(_AS4), \
    Q__NOTE(_B4), \
    HD_NOTE(_C5), \
    Q__NOTE(_B4 ), \
    HD_NOTE(_C5 ), \

#define DISNEY_SONG \
    H__NOTE(_G3 ),  \
    H__NOTE(_G4 ),  \
    H__NOTE(_F4 ),  \
    H__NOTE(_E4 ),  \
    H__NOTE(_CS4),  \
    H__NOTE(_D4 ),  \
    W__NOTE(_A4 ),  \
    H__NOTE(_B3 ),  \
    H__NOTE(_B4 ),  \
    H__NOTE(_A4 ),  \
    H__NOTE(_G4 ),  \
    H__NOTE(_FS4),  \
    H__NOTE(_G4 ),  \
    W__NOTE(_C5 ),  \
    H__NOTE(_D5 ),  \
    H__NOTE(_C5 ),  \
    H__NOTE(_B4 ),  \
    H__NOTE(_A4 ),  \
    H__NOTE(_G4 ),  \
    H__NOTE(_F4 ),  \
    H__NOTE(_E4 ),  \
    H__NOTE(_D4 ),  \
    W__NOTE(_A4 ),  \
    W__NOTE(_B3 ),  \
    W__NOTE(_C4 ),


#undef STARTUP_SONG
#define STARTUP_SONG SONG(DISNEY_SONG)

#define MIDI_BASIC
