extern crate regex;
extern crate lazy_static;

mod region;

use region::Region;

use std::fs;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");
    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");
    let silver_region = contents.lines()
        .map(|line| Region::new(line, (-50, 50, -50, 50, -50, 50)))
        .fold(Region::default(), |mut acc, region| {
            if region.is_on {
                acc.add(region);
            } else {
                acc.remove(region);
            }
            acc
        });

    println!("Silver: {}", silver_region.size());
}
