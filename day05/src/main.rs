use std::fs;
use std::env;

const MAP_SIZE: usize = 1000;

type CoordMap = [[u8; MAP_SIZE]; MAP_SIZE];

#[derive(Debug,Clone,Copy)]
struct Coordinates {
    x: i32,
    y: i32
}

impl Coordinates {
    fn new(input: &str) -> Coordinates {
        let converted: Vec<i32> = input.split(",")
            .map(|elem| elem.parse::<i32>().expect("Failed to parse"))
            .collect::<Vec<i32>>();
        Coordinates {
            x: converted[0],
            y: converted[1]
        }
    }
}

fn draw(coord1: Coordinates, coord2: Coordinates, data: &mut CoordMap) {
    if coord1.x == coord2.x {
        let y_range = if coord1.y > coord2.y { coord2.y..coord1.y + 1 } else { coord1.y..coord2.y + 1 };
        for i in y_range {
            data[coord1.x as usize][i as usize] += 1;
        }
        return
    }
    if coord1.y == coord2.y {
        let x_range = if coord1.x > coord2.x { coord2.x..coord1.x + 1 } else { coord1.x..coord2.x + 1 };
        for i in x_range {
            data[i as usize][coord1.y as usize] += 1;
        }
    }
}

fn draw_diagonal(coord1: Coordinates, coord2: Coordinates, data: &mut CoordMap) {
    if coord1.x != coord2.x && coord1.y != coord2.y {
        let x_range = if coord1.x > coord2.x { 
            let rotator = if coord1.y > coord2.y { 1 } else { -1 };
            (coord2.x, coord1.x + 1, coord2.y, rotator)
        } else { 
            let rotator = if coord1.y < coord2.y { 1 } else { -1 };
            (coord1.x, coord2.x + 1, coord1.y, rotator)
        };
        for i in x_range.0..x_range.1 {
            let step: i32 =(i - x_range.0) * x_range.3;
            let y_value: i32 = x_range.2 + step;
            data[i as usize][y_value as usize] += 1;
        }
    }
}

fn map_counter(data: &CoordMap) -> u16 {
    let mut output = 0;
    for i in 0..MAP_SIZE {
        for j in 0..MAP_SIZE {
            if data[i][j] > 1 {
                output += 1;
            }
        }
    }
    return output;
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");
    let coordinate_pairs: Vec<(Coordinates, Coordinates)> = fs::read_to_string(filename)
        .expect("Unable to read file")
        .lines()
        .map(|line| {
            let splits: Vec<&str> = line.split(" -> ").collect();
            return (
                Coordinates::new(splits[0]), 
                Coordinates::new(splits[1]),
            )
        })
        .collect();

    let silver_map = coordinate_pairs.iter()
        .fold([[0 as u8; MAP_SIZE]; MAP_SIZE], |accumulator, (coord1, coord2)| {
            let mut output = accumulator;
            draw(*coord1, *coord2, &mut output);
            return output;
        });
    let silver = map_counter(&silver_map);

    println!("Silver: {}", silver);
    
    let gold_map = coordinate_pairs.iter()
        .fold([[0 as u8; MAP_SIZE]; MAP_SIZE], |accumulator, (coord1, coord2)| {
            let mut output = accumulator;
            draw(*coord1, *coord2, &mut output);
            draw_diagonal(*coord1, *coord2, &mut output);
            return output;
        });
    let gold = map_counter(&gold_map);
    println!("Gold: {}", gold);
}
