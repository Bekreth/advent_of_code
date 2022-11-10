extern crate regex;
extern crate lazy_static;

mod cave;
mod walker;

use cave::{CaveSystem, Cave};
use walker::{Walker, SilverWalker, GoldWalker};

use std::fmt::Display;
use std::fs;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");

    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");

    let cave_system = CaveSystem::new(contents.clone());

    let silver_walker = SilverWalker::new();
    let silver_success = walker_solver(silver_walker, &cave_system);
    println!("Silver: {:?}", silver_success.len());

    let gold_walker = GoldWalker::new();
    let gold_successes = walker_solver(gold_walker, &cave_system);
    println!("Gold: {:?}", gold_successes.len());
}


fn walker_solver<T: Walker + Display>(first_walker: T, cave_system: &CaveSystem) -> Vec<Vec<Cave>> {
    let mut walkers = vec![first_walker];
    let mut finished_walkers = vec![];
    loop {
        let walker = match walkers.pop() {
            None => break,
            Some(w) => w
        };
        let next_walkers = walker.possible_next_steps(cave_system);
        for w in next_walkers {
            if w.finished() {
                finished_walkers.push(w);
            } else {
                walkers.push(w);
            }
        }
    }
    let mut output = finished_walkers.iter()
        .map(|w| w.previously_visited())
        .collect::<Vec<Vec<Cave>>>();

    output.sort();
    output.dedup();
    output
}