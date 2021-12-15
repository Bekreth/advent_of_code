mod floor_map;
mod walker;

use floor_map::{FloorMap};
use walker::{Walker};

use std::fs;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename = args.get(1).expect("missing filename");
    let line_data: String = fs::read_to_string(filename)
        .expect("Unable to read file");

    let floor_map = FloorMap::new(line_data);
    let base_walker = Walker::new();

    let mut running: Vec<Walker> = vec![base_walker];
    // let mut best_solution: u16 = 1078;
    // let mut best_solution: u16 = u16::MAX;
    let mut best_solution: u16 = floor_map.upper_limit;

    let mut counter = 0;

    while running.len() > 0 {
        counter += 1;
        let walker: Walker;
        match running.pop() {
            Some(w) => walker = w,
            None => break,
        }
        if counter == 500_000 {
            println!("");
            println!("best solution {}", best_solution);
            println!("depth: {}", running.len());
            println!("{:?}", walker);
            counter = 0;
        }
        for w in walker.next_step(&floor_map) {
            if w.too_risky(best_solution, floor_map.maxes) {
                continue;
            }
            match w.completed(floor_map.maxes) {
                Some(walk_risk) => {
                    println!("risk value: {}", walk_risk);
                    println!("depth: {}", running.len());
                    best_solution = walk_risk;
                    continue;
                },
                None => {
                    running.push(w);
                },
            }
        }
    }

    println!("Silver: {}", best_solution);
}
