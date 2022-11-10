use std::fs;

fn main() {
    let filename = "input_data.txt";
    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");
    println!("{}", contents);
}
