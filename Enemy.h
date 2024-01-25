#ifndef ENEMY_H
#define ENEMY_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include "Shoot.h"
#include <vector>

#define WIDTH_ENEMY 100
#define HEIGHT_ENEMY 50

class Enemy : public BaseObject{
	public:
		Enemy();
		~Enemy();
		void handleMove(const int& x_border, const int& y_border);
		void handleInputAction(SDL_Event events);
		void set_x_val(const int& val){
			x_val_ = val;
		}

		void set_y_val(const int& val){
			y_val_ = val;
		}

		int get_x_val() const{
			return x_val_;
		}

		int get_y_val() const{
			return y_val_;
		}

		void SetShootList(std::vector<Shoot*> shoot_list){
			p_shoot_list_ = shoot_list;
		}
		std::vector<Shoot*> GetShootList() const{
			return p_shoot_list_;
		}

		void ActionEnemy(Shoot* p_shoot);
		void ShootEnemy(SDL_Surface* des, const int& x_limit, const int& y_limit);
		void Reset(const int& xboder);
		void ResetShoot(Shoot* p_shoot);
		static Enemy* InitEnemies();

	private:
		int x_val_;
		int y_val_;
		std::vector<Shoot*> p_shoot_list_;
};

#endif