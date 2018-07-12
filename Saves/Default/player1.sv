Player{
    ObjectProperties{
        position 10 130
        name player1
        texture ball
    }
    PhysicObjectProperties{
        type dynamic
        shape circle
        friction 0.3
        density 1
    }
    EntityProperties{
        maxHP 10
        HP 10
        jumpHeight 250
        movementSpeed 10
        EQ{
            gun 1
        }
    }
}