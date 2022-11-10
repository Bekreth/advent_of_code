use player::Player;
use dice::Dice;

pub struct Game<'a, T: Dice> {
    player1: &'a mut Player,
    player2: &'a mut Player,
    dice: &'a mut T,
    win_condition: u16
}

impl <'a, T: Dice> Game<'a, T> {
    pub fn new(
        player1: &'a mut Player, 
        player2: &'a mut Player, 
        dice: &'a mut T,
        win_condition: u16
    ) -> Self {
        Game::<'a, T> {
            player1: player1,
            player2: player2,
            dice: dice,
            win_condition: win_condition,
        }
    }

    pub fn run_game(self) -> u32 {
        // println!("{:?}", self.player1);
        // println!("{:?}", self.player2);

        let mut which_player = true;

        while self.player1.score < self.win_condition 
            && self.player2.score < self.win_condition {
            let rolled_value = self.dice.roll_thrice();
            // println!("roll: {:?}", rolled_value);
            if which_player {
                self.player1.rolled_value(rolled_value);
                // println!("{:?}", self.player1);
            } else {
                self.player2.rolled_value(rolled_value);
                // println!("{:?}", self.player2);
            }
            which_player = !which_player;
            // println!();
        }

        let low_score = if self.player1.score < self.player2.score {
            self.player1.score
        } else { self.player2.score };

        // println!("GAME: {} {}", low_score, self.dice.roll_counter());
        (low_score as u32) * (self.dice.roll_counter() as u32)
    }
}