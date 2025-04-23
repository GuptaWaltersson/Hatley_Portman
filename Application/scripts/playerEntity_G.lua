entities = {
    --Player
    {
        type = "player",
        position = {x = 800, y= 450},
        speed = {dx = 10, dy = 10}
    },
    
    --Ground platform
    {
        type = "ground",
        position = {x=800,y=350}
    }
}

function on_move_left(player)
    player.x = player.x - player.dx
    return player
end

function on_move_right(player)
    player.x = player.x + player.dx
    return player
end


