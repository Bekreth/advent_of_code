mod map;

use map::Map;

use std::env;
use std::fs;

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename = args.get(1).expect("missing filename");
    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");

    let mut map = Map::new(contents);
    let silver = &map.move_until_unable();

    println!("Silver: {}", silver);
}
