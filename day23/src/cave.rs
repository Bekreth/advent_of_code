use std::collections::HashSet;

const SAMPLE: Cave = Cave {
    energy_spent: 0,
    position: [
        (Amphipods::B, Space::A0),
        (Amphipods::A, Space::A1),

        (Amphipods::C, Space::B0),
        (Amphipods::D, Space::B1),

        (Amphipods::B, Space::C0),
        (Amphipods::C, Space::C1),

        (Amphipods::D, Space::D0),
        (Amphipods::A, Space::D1),
    ],
};

const INPUT: Cave = Cave {
    energy_spent: 0,
    position: [
        (Amphipods::B, Space::A0),
        (Amphipods::C, Space::A1),

        (Amphipods::B, Space::B0),
        (Amphipods::A, Space::B1),

        (Amphipods::D, Space::C0),
        (Amphipods::D, Space::C1),

        (Amphipods::A, Space::D0),
        (Amphipods::C, Space::D1),
    ],
};


#[derive(Debug, Copy, Clone, PartialEq, Eq, Hash)]
pub enum Space {
    S0, S1, 
    S3, S5, S7, 
    S9, S10,

    A0, A1,
    B0, B1,
    C0, C1,
    D0, D1,
}

impl Space {
    pub fn space_set() -> HashSet<Self> {
        HashSet::from([
            Space::S0,
            Space::S1,
            Space::S3,
            Space::S5,
            Space::S7,
            Space::S9,
            Space::S10,

            Space::A0, Space::A1,
            Space::B0, Space::B1,
            Space::C0, Space::C1,
            Space::D0, Space::D1,
        ])
    } 
}

enum Amphipods {
    A, B, C, D
}

struct Cave {
    energy_spent: u64,
    position: [(Amphipods, Space);8],
}

impl Cave {
    fn final_position(&self) -> bool {
        self.position.iter()
            .filter(|p| {
                match p {
                    (Amphipods::A, Space::A0) => false,
                    (Amphipods::A, Space::A1) => false,
                    (Amphipods::B, Space::B0) => false,
                    (Amphipods::B, Space::B1) => false,
                    (Amphipods::C, Space::C0) => false,
                    (Amphipods::C, Space::C1) => false,
                    (Amphipods::D, Space::D0) => false,
                    (Amphipods::D, Space::D1) => false,
                    (_, _) => true,
                }
            })
            .count() == 0
    }
}

#[cfg(test)]
mod tests {
    use cave::{Amphipods, Space, Cave};

    #[test]
    fn test_known_completion() {
        let finished_cave = Cave {
            energy_spent: 0,
            position: [
                (Amphipods::A, Space::A0),
                (Amphipods::A, Space::A1),
                (Amphipods::B, Space::B0),
                (Amphipods::B, Space::B1),
                (Amphipods::C, Space::C0),
                (Amphipods::C, Space::C1),
                (Amphipods::D, Space::D0),
                (Amphipods::D, Space::D1),
            ],
        };
        assert_eq!(true, finished_cave.final_position());

        let not_finished_cave = Cave {
            energy_spent: 0,
            position: [
                (Amphipods::A, Space::S0),
                (Amphipods::A, Space::S1),
                (Amphipods::B, Space::B0),
                (Amphipods::B, Space::B1),
                (Amphipods::C, Space::C0),
                (Amphipods::C, Space::C1),
                (Amphipods::D, Space::D0),
                (Amphipods::D, Space::D1),
            ],
        };
        assert_eq!(false, not_finished_cave.final_position());
    }
}


/* 

01234567890
  a b c d
  A B C D

*/

/* 

01X3X5X7X90
  a X X X
  A X X X

*/