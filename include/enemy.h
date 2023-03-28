
typedef struct {
    int x;
    int y;
    int width;
    int speed;
} Enemy;

Enemy init_enemy(int x);
void update_enemy(Enemy* enemy);