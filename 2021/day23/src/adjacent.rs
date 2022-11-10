use crate::cave::Space;
use std::collections::HashMap;

/*
S0 S1    S3    S5    S7    S9 S10
      A0    B0    C0    D0
      A1    B1    C1    D1
*/
const ADJACENT: [(Space, Space, u8); 18] = [
    (Space::S0, Space::S1, 1),

    (Space::S1, Space::S3, 2),
    (Space::S1, Space::A0, 2),

    (Space::A0, Space::A1, 1),
    (Space::A0, Space::S3, 2),

    (Space::S3, Space::S5, 2),
    (Space::S3, Space::B0, 2),

    (Space::B0, Space::B1, 1),
    (Space::B0, Space::S5, 2),

    (Space::S5, Space::S7, 2),
    (Space::S5, Space::C0, 2),

    (Space::C0, Space::C1, 1),
    (Space::C0, Space::S7, 2),

    (Space::S7, Space::S9, 2),
    (Space::S7, Space::D0, 2),

    (Space::D0, Space::D1, 1),
    (Space::D0, Space::S9, 2),

    (Space::S9, Space::S10, 1),
];

#[derive(Debug)]
struct MoveNetwork {
    move_cost: HashMap<Space, u8>,
}

impl MoveNetwork {
    fn new(starting_space: Space) -> Self {
        let mut move_cost = HashMap::<Space, u8>::new();
        let mut leading_edge = vec![(starting_space, 0)];
        while leading_edge.len() != 0 {
            let current_space = leading_edge.pop().expect("Should have gotten the value");
            match move_cost.get(&current_space.0) {
                None => move_cost.insert(current_space.0, current_space.1),
                Some(current_step_value) => {
                    if current_space.1 < *current_step_value {
                        move_cost.insert(current_space.0, current_space.1);
                    } else {
                        continue;
                    }
                    None
                },
            };
            ADJACENT.iter()
                .for_each(|(s1, s2, v)| {
                    if *s1 == current_space.0 {
                        leading_edge.push((*s2, v + current_space.1))
                    } else if *s2 == current_space.0 {
                        leading_edge.push((*s1, v + current_space.1))
                    }
                });

        }
        MoveNetwork {
            move_cost: move_cost,
        }
    }
}

struct StepCounter {
    move_cost: HashMap<Space, MoveNetwork>,
}

impl StepCounter {
    pub fn new() -> Self {
        StepCounter {
            move_cost: Space::space_set().iter()
                .fold(HashMap::<Space, MoveNetwork>::new(), |mut acc, space| {
                    acc.insert(*space, MoveNetwork::new(*space));
                    acc
                }),
        }
    }

    pub fn count_steps(&self, from: Space, to: Space) -> u8 {
        let move_network = self.move_cost.get(&from)
            .expect("Shouldn't have failed looking up move network");

        *move_network.move_cost.get(&to)
            .expect("Shouldn't have failed to get move value")
    }
}


#[cfg(test)]
mod tests {
    use adjacent::{StepCounter, MoveNetwork};
    use cave::Space;

    #[test]
    fn test_move_network() {
        let move_network = MoveNetwork::new(Space::S0);
        println!("{:?}", move_network);

        assert_eq!(Some(&7), move_network.move_cost.get(&Space::S7))
    }

    #[test]
    fn test_step_counter() {
        let step_counter = StepCounter::new();

        assert_eq!(0, step_counter.count_steps(Space::C1, Space::C1));
        assert_eq!(1, step_counter.count_steps(Space::C1, Space::C0));
        assert_eq!(7, step_counter.count_steps(Space::S0, Space::S7));
        assert_eq!(10, step_counter.count_steps(Space::D1, Space::S0));
        assert_eq!(9, step_counter.count_steps(Space::D1, Space::A0));
    }
}