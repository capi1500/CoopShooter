Player{
    ObjectProperties{
        position 0 -1
        name player1
        texture mage
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
}