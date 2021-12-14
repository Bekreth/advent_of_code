extern crate regex;
extern crate lazy_static;

mod input_data;
mod paper;

use std::fs;
use std::env;

use input_data::InputData;
use paper::Paper;

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename = args.get(1).expect("missing filename");
    let mut paper: Paper = Paper::new();
    fs::read_to_string(filename)
        .expect("Unable to find file")
        .lines()
        .filter_map(InputData::new)
        .for_each(|input| paper.handle_input_data(input));

    println!("Gold: {}", paper);
}
