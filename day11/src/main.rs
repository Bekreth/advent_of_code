extern crate array_init;

mod grid;
mod octopus;

use std::fs;
use std::env;
use grid::{Grid};


fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");
    let grid: &mut Grid = &mut Grid::new();
    fs::read_to_string(filename)
        .expect("Unable to find file")
        .lines()
        .enumerate()
        .for_each(|(i, line)| {
            line.chars()
                .map(|c| c as u8)
                .enumerate()
                .for_each(|(j, number)| {
                    grid.initialize_octopus(i, j, number)
                })
        });
    
    for i in 0..3 {
        grid.run_loop();
        println!("Line {} -------", i);
        println!("{}", grid);
    }
    // println!("Silver {}", grid);
}
