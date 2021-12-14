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
    let low_points = f_map.find_low_points();
    let silver: u16 = low_points.iter()
        .map(|(i, j, x)| {
            // println!("{} {}", i, j);
            *x + 1
        })
        .sum();
    println!("Silver: {}", silver);
}
