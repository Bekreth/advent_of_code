extern crate regex;
extern crate lazy_static;

mod cave;
mod walker;

use cave::CaveSystem;
use walker::{Walker, SilverWalker};

use std::fs;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");

    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");

    let cave_system = CaveSystem::new(contents.clone());
    let first_walker = SilverWalker::new();

    let successful_walkers = walker_solver(first_walker, &cave_system);

    println!("Silver: {:?}", successful_walkers.len());
}


fn walker_solver<T: Walker>(first_walker: T, cave_system: &CaveSystem) -> Vec<T> {
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
    finished_walkers
}