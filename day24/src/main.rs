extern crate regex;
extern crate lazy_static;

mod alu;
mod operation;

use alu::ALU;

use std::fs;
use std::env;

const AVAILABLE_INTS: [u8; 9] = [9, 8, 7, 6, 5, 4, 3, 2, 1];

fn find_monad(contents: String, int_size: usize, current_input: i128) -> Option<i128> {
    if int_size == 0 {
        let mut alu = ALU::new(current_input);
        contents.lines().for_each(|line| alu.apply_operation(line));
        return if alu.output() == 1 { Some(current_input) } else { None }
    } else {
        for i in 0..9 {
            let next_input = current_input * 10 + (AVAILABLE_INTS[i] as i128);
            match find_monad(contents.clone(), int_size - 1, next_input) {
                None => {
                    // if int_size > 3 {
                        // println!("Nope: {}", current_input);
                    // }
                },
                Some(v) => return Some(v),
            }
        }
        None
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename = args.get(1).expect("missing filename");
    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");
    let input_size = args.get(2).expect("missing input");
    let input = input_size.parse::<usize>().expect("failed to parse size of input");

    let output = find_monad(contents, input, 0);
    // let mut alu = ALU::new(99);
    // contents.lines().for_each(|line| alu.apply_operation(line));
    println!("Silver: {:?}", output);

}
