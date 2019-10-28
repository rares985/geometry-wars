#include "PowerupFactory.h"
#include <Files\LifePowerup.h>
#include <Files\FreezePowerup.h>

class PowerupNotFoundException {};

std::unique_ptr<Powerup> PowerupFactory::createPowerup(PowerupType type)
{
	switch (type) {
		case PowerupType::PT_LIFE:
			return std::make_unique<LifePowerup>();
			break;
		case PowerupType::PT_FREEZE:
			return std::make_unique<FreezePowerup>();
			break;
		default:
			throw new PowerupNotFoundException();
		break;
		
	}
}
