#include "Enemy.h"

Enemy::Enemy(){
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT*0.6;
	rect_.w = WIDTH_ENEMY;
	rect_.h = HEIGHT_ENEMY;
	x_val_ = 0;
	y_val_ = 0;
}

Enemy::~Enemy(){
	if(p_shoot_list_.size() > 0){
		for(int i = 0; i < p_shoot_list_.size(); i++){
			Shoot* p_shoot = p_shoot_list_.at(i);
			if(p_shoot != NULL){
				delete p_shoot;
				p_shoot = NULL;
			}
		}
		p_shoot_list_.clear();
	}
}

void Enemy::ActionEnemy(Shoot* p_shoot){
	if(p_shoot){
		bool setImg = p_shoot->LoadImg(g_name_bullet);
		if(setImg){
			p_shoot->set_is_move(true);
			p_shoot->setWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_shoot->set_type(Shoot::SPHERE);
			p_shoot->SetRect(rect_.x, rect_.y + rect_.h*0.5);
			p_shoot->set_x_val(SPEED_SHOOT_ENEMIES);
			p_shoot_list_.push_back(p_shoot);
		}
	}
}

void Enemy::ShootEnemy(SDL_Surface* des, const int& x_limit, const int& y_limit){
	for(int i = 0; i < p_shoot_list_.size(); i++){
		Shoot* p_shoot = p_shoot_list_.at(i);
		if(p_shoot){
			if(p_shoot->get_is_move()){
				p_shoot->Show(des);
				p_shoot->handleMoveRightToLeft();
			}
			else{
				p_shoot->set_is_move(true);
				p_shoot->SetRect(rect_.x, rect_.y + rect_.h*0.5);
			}
		}
	}
}

void Enemy::handleMove(const int& x_border, const int& y_border){
	rect_.x -= x_val_;
	if(rect_.x <= 0){
		rect_.x = SCREEN_WIDTH;
		int random_y = rand() % 800;
		if(random_y > SCREEN_HEIGHT - 150){
			random_y = SCREEN_HEIGHT * 0.5;
		}
		rect_.y = random_y;
	}
}

void Enemy::Reset(const int& xboder){
	rect_.x = xboder;
	int random_y = rand() % 800;
	if(random_y > SCREEN_HEIGHT - 150){
		random_y = SCREEN_HEIGHT * 0.5;
	}
	rect_.y = random_y;

	for(int i = 0; i < p_shoot_list_.size(); i++){
		Shoot* p_shoot = p_shoot_list_.at(i);
		if(p_shoot){
			ResetShoot(p_shoot);
		}
	}
}

void Enemy::ResetShoot(Shoot* p_shoot){
	p_shoot->SetRect(rect_.x, rect_.y + rect_.h*0.5);
}

Enemy* Enemy::InitEnemies(){
    Enemy* p_enemies = new Enemy[NUM_ENEMIES];
    for (int enemy = 0; enemy < NUM_ENEMIES; enemy++) {
        Enemy* p_enemy = (p_enemies + enemy);
        if (p_enemy) {
            bool setImg = p_enemy->LoadImg(g_name_enemy);
            if (setImg == false) {
                delete[] p_enemies; 
                return nullptr;
            }

            int random_y = rand() % 800;
            if (random_y > SCREEN_HEIGHT - 150) {
                random_y = SCREEN_HEIGHT * 0.5;
            }

            p_enemy->SetRect(SCREEN_WIDTH + enemy * 1000, random_y);
            p_enemy->set_x_val(SPEED_ENEMY);

            Shoot* p_shoot = new Shoot();
            p_enemy->ActionEnemy(p_shoot);
        }
    }
    return p_enemies;
}

void Enemy::handleInputAction(SDL_Event events){}

