#include "Spaceships/Spaceship.h"

Spaceship::Spaceship(const sf::Vector2f & pos,
	const sf::Texture & shipTex,
	const sf::Texture & missileTex)
	: mRot{ 0 },
	mSprite{ shipTex, sf::IntRect{0, 0, 64, 64} },
	mMissiles{10, Missile{ missileTex, pos }}
{
	mSprite.setPosition(pos);
	mSprite.setOrigin(32, 32);
}

void Spaceship::update(const sf::Time & dt)
{
	float cs = cos(mRot), sn = sin(mRot);

	if (forward || backward || left || right) {
		if (forward) {
			mVel += {cs * mAcc * dt.asSeconds(),
				sn * mAcc * dt.asSeconds()};
		}
		if (left) {
			mRotVel += -mRotAcc * dt.asSeconds();
		}

		if (backward) {
			mVel += {-cs * backPenalty * mAcc * dt.asSeconds(),
				-sn * backPenalty * mAcc * dt.asSeconds()};
		}

		if (right) {
			mRotVel += mRotAcc * dt.asSeconds();
		}

		isMoving = true;

		if (!backward) {
			mSprite.setTextureRect({ 64, 0, 64, 64 });
		}

	} else {
		isMoving = false;
		mSprite.setTextureRect({ 0, 0, 64, 64 });
	}

	mVel *= mDamp;
	mRot *= mRotDamp;

	mSprite.move(mVel);

	mRot += mRotVel * dt.asSeconds();
	mSprite.setRotation(mRot * 180.f / (float)M_PI);

	for (auto & mis : mMissiles) {
		mis.update(dt);
		if (distance(*this, mis) > 1000)
			mis.visible = false;
	}
}

float distance(const Spaceship & s, const Missile & m) {
	float xs = s.getPosition().x, ys = s.getPosition().y;
	float xm = m.getPosition().x, ym = m.getPosition().y;
	return sqrt((xs - xm)*(xs - xm) + (ys - ym)*(ys - ym));
}


void Spaceship::draw(sf::RenderTarget & t)
{
	for (auto & mis : mMissiles)
		mis.draw(t);

	t.draw(mSprite);
}

sf::Vector2f Spaceship::getPosition() const
{
	return mSprite.getPosition();
}

void Spaceship::launchMissile()
{
	auto res = std::find_if(mMissiles.begin(), mMissiles.end(),
		[](Missile & m) -> bool {
		return m.visible == false;
	}
	);

	if (res != mMissiles.end()) {
		res._Ptr->launch(getPosition(), mRot);
	}
}
