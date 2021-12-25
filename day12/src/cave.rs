use std::fmt::{Display, Formatter, Error};
use regex::Regex;
use lazy_static::lazy_static;

use std::collections::HashMap;

#[derive(Debug, Hash, PartialEq, Eq, Clone, PartialOrd, Ord)]
pub enum Cave {
    Small(String),
    Large(String),
}

impl Cave {
    pub fn start() -> Self {
        Cave::Small(String::from("start"))
    }

    pub fn end() -> Self {
        Cave::Small(String::from("end"))
    }
}

impl Display for Cave {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> { 
        match self {
            Cave::Small(id) => write!(formatter, "{},", id),
            Cave::Large(id) => write!(formatter, "{},", id),
        }
    }
}

#[derive(Debug)]
pub struct CaveSystem {
    caves: HashMap<Cave, Vec<Cave>>
}

impl CaveSystem {
    pub fn new(contents: String) -> Self {
        lazy_static! {
            static ref LARGE_CAVE_1: Regex = Regex::new(r"^([A-Z]+)-")
                .expect("Should have compiled regex");
            static ref SMALL_CAVE_1: Regex = Regex::new(r"^([a-z]+)-")
                .expect("Should have compiled regex");
            static ref LARGE_CAVE_2: Regex = Regex::new(r"-([A-Z]+)$")
                .expect("Should have compiled regex");
            static ref SMALL_CAVE_2: Regex = Regex::new(r"-([a-z]+)$")
                .expect("Should have compiled regex");
        }

        let map = contents.lines()
            .map(|line| {
                let cave_1 = match LARGE_CAVE_1.captures(line) {
                    Some(cap) => Cave::Large(String::from(cap.get(1).expect("").as_str())),
                    None => {
                        match SMALL_CAVE_1.captures(line) {
                            Some(cap) => Cave::Small(String::from(cap.get(1).expect("").as_str())),
                            None => panic!("Should have found match"),
                        }
                    }
                };
                let cave_2 = match LARGE_CAVE_2.captures(line) {
                    Some(cap) => Cave::Large(String::from(cap.get(1).expect("").as_str())),
                    None => {
                        match SMALL_CAVE_2.captures(line) {
                            Some(cap) => Cave::Small(String::from(cap.get(1).expect("").as_str())),
                            None => panic!("Should have found match"),
                        }
                    }
                };
                (cave_1, cave_2)
            })
            .fold(HashMap::<Cave, Vec<Cave>>::new(), |mut acc, (cave_1, cave_2)| {
                let mut vec_1: Vec<Cave>;
                match acc.get_mut(&cave_1) {
                    Some(vec) => vec_1 = (*vec).to_vec(),
                    None => vec_1 = Vec::<Cave>::new(),
                };
                let mut vec_2: Vec<Cave>;
                match acc.get_mut(&cave_2) {
                    Some(vec) => vec_2 = (*vec).to_vec(),
                    None => vec_2 = Vec::<Cave>::new(),
                };

                if !vec_1.contains(&cave_2) { vec_1.push(cave_2.clone()) }
                if !vec_2.contains(&cave_1) { vec_2.push(cave_1.clone()) }

                acc.insert(cave_1, vec_1);
                acc.insert(cave_2, vec_2);

                acc
            })
            ;

        CaveSystem {
            caves: map,
        }
    }

    pub fn find_caves(&self, cave: &Cave) -> Vec<Cave> {
        self.caves.get(cave).expect("Unable to find cave")
            .iter()
            .filter(|c| {
                match c {
                    Cave::Small(id) => id != "start",
                    _ => true,
                }
            })
            .map(|c| c.clone())
            .collect()
    }
}

