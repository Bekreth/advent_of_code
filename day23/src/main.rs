mod cave;
mod adjacent;

use std::fs;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");

    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");

    println!("{}", contents);
}
