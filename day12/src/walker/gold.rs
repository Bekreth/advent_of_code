use cave::{Cave, CaveSystem};
use Walker;

use std::fmt::{Display, Formatter, Error};

#[derive(Clone)]
pub struct GoldWalker {
    visit_twice: Option<(Cave, bool)>,
    current_cave: Cave,
    previously_visited: Vec<Cave>,
}

impl GoldWalker {
    pub fn new() -> Self {
        let starting_cave = Cave::start();
        GoldWalker {
            visit_twice: None,
            current_cave: starting_cave.clone(),
            previously_visited: vec![],
        }
    }

    fn this_next_steps(&self, caves: &Vec<Cave>) -> Vec<Self> {
        caves.iter()
            .filter(|adjacent| {
                match adjacent {
                    Cave::Large(_) => true,
                    Cave::Small(_) => {
                        match self.visit_twice.clone() {
                            Some((cave, has_visited)) => {
                                if has_visited {
                                    !self.previously_visited.contains(adjacent)
                                } else {
                                    if cave == **adjacent {
                                        true
                                    } else {
                                        !self.previously_visited.contains(adjacent)
                                    }
                                }
                            },
                            None => !self.previously_visited.contains(adjacent), 
                        }
                    },
                }
            })
            .map(|cave| {
                let mut output = self.clone();
                output.previously_visited.push(self.current_cave.clone());
                output.current_cave = cave.clone();
                if output.visit_twice == Some((cave.clone(), false)) {
                    output.visit_twice = Some((cave.clone(), true));
                }
                output
            })
            .collect::<Vec<GoldWalker>>()
    }
}

impl Walker for GoldWalker {
    fn possible_next_steps(&self, cave_system: &CaveSystem) -> Vec<Self> {
        let mut walkers = vec![self.clone()];
        if self.visit_twice.is_none() {
            match self.current_cave.clone() {
                Cave::Large(_) => (),
                Cave::Small(id) => {
                    if id != "start" {
                        let mut extra_walker = self.clone();
                        extra_walker.visit_twice = Some((extra_walker.current_cave.clone(), false));
                        walkers.push(extra_walker);
                    }
                },
            }
        }

        let caves = cave_system.find_caves(&self.current_cave);

        walkers.iter()
            .map(|w| w.this_next_steps(&caves))
            .flatten()
            .collect::<Vec<GoldWalker>>()
    }
    
    fn finished(&self) -> bool {
        self.current_cave == Cave::end()
    }

    fn previously_visited(&self) -> Vec<Cave> {
        self.previously_visited.clone()
    }
}

impl Display for GoldWalker {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> { 

        self.previously_visited
            .iter()
            .for_each(|visited| {
                write!(formatter, "{}", visited);
            });
        write!(formatter, "end");
        // writeln!(formatter, "\t\t\t\tposition: {:?}", self.current_cave);
        // write!(formatter, "\t\t\t\tdoubled: {:?}", self.visit_twice);
        Ok(())
    }
}
