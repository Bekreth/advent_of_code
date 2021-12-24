use cave::{Cave, CaveSystem};


pub trait Walker : Sized {
    fn possible_next_steps(&self, cave_system: &CaveSystem) -> Vec<Self>;
    fn finished(&self) -> bool;
}

#[derive(Clone)]
pub struct SilverWalker {
    current_cave: Cave,
    previously_visited: Vec<Cave>,
}

impl SilverWalker {
    pub fn new() -> Self {
        let starting_cave = Cave::start();
        SilverWalker {
            current_cave: starting_cave.clone(),
            previously_visited: vec![starting_cave],
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
}