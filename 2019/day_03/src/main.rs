use std::collections::{HashMap};
use std::fs::File;
use std::io::Read;
use crate::Direction::{Up, Right, Down, Left};

/*
6
159
135
*/

#[derive(Copy, Clone)]
enum Direction {
    Left,
    Right,
    Up,
    Down
}

struct WirePath {
    id: i32,
    step_count: i32,
    position: (i32, i32),
}

impl WirePath {
    fn move_direction (&mut self, direction: Direction) {
        match direction {
            Left => self.position = (self.position.0 - 1, self.position.1),
            Right => self.position = (self.position.0 + 1, self.position.1),
            Up => self.position = (self.position.0, self.position.1 + 1),
            Down => self.position = (self.position.0, self.position.1 - 1),
        }

        self.step_count = self.step_count + 1;
    }
}

fn main() {
    silver();
    println!("=======");
    gold();
}

fn silver() {
    println!("Silver");
    let mut wire_path: HashMap<(i32, i32), HashMap<i32, i32>> = HashMap::new();

    let wires: Vec<String> = read_input_file(&String::from("input.txt"))
        .split("\n")
        .map(|line| String::from(line))
        .collect();

    run_wire(&wires[0], &mut WirePath {id: 0, step_count: 0, position: (0, 0)}, &mut wire_path);
    run_wire(&wires[1], &mut WirePath {id: 1, step_count: 0, position: (0, 0)}, &mut wire_path);

    println!("{}", examine_wire_silver_paths(&wire_path));
}

fn gold() {
    println!("Gold");
    let mut wire_path: HashMap<(i32, i32), HashMap<i32, i32>> = HashMap::new();

    let wires: Vec<String> = read_input_file(&String::from("input.txt"))
        .split("\n")
        .map(|line| String::from(line))
        .collect();

    run_wire(&wires[0], &mut WirePath {id: 0, step_count: 0, position: (0, 0)}, &mut wire_path);
    run_wire(&wires[1], &mut WirePath {id: 1, step_count: 0, position: (0, 0)}, &mut wire_path);

    println!("{}", examine_wire_gold_paths(&wire_path));
}

fn read_input_file(file_name: &String) -> String {
    let mut file = File::open(file_name).expect("Failed to read data");
    let mut file_contents = String::new();
    file.read_to_string(&mut file_contents).expect("Failed to read data");
    return file_contents
}

fn run_wire(instructions: &String, wire: &mut WirePath, wire_path: &mut HashMap<(i32, i32), HashMap<i32, i32>>) {
    for instruction in instructions.split(",") {
        let parsed_instruction = String::from(instruction);
        let split_instruction = parsed_instruction.split_at(1);
        let direction = match split_instruction.0 {
            "U" => Up,
            "D" => Down,
            "R" => Right,
            "L" => Left,
            _ => panic!("This char shouldn't have popped up {}")
        };

        let step_size = split_instruction.1.parse::<i32>().unwrap_or_default();

        for _ in 0..step_size {
            wire.move_direction(direction);
            match wire_path.get(&wire.position) {
                Some(map) => {
                    if !map.contains_key(&wire.id) {
                        let mut next = map.clone();
                        next.insert(wire.id, wire.step_count);
                        wire_path.insert(wire.position, next);
                    }
                },
                None => {
                    let mut next = HashMap::new();
                    next.insert(wire.id, wire.step_count);
                    wire_path.insert(wire.position, next);
                }
            };
        }
    }
}

fn examine_wire_silver_paths(wire_path: &HashMap<(i32, i32), HashMap<i32, i32>>) -> i32 {
    let mut distances: Vec<i32> = wire_path.iter()
        .filter(|(_, value)| value.len() > 1)
        .map(|(key, _)| key.0.abs() + key.1.abs())
        .collect();

    distances.sort_by(|a, b| a.cmp(b));
    distances[0]
}

fn examine_wire_gold_paths(wire_path: &HashMap<(i32, i32), HashMap<i32, i32>>) -> i32 {
    let mut distances: Vec<i32> = wire_path.iter()
        .filter(|(_, value)| value.len() > 1)
        .map(|(_, value)| value.iter()
            .map(|(_, step_count)| step_count)
            .sum()
        )
        .collect();

    distances.sort_by(|a, b| a.cmp(b));
    distances[0]
}


