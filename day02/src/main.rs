use std::fs;

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");
    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");

    // println!("Silver: {}", silver_aggregator.depth_increases);
    // println!("Gold  : number of depth increases: {}", gold_aggregator.depth_increases);
}
