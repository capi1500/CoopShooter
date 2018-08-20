Player{
    ObjectProperties{
        position 0 -1
        name player1
        texture humanMale
    }
    PhysicObjectProperties{
        type dynamic
        shape circle
        friction 0.1
        density 1
    }
    EntityProperties{
        maxHP 25
        HP 25
        jumpHeight 300
        movementSpeed 10
        EQ{
            dagger 1 0
            laserRod 50 0
        }
    }
    PlayerProperties{
        textureBase humanMale
        textureHair longWhiteHair
        textureBoots bootsMiddleGray
        textureBody gandalfBody
        textureCloak cloackGray
		textureBeard longWhiteBeard
    }
}
