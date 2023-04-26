#define MENU_STATE_MAIN 0
#define MENU_STATE_SETTING 1

void init_menu(double* music_volume,double* effect_volume,double* new_music_volume, MLV_Music *music);
void draw_button(int x, int y, int w, int h, char *text, MLV_Font *font, int mouse_x, int mouse_y);