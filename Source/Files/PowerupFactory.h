#pragma once

#ifndef POWERUP_FACTORY_H_
#define POWERUP_FACTORY_H_

#include <memory>


class Powerup;


enum class PowerupType {
	PT_LIFE,
	PT_FREEZE,
	PT_MAX_NO
};

class PowerupFactory {

public:
	static std::unique_ptr<Powerup> createPowerup(PowerupType type);
};


#endif /* POWERUP_FACTORY_H_ */
