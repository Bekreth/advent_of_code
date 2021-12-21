enum Rotate {
    PLUS_X,
    MINUX_X,
    PLUS_Y,
    MINUX_Y,
    PLUS_Z,
    MINUX_Z,
}

#[derive(Debug)]
pub struct Point {
    x: i32,
    y: i32,
    z: i32,
}

impl Point {
    pub fn new(line: &str) -> Self {
        let splits = line.split(",").collect::<Vec<&str>>();
        Point {
            x: splits[0].parse::<i32>().expect("Should parse X"),
            y: splits[1].parse::<i32>().expect("Should parse Y"),
            z: splits[2].parse::<i32>().expect("Should parse Z"),
        }
    }
}

impl Default for Point {
    fn default() -> Self {
        Point {
            x: 0,
            y: 0,
            z: 0,
        }
    }
}