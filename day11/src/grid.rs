use std::fmt::{Display, Formatter, Error};
use array_init::array_init;

use octopus::Octopus;

fn max(i: usize, j: usize) -> usize {
    if i > j { i }
    else { j }
}

fn min(i: usize, j: usize) -> usize {
    if i < j { i }
    else { j }
}

pub struct Grid<'a> {
    octopi: [[&'a mut Octopus; 10]; 10]
}

impl <'a> Grid<'a> {
    pub fn new() -> Self {
        todo!()
        /*
        return Grid{
            octopi: array_init(|_| {
                array_init(|_| {
                    &Octopus::new()
                })
            }),
        };
    */
    } 

    pub fn initialize_octopus(self, x: usize, y: usize, number: u8) {
        self.octopi[x][y].set_energy_level(number)
    }

    pub fn run_loop(&mut self) {
        for i in 0..10 {
            for j in 0..10 {
                self.octopi[i][j].increment_energy();
                self.octopi[i][j].try_falsh();
            }
        } 

        loop {
            let flashes = self.octopi.iter()
                .enumerate()
                .map(|(x, octopi_row)| {
                    let output: Vec<(usize, usize)> = octopi_row.iter()
                        .enumerate()
                        .filter(|(_, octopus)| octopus.try_falsh())
                        .map(|(y, _)| (x, y))
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
                    for i in min(0, x - 1)..max(10, x + 1) {
                        for j in min(0, y - 1)..max(10, y + 1) {
                            self.octopi[i][j].counter_flase();
                        }
                    }
                });
        }
    }
}

impl  Display for Grid<'_> {
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
