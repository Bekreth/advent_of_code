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

    let image = Image::new(&mut lines);

    println!("{}", image);
    let new_image = image.iterate();
    println!("");
    println!("{}", new_image);

    let new_image = new_image.iterate();
    println!("");
    println!("{}", new_image);

    println!("Silver: {}", new_image.count())
}
