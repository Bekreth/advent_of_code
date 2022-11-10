mod image;

use image::Image;

use std::fs;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");
    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");
    let mut lines = contents.lines();

    let mut image = Image::new(&mut lines);
    let mut silver = 0;

    // println!("{}", image);
    for i in 1..=50 {
        image = image.iterate();
        // println!("{}\n{}", i, image);
        if i == 2 {
            silver = image.count();
        }
    }

    println!("Silver: {}", silver);
    println!("Gold: {}", image.count());
}