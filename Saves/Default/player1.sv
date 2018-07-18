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
        maxHP 10
        HP 10
        jumpHeight 300
        movementSpeed 10
        EQ{
            staff 1
        }
    }
    PlayerProperties{
        textureBase humanMale
        textureHair longWhiteHair
        textureBoots bootsMiddleGray
        textureBody gandalfBody
        textureCloack cloackGray
    }
}