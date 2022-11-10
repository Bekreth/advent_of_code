use std::fmt::{Display, Formatter, Error};
use array_init::array_init;

use octopus::Octopus;

pub struct Grid {
    octopi: [[Octopus; 10]; 10],
}

impl  Grid {
    pub fn new() -> Self {
        return Grid{
            octopi: array_init(|_| {
                array_init(|_| {
                    Octopus::new()
                })
            }),
        };
    } 

    pub fn initialize_octopus(&mut self, x: usize, y: usize, number: u8) {
        self.octopi[x][y].set_energy_level(number)
    }

    pub fn run_loop(&mut self) {
        for i in 0..10 {
            for j in 0..10 {
                self.octopi[i][j].increment_energy();
            }
        } 

        loop {
            let flashes = self.octopi.iter_mut()
                .enumerate()
                .map(|(x, octopi_row)| {
                    let output: Vec<(usize, usize)> = octopi_row.iter_mut()
                        .enumerate()
                        .filter_map(|(y, octopus)| {
                            match octopus.try_flash() {
                                true => Some((x, y)),
                                false => None
                            }
                        })
                        .collect::<Vec<(usize, usize)>>();
                    return output;
                })
                .flatten()
                .collect::<Vec<(usize, usize)>>();

            if flashes.len() == 0 {
                break;
            }

            flashes.iter()
                .for_each(|(x, y)| {
                    let min_x = if *x == 0 { 0 } else { x - 1 };
                    let max_x = if *x == 9 { 10 } else { x + 2 };
                    let min_y = if *y == 0 { 0 } else { y - 1 };
                    let max_y = if *y == 9 { 10 } else { y + 2 };
                    for i in min_x..max_x {
                        for j in min_y..max_y {
                            self.octopi[i][j].counter_flase();
                        }
                    }
                });
        }

        for i in 0..10 {
            for j in 0..10 {
                self.octopi[i][j].reset();
            }
        } 
    }

    pub fn is_total_flash(&self) -> bool {
        for i in 0..10 {
            for j in 0..10 {
                if self.octopi[i][j].get_energy_level() != 0{
                    return false;
                }
            }
        } 
        return true;
    }

    pub fn get_flash_count(&self) -> u32 {
        self.octopi.iter()
            .map(|octopi_row| {
                octopi_row.iter()
                    .map(|octopus| octopus.get_flash_count())
                    .fold(0 as u32, |summer, value| summer + value as u32)
            })
            .fold(0, |summer, value| summer + value)
    }
}

impl  Display for Grid {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> { 
        for i in 0..10 {
            for j in 0..10 {
                write!(formatter, "{} ", self.octopi[i][j]);
            }
            writeln!(formatter);
        }
        writeln!(formatter);
        Ok(())
    }
}
