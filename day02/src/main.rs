use std::fs;
use std::u32;
use std::env;

struct Positioning {
    x: i32,
    y: i32,
    aim: i32
}

impl Positioning {
    fn new(direction: &str, value: i32) -> Self {
        match direction {
            "forward" => Positioning{x: value, y: 0, aim: 0},
            "up" => Positioning{x: 0, y: 0, aim: -value},
            "down" => Positioning{x: 0, y: 0, aim: value},
            _ => Positioning{x: 0, y: 0, aim: 0}
        }
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");
    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");

    let silver = contents.lines()
        .map(|line| line.split(" ").collect::<Vec<&str>>())
        .map(|splits| (splits[0], splits[1]))
        .map(|(movement, step_string)| {
            let step_size = step_string.parse::<i32>().unwrap();
            match movement {
                "forward" => (0, step_size),
                "up" => (-step_size, 0),
                "down" => (step_size, 0),
                _ => (0, 0),
            }
        })
        .reduce(|(x1, y1), (x2, y2)| (x1 + x2, y1 + y2));

    match silver {
        Some(value) => println!("Silver: ({}, {}), {}", value.0, value.1, value.0 * value.1),
        None => println!("Failed")
    }
    
    let gold = contents.lines()
        .map(|line| line.split(" ").collect::<Vec<&str>>())
        .map(|splits| (splits[0], splits[1].parse::<i32>().unwrap()))
        .map(|(_1, _2)| Positioning::new(_1, _2))
        .reduce(|previous, current| {
            return Positioning {
                x: previous.x + current.x,
                y: previous.y + previous.aim * current.x,
                aim: previous.aim + current.aim
            }
        });

    match gold {
        Some(value) => println!("Silver: ({}, {}), {}", value.x, value.y, value.y * value.x),
        None => println!("Failed")
    }
        

}
