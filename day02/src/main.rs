use std::fmt::Error;
use std::fmt::Formatter;
use std::fmt::Display;
use std::fs;
use std::env;

struct Positioning {
    x: i32,
    y: i32,
}

impl Positioning {
    fn new(direction: &str, value: i32) -> Self {
        match direction {
            "forward" => Positioning{x: value, y: 0},
            "up" => Positioning{x: 0, y: -value},
            "down" => Positioning{x: 0, y: value},
            _ => Positioning{x: 0, y: 0}
        }
    }

    fn reduce(self, next: Positioning) -> Positioning {
        Positioning {
            x: self.x + next.x,
            y: self.y + next.y,
        }
    }
}

impl Display for Positioning {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> { 
        write!(formatter, "({}, {}) -> {}", self.x, self.y, self.x * self.y)
    }
}

struct AimPositioning {
    x: i32,
    y: i32,
    aim: i32
}

impl AimPositioning {
    fn new(direction: &str, value: i32) -> Self {
        match direction {
            "forward" => AimPositioning{x: value, y: 0, aim: 0},
            "up" => AimPositioning{x: 0, y: 0, aim: -value},
            "down" => AimPositioning{x: 0, y: 0, aim: value},
            _ => AimPositioning{x: 0, y: 0, aim: 0}
        }
    }

    fn reduce(self, next: AimPositioning) -> AimPositioning {
        AimPositioning {
            x: self.x + next.x,
            y: self.y + self.aim * next.x,
            aim: self.aim + next.aim
        }
    }
}

impl Display for AimPositioning {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> { 
        write!(formatter, "({}, {}) -> {}", self.x, self.y, self.x * self.y)
    }
}


fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");
    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");

    let silver = contents.lines()
        .map(|line| line.split(" ").collect::<Vec<&str>>())
        .map(|splits| (splits[0], splits[1].parse::<i32>().unwrap()))
        .map(|(_1, _2)| Positioning::new(_1, _2))
        .reduce(Positioning::reduce);

    match silver {
        Some(value) => println!("Silver: {}", value),
        None => println!("Failed")
    }
    
    let gold = contents.lines()
        .map(|line| line.split(" ").collect::<Vec<&str>>())
        .map(|splits| (splits[0], splits[1].parse::<i32>().unwrap()))
        .map(|(_1, _2)| AimPositioning::new(_1, _2))
        .reduce(AimPositioning::reduce);

    match gold {
        Some(value) => println!("Gold: {}", value),
        None => println!("Failed")
    }
}
