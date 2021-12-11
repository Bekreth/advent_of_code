use std::fmt::{Display, Formatter, Error};

pub struct Octopus {
    energy_level: u8,
    has_flashed: bool
}

impl Octopus {
    pub fn new() -> Self {
        return Octopus{
            energy_level: 0,
            has_flashed: false
        };
    }

    pub fn set_energy_level(&mut self, energy_level: u8) {
        self.energy_level = energy_level;
    }

    pub fn counter_flase(&mut self) {
        if !self.has_flashed {
            self.energy_level += 1;
        }
    }

    pub fn try_falsh(&mut self) -> bool {
        if self.has_flashed {
            return false;
        }
        if self.energy_level > 9 {
            self.energy_level = 0;
            return true;
        }
        return false;
    }

    pub fn increment_energy(&mut self) {
        self.energy_level += 1;
    }
}

impl Display for Octopus {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> { 
        write!(formatter, "{}", self.energy_level);
        Ok(())
    }
}

