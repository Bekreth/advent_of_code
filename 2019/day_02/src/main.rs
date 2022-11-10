use std::fs::File;
use std::io::Read;
use crate::OpCode::{Add, Multiply, Halt};

enum OpCode {
    Add,
    Multiply,
    Halt
}

#[derive(Clone)]
struct Machine {
    reader_position: usize,
    tape: Vec<i64>
}

impl Machine {
    fn new(filename: &String) -> Machine {
        let tape = read_input_file(filename)
            .split(",")
            .map(|int_code| int_code.parse::<i64>().unwrap_or_default())
            .collect();
        let reader_position: usize = 0;
        Machine {reader_position, tape}
    }

    fn overwrite_tape_at_index(&mut self, index: usize, value: i64) {
        self.tape[index] = value;
    }

    fn read_tape(&self) -> OpCode {
        return match self.tape[self.reader_position] {
            1 => Add,
            2 => Multiply,
            99 => Halt,
            _ => panic!("Shouldn't have received this")
        }
    }

    fn operate(&mut self, operator: &dyn Fn(i64, i64) -> i64) {
        let position_1 = self.tape[self.reader_position + 1];
        let position_2 = self.tape[self.reader_position + 2];
        let position_3 = self.tape[self.reader_position + 3];

        let value_1 = self.tape[position_1 as usize];
        let value_2 = self.tape[position_2 as usize];

        self.tape[position_3 as usize] = operator(value_1, value_2);
    }

    fn advance_reader(&mut self) {
        self.reader_position += 4;
    }

    fn run_machine(&mut self) {
        loop {
            match self.read_tape() {
                Halt => break,
                Add => self.operate(&|x, y| x + y),
                Multiply => self.operate(&|x, y| x * y)
            }
            self.advance_reader();
        }
    }

    fn output(&self) -> i64 {
        return self.tape[0];
    }
}

fn main() {
    silver();
    println!("=======");
    gold();
}

fn silver() {
    println!("Silver");
    let mut machine = Machine::new(&String::from("input.txt"));
    machine.run_machine();
    println!("{:?}", machine.output());
}

fn gold() {
    println!("Gold");
    let base_machine = Machine::new(&String::from("input.txt"));
    for i in 0..100 {
        for j in 0..100 {
            let mut current_machine = base_machine.clone();
            current_machine.overwrite_tape_at_index(1, i);
            current_machine.overwrite_tape_at_index(2, j);

            current_machine.run_machine();
            if current_machine.output() == 19690720 {
                println!("noun: {}, verb: {}, total: {}", i, j, 100 * i + j);
                break;
            }
        }
    }
}

fn read_input_file(file_name: &String) -> String {
    let mut file = File::open(file_name).expect("Failed to read data");
    let mut file_contents = String::new();
    file.read_to_string(&mut file_contents).expect("Failed to read data");
    return file_contents
}

