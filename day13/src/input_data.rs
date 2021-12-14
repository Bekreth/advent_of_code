use lazy_static::lazy_static;
use regex::Regex;

#[derive(Debug)]
pub enum InputData {
    Point(u16, u16),
    FoldX(u16),
    FoldY(u16),
}

impl InputData {
    pub fn new(line: &str) -> Option<Self> {
        lazy_static! {
            static ref POINT_REGEX: Regex = Regex::new(r"^(\d+),(\d+)$")
                .expect("Failed to parse point regex");
            static ref FOLD_REGEX: Regex = Regex::new(r"^fold along ([xy])=(\d+)$")
                .expect("Failed to parse point regex");
        }

        match POINT_REGEX.captures(line) {
            Some(capture) => Some(InputData::Point(
                capture[1].parse().expect("couldn't parse X"),
                capture[2].parse().expect("couldn't parse Y"),
            )),
            None => {
                match FOLD_REGEX.captures(line) {
                    Some(capture) => {
                        let value: u16 = capture[2].parse().expect("Failed to parse fold value");
                        if capture[1] == *"x" {
                            Some(InputData::FoldX(value))
                        } else {
                            Some(InputData::FoldY(value))
                        }
                    },
                    None => None
                }
            }
        }
    }
}
