use std::fmt::{Display, Formatter, Error};
use cave::{Cave, CaveSystem};
use Walker;

#[derive(Clone, Ord, PartialOrd, Eq, PartialEq)]
pub struct SilverWalker {
    current_cave: Cave,
    previously_visited: Vec<Cave>,
}

impl SilverWalker {
    pub fn new() -> Self {
        let starting_cave = Cave::start();
        SilverWalker {
            current_cave: starting_cave.clone(),
            previously_visited: vec![],
        }
    }
}

impl Walker for SilverWalker {
    fn possible_next_steps(&self, cave_system: &CaveSystem) -> Vec<Self> {
        cave_system.find_caves(&self.current_cave)
            .iter()
            .filter(|adjacent| {
                match adjacent {
                    Cave::Small(_) => !self.previously_visited.contains(adjacent),
                    Cave::Large(_) => true,
                }
            })
            .map(|cave| {
                let mut output = self.clone();
                output.previously_visited.push(self.current_cave.clone());
                output.current_cave = cave.clone();
                output
            })
            .collect::<Vec<SilverWalker>>()
    }

    fn finished(&self) -> bool {
        self.current_cave == Cave::end()
    }

    fn previously_visited(&self) -> Vec<Cave> {
        self.previously_visited.clone()
    }
}

impl Display for SilverWalker {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> { 
        self.previously_visited
            .iter()
            .for_each(|visited| {
                write!(formatter, "{} ", visited);
            });
        write!(formatter, "end");
        Ok(())
    }
}
