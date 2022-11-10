use std::str::Lines;
use std::fs;
use std::env;

#[derive(Debug)]
struct Bingo {
    entries: [[u8;5];5],
    hitbox: [[bool;5];5]
}

impl Bingo {
    fn new(input: [&str; 5]) -> Self {
        let mut entries: [[u8; 5]; 5] = [[0; 5];5];
        for i in 0..5 {
            input[i]
                .split_whitespace()
                .map(|v| v.parse::<u8>().expect("failed to map"))
                .enumerate()
                .for_each(|(j,value)| entries[i][j] = value);
        }
        return Bingo{
            entries: entries,
            hitbox:[[false;5];5]
        }
    }

    fn call_number(&mut self, number: u8) {
        for i in 0..5{
            for j in 0..5 {
                if self.entries[i][j] == number {
                    self.hitbox[i][j] = true
                }
            }
        }
    }

    fn five_across(&self) -> bool {
        for i in 0..5 {
            if self.hitbox[i][0] &&
                self.hitbox[i][1] &&
                self.hitbox[i][2] &&
                self.hitbox[i][3] &&
                self.hitbox[i][4] { 
                    return true 
                }
        }
        for i in 0..5 {
            if self.hitbox[0][i] &&
                self.hitbox[1][i] &&
                self.hitbox[2][i] &&
                self.hitbox[3][i] &&
                self.hitbox[4][i] { 
                    return true
                }
        }
        false
    }

    fn calculate_score(&self, last_score: u8) -> u32 {
        let mut summation: u32 = 0;
        for i in 0..5 {
            for j in 0..5 {
                if !self.hitbox[i][j] {summation += self.entries[i][j] as u32}
            }
        }
        let output =  summation * (last_score as u32);
        return output
    }
}

fn collect_score_cards<'a>(lines: &'a mut Lines) -> [&'a str; 5]{
    let mut output: [&'a str; 5] = [""; 5];
    for i in 0..5 {
        output[i] = lines.next().expect("should have gotten a line")
    }
    return output
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");

    let file_data = fs::read_to_string(filename)
        .expect("Unable to read file");

    let mut contents = file_data.lines();

    let callout = contents.next()
        .expect("should have gotten header")
        .split(",")
        .map(|number| number.parse::<u8>().expect("failed to parse"))
        .collect::<Vec<u8>>();
    let mut caller = callout.iter();
    let mut all_cards: Vec<Bingo>= vec![];

    while contents.next().is_some() {
        let score_card = collect_score_cards(&mut contents);
        all_cards.push(Bingo::new(score_card));
    }

    let mut bingo_cards: Vec<&mut Bingo> = all_cards.iter_mut().collect();
    let bingo_count = bingo_cards.len();

    let mut call = 0;
    let mut silver = vec![];

    while (silver = bingo_cards.iter()
        .filter(|card| card.five_across())
        .map(|card| card.calculate_score(call))
        .collect()) == () && silver.len() == 0
    {
        call = *caller.next().expect("");
        bingo_cards.iter_mut()
            .for_each(|card| card.call_number(call))
    }

    let mut gold = 0;

    while bingo_cards.len() > 0 {
        call = *caller.next().expect("");
        bingo_cards.iter_mut()
            .for_each(|card| card.call_number(call));

        if bingo_cards.len() == 1 {
            gold = bingo_cards[0].calculate_score(call);
        }

        bingo_cards = bingo_cards
            .drain(..)
            .filter(|card| !card.five_across())
            .collect();
    }

    println!("Silver: {}", silver[0]);
    println!("Gold: {}", gold);
}
