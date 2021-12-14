mod floor_map;

use floor_map::FloorMap;

use std::fs;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename = args.get(1).expect("missing filename");

    let content = fs::read_to_string(filename)
        .expect("failed to read file");
    
    let f_map = FloorMap::new(content);
    let low_points = &f_map.find_low_points();
    let silver: u16 = low_points.iter()
        .map(|(_, _, x)| *x as u16)
        .map(|x| x + 1)
        .sum();
    println!("Silver: {}", silver);

    let mut gold_solutions: Vec<usize> = low_points.iter()
        .map(|(i, j, _)| (&f_map).calculate_basin(*i, *j).len())
        .collect::<Vec<usize>>();

    gold_solutions.sort();
    let size = gold_solutions.len();
    let last_set: &[usize] = gold_solutions
        .get(size-3..size)
        .expect("expected 3 last values");

    let gold: usize = last_set.iter()
        .map(|v| *v)
        .reduce(|previous, value| previous * value)
        .expect("Failed to reduce finals");

    println!("Gold: {}", gold);
}
