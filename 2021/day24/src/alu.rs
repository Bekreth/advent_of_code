use regex::Regex;
use lazy_static::lazy_static;

use std::collections::HashMap;

use crate::operation::{Operator, Operations};

enum Either {
    Left(Register),
    Right(i128),
}

#[derive(Debug, Hash, PartialEq, Eq, Copy, Clone)]
enum Register {
    W, X, Y, Z,
}

pub struct ALU {
    registers: HashMap<Register, i128>,
    input: Vec<i128>,
}

fn parse_register(v1: &str) -> Either {
    match v1 {
        "w" => Either::Left(Register::W),
        "x" => Either::Left(Register::X),
        "y" => Either::Left(Register::Y),
        "z" => Either::Left(Register::Z),
        _ => Either::Right(v1.parse::<i128>().expect("should have successfully parsed u32")),
    }
}

impl ALU {
    pub fn new(mut input_size: i128) -> Self {
        let mut numbers = vec![];
        loop {
            let next_number = input_size % 10;
            if next_number == 0 {
                break;
            }
            input_size /= 10;
            numbers.push(next_number);
        }
        ALU {
            registers: HashMap::from([
                (Register::W, 0),
                (Register::X, 0),
                (Register::Y, 0),
                (Register::Z, 0),
            ]),
            input: numbers,
        }
    }

    pub fn apply_operation(&mut self, line: &str) {
        lazy_static!{
            static ref OP_REGEX: Regex = Regex::new(r"^(?P<op>[a-z]{3}) (?P<r1>[wxyz])( (?P<r2>[wxyz]|-?\d+))?$")
                .expect("Failed to parse point regex");
        }

        let captures = OP_REGEX.captures(line).expect("Shouldn't have failed to captures line");
        let cap_1 = captures.name("r1").expect("").as_str();
        match captures.name("op").expect("Should have found op").as_str() {
            "inp" => {
                let input_value = self.input.pop().expect("Shouldn't have run out of numbers");
                match parse_register(cap_1) {
                    Either::Left(r) => {
                        self.registers.insert(r, input_value);
                    },
                    Either::Right(_) => panic!("Should have gotten register"),
                }
            },
            "add" => {
                let cap_2 = captures.name("r2").expect("").as_str();
                self.upsert_value(Operations::Add, cap_1, cap_2);
            },
            "mul" => {
                let cap_2 = captures.name("r2").expect("").as_str();
                self.upsert_value(Operations::Multiply, cap_1, cap_2);
            },
            "div" => {
                let cap_2 = captures.name("r2").expect("").as_str();
                self.upsert_value(Operations::Divide, cap_1, cap_2);
            },
            "mod" => {
                let cap_2 = captures.name("r2").expect("").as_str();
                self.upsert_value(Operations::Modulo, cap_1, cap_2);
            },
            "eql" => {
                let cap_2 = captures.name("r2").expect("").as_str();
                self.upsert_value(Operations::Equal, cap_1, cap_2);
            },
            _ => panic!("op is unknown"),
        }
    }

    fn upsert_value<T : Operator>(&mut self, op: T, v1: &str, v2: &str) {
        let r1 = parse_register(v1);
        let r2 = parse_register(v2);

        let value1 = match r1 {
            Either::Right(_) => panic!("Should have gotten register in slot 1"),
            Either::Left(r) => *self.registers.get(&r).expect("Should have succeeded lookup"),
        };

        let value2 = match r2 {
            Either::Right(v) => v,
            Either::Left(r) => *self.registers.get(&r).expect("Should have succeeded lookup"),
        };

        match r1 {
            Either::Right(_) => panic!("Should have gotten register in slot 1"),
            Either::Left(r) => {
                self.registers.insert(r, op.apply(value1, value2)).expect("Shouldn't have failed to upsert value");
            },
        }
    }

    pub fn output(&self) -> i128 {
        *self.registers.get(&Register::Z).expect("Definitely has a Z value")
    }
}
