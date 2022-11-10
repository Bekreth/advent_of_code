use std::fmt::{Display, Formatter, Error};

pub struct Octopus {
    energy_level: u8,
    has_flashed: bool,
    flash_count: u16,
}

impl Octopus {
    pub fn new() -> Self {
        return Octopus{
            energy_level: 0,
            has_flashed: false,
            flash_count: 0,
        };
    }

    pub fn get_energy_level(&self) -> u8 {
        self.energy_level
    }

    pub fn set_energy_level(&mut self, energy_level: u8) {
        self.energy_level = energy_level;
    }

    pub fn counter_flase(&mut self) {
        if !self.has_flashed {
            self.energy_level += 1;
        }
    }

    pub fn try_flash(&mut self) -> bool {
        if self.has_flashed {
            return false;
        }
        if self.energy_level > 9 {
            self.has_flashed = true;
            self.energy_level = 0;
            self.flash_count += 1;
            return true;
        }
        return false;
    }
    pub fn reset(&mut self) {
        self.has_flashed = false;
    }

    pub fn increment_energy(&mut self) {
        self.energy_level += 1;
    }

    pub fn get_flash_count(&self) -> u16 {
        return self.flash_count;
    }
}

impl Display for Octopus {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> { 
        write!(formatter, "{}", self.energy_level);
        Ok(())
    }
}

