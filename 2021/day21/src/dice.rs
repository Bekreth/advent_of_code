pub trait Dice {
    fn roll_thrice(&mut self) -> u16;
    fn roll_counter(&self) -> u16;
}

pub struct Deterministic {
    roll_counter: u16,
    value: u16,
}

impl Deterministic {
    pub fn new() -> Self {
        Deterministic {
            roll_counter: 0,
            value: 0,
        }
    }
}

impl Dice for Deterministic {
    fn roll_thrice(&mut self) -> u16 {
        let mut output = 0;
        for _ in 0..3 {
            self.value += 1;
            output += self.value;
            if self.value % 100 == 0{
                self.value = 0;
            }
        }
        self.roll_counter += 3;
        output
    }

    fn roll_counter(&self) -> u16 {
        self.roll_counter
    }
}