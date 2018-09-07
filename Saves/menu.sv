Menu{
    name mainMenu
    Labels{
        Label{
            texture logo
            displayText false
        }
        Label{
            text "n\n\nn"
            displayText false
        }
        Button{
            text "New Game"
            Event{
                what newGame
            }
        }
        Button{
            text "Resume"
            Event{
                what load
                par1 Temp
            }
        }
        Button{
            text "Exit"
            Event{
                what exit
            }
        }
    }
}
Menu{
    name pause
    Labels{
        Button{
            text "Resume"
            Event{
                what load
                par1 Temp
            }
        }
        Button{
            text "Restart"
            Event{
                what load
                par1 Default
            }
        }
        Button{
            text "Main menu"
            Event{
                what changeMenu
                par1 mainMenu
            }
        }
        Button{
            text "Exit"
            Event{
                what exit
            }
        }
    }
}
Menu{
    name play
    gameRunning true
    gameDraw true
    splitScreen true
}
Menu{
    name editor
    gameRunning false
    gameDraw true
    freeCamera true
}
Menu{
    name editorPause
    Labels{
        Button{
            text "Resume"
            Event{
                what changeMenu
                par1 editor
            }
        }
        Button{
            text "Save"
            Event{
                what save
                par1 Temp
            }
        }
        Button{
            text "Main menu"
            Event{
                what changeMenu
                par1 mainMenu
            }
        }
        Button{
            text "Exit"
            Event{
                what exit
            }
        }
    }
}
active mainMenu