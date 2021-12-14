mod insertion_set;
mod polymer;

use polymer::PolymerChain;
use insertion_set::InsertionSet;

use std::fs;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename = args.get(1).expect("missing filename");

    let content = fs::read_to_string(filename)
        .expect("failed to read file");
    let mut lines = content.lines();
    let mut polymer = PolymerChain::new(lines.next().expect(""));
    lines.next();
    let mut insertions = InsertionSet::new();
    lines.for_each(|rule_string| insertions.add_insertion_rule(rule_string));

    for _ in 0..10 {
        polymer.insert(&insertions);
    }
    println!("Silver: {}", polymer);
    
    for i in 10..40 {
        println!("{}", i);
        polymer.insert(&insertions);
    }
    println!("Gold: {}", polymer);
}
