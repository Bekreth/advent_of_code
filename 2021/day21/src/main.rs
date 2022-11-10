mod player;
mod dice;
mod game;

use player::Player;
use dice::Deterministic;
use game::Game;

use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let input = args.get(1).expect("missing filename");

    let (mut player1, mut player2) = match input.as_str() {
        "sample" => (
            (
                Player::new(1, 4),
                Player::new(2, 8),
            )
        ),
        "input" => (
            (
                Player::new(1, 4),
                Player::new(2, 7),
            )
        ),
        _ => panic!("nope")
    };

    let mut d_dice = Deterministic::new();

    let silver_game = Game::new(
        &mut player1,
        &mut player2,
        &mut d_dice,
        1000
    );

    let silver = silver_game.run_game();
    println!("Silver: {}", silver);
}
