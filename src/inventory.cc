/*
 * FILNAMN:       inventory.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *				  Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-12-12
 *
 */

#include "inventory.h"

namespace feed
{
	Inventory::Inventory()
	{}

	Inventory::~Inventory()
	{
		for (auto weapon : inventory_list)
			delete weapon;
	}

	void Inventory::add(Weapon::Type weapon_type, int ammo)
	{
        for (auto weapon : inventory_list)
        {
            if (weapon->get_type() == weapon_type)
            {
                weapon->addAmmo(ammo);
                return;
            }
        }

        inventory_list.push_back(Weapon::createWeapon(weapon_type));
        inventory_list.back()->addAmmo(ammo);
	}

	void Inventory::remove(unsigned int index)
	{
		inventory_list.erase(inventory_list.begin() + index);
	}

	Weapon* Inventory::get_item(unsigned int index)
	{
		Weapon* weapon = nullptr;
		
		if (index < inventory_list.size())
			weapon = inventory_list[index];

		return weapon;
	}

    unsigned int Inventory::get_size() const
    {
        return inventory_list.size();
    }
}
