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
                .map(|c| c.to_digit(10).expect("") as u8)
                .enumerate()
                .for_each(|(j, number)| {
                    grid.initialize_octopus(i, j, number)
                })
        });
    
    let mut total_flash = 0;
    let mut counter = 1;
    loop {
        grid.run_loop();
        if total_flash == 0 && grid.is_total_flash() {
            total_flash = counter;
        }
        if counter == 100 {
            println!("Silver {}", grid.get_flash_count());
        }
        if total_flash != 0 {
            break;
        }
        counter += 1;
    }
    println!("Gold {}", total_flash);
}
