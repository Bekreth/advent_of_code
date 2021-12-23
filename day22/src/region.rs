use lazy_static::lazy_static;
use regex::Regex;
use std::ops::RangeInclusive;
use std::collections::HashSet;
use std::cmp::{max, min};

#[derive(Debug, Clone, Copy, Eq, Hash)]
pub struct Point {
    pub coordinate: (i64, i64, i64)
}

impl PartialEq for Point {
    fn eq(&self, other: &Point) -> bool {
        self.coordinate == other.coordinate
    }
}

pub struct Region {
    pub is_on: bool,
    points: HashSet<Point>,
}

impl Default for Region {
    fn default() -> Self {
        Region {
            is_on: false,
            points: HashSet::new(),
        }
    }
}

impl  Region {
    pub fn new(line: &str, bounds: (i64, i64, i64, i64, i64, i64)) -> Self {
        lazy_static! {
            static ref SILVER: Regex = 
                Regex::new(r"^(on|off) x=(-\d+|\d+)..(-\d+|\d+),y=(-\d+|\d+)..(-\d+|\d+),z=(-\d+|\d+)..(-\d+|\d+)$")
                    .expect("Failed to parse silver regex");
        }

        let (is_on, x_range, y_range, z_range): (
            bool, 
            RangeInclusive<i64>, 
            RangeInclusive<i64>, 
            RangeInclusive<i64>,
        ) = match SILVER.captures(line) {
            Some(capture) => {
                (
                match &capture[1] {
                    "on" => true,
                    "off" => false,
                    _ => panic!("Shouldn't have failed to get on/off"),
                },

                max(capture[2].parse()
                    .expect("Failed to parse low x"), bounds.0)
                    ..=
                min(capture[3].parse()
                    .expect("Failed to parse high x"), bounds.1),

                max(capture[4].parse()
                    .expect("Failed to parse low y"), bounds.2)
                    ..=
                min(capture[5].parse()
                    .expect("Failed to parse high y"), bounds.3),

                max(capture[6].parse()
                    .expect("Failed to parse low z"), bounds.4)
                    ..=
                min(capture[7].parse()
                    .expect("Failed to parse high z"), bounds.5),
                )
            },
            None => panic!("Failed to capture regex"),
        };

        let mut points: HashSet<Point> = HashSet::new();
        for x in x_range.clone() {
            for y in y_range.clone() {
                for z in z_range.clone() {
                    points.insert(Point { coordinate: (x, y, z) });
                }
            }
        }

        Region {
            is_on: is_on,
            points: points,
        }
    }

    pub fn add(&mut self, other: Self) {
        for p in other.points {
            self.points.insert(p);
        }
    }

    pub fn remove(&mut self, other: Self) {
        for p in other.points {
            self.points.remove(&p);
        }
    }

    pub fn size(self) -> usize {
        self.points.len()
    }

}

#[cfg(test)]
mod test {
    use std::collections::HashSet;
    use region::Point;

    #[test]
    fn test_this() {
        let mut points: HashSet<Point> = HashSet::new();
    }
}