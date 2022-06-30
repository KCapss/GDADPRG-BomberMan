#include "BombBehaviour.h"
#include "../AGameObject.h"

#include "../ObjectPooling/ObjectPoolHolder.h"

#include "../TextureManager.h"
#include "../TileMapState.h"
#include "../PlayerState.h"

#include "../BombObject.h"
#include "../GameObjectManager.h"
#include "../Player.h"
BombBehaviour::BombBehaviour(string name): AComponent(name, Script)
{
}

void BombBehaviour::perform()
{
	BombObject* bomb = (BombObject*)this->getOwner();
	this->ticks += this->deltaTime.asSeconds();

	if (this->ticks > timer || bomb->hitConfirmed()) {
		reset();
		//Do some action

		int maxRange = PlayerState::getInstance()->retrieveMaxRange();
		int vfxTileCount = (maxRange * 4) + 1;

		
		for (int i = 4; i >= 0; i--) {
			sf::Vector2f posPlaceholder = bomb->getTransformable()->getPosition();
			TileMapState::getInstance()->registerExplosion(posPlaceholder, i, 0);
		}

		int availableSpots = TileMapState::getInstance()->availableExplotion();
		cout << "Available Spots: " << availableSpots << endl;

		this->bombVFXPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::VFX_POOL_TAG);
		for (int i = 0; i < availableSpots; i++) {
			this->bombVFXPool->requestPoolable();
		}

		GameObjectPool* bombPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECT_POOL_TAG);
		bombPool->releasePoolable((APoolable*)this->getOwner());


		Player* player = (Player*)GameObjectManager::getInstance()->findObjectByName("Player");
		player->incrementBombUsedCount(-1);
		//RemoveObject

	}
}

void BombBehaviour::reset()
{
	BombObject* bomb = (BombObject*)this->getOwner();
	bomb->resetHit();
	this->ticks = 0.0f;
}
