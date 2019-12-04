use std::fs::File;
use std::io::Read;

fn main() {
    println!("Hello, world!");
}

fn read_input_file(file_name: &String) -> String {
    let mut file = File::open(file_name).expect("Failed to read data");
    let mut file_contents = String::new();
    file.read_to_string(&mut file_contents).expect("Failed to read data");
    return file_contents
}

