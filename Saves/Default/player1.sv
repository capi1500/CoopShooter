Player{
    ObjectProperties{
        position 20 -20
        name player1
        texture ballBlue
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
            gun 1
        }
    }
}