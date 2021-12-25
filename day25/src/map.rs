use std::fmt::{Display, Formatter, Error};
use std::collections::HashSet;

#[derive(PartialEq, Eq)]
enum Space {
    East,
    South,
    Empty
}

pub struct Map {
    width: usize,
    height: usize,
    east_cucumbers: HashSet<(usize, usize)>,
    south_cucumbers: HashSet<(usize, usize)>,
}

impl Map {
    pub fn new(contents: String) -> Self {
        let height = contents.lines().count();
        let width = contents.lines().next()
            .expect("unexpected failure")
            .chars()
            .count();
        let mut east_cucumbers: HashSet<(usize, usize)> = HashSet::new();
        let mut south_cucumbers: HashSet<(usize, usize)> = HashSet::new();
        contents.lines()
            .enumerate()
            .for_each(|(y, line)| {
                line.chars()
                    .enumerate()
                    .for_each(|(x, c)| {
                        match c {
                            '>' => east_cucumbers.insert((x, y)),
                            'v' => south_cucumbers.insert((x, y)),
                            _ => true,
                        };
                    });
            });
        Map {
            height: height,
            width: width,
            east_cucumbers: east_cucumbers,
            south_cucumbers: south_cucumbers,
        }
    }

    pub fn move_until_unable(&mut self) -> u32 {
        let mut step_counter = 0; 
        println!("{}", self);
        loop {
            let e_moves = self.move_east_cucumbers();
            let s_moves = self.move_south_cucumbers(); 
            step_counter += 1;
            if e_moves == 0 && s_moves == 0 {
                break;
            }
        }
        println!("{}", self);
        step_counter
    }

    fn move_east_cucumbers(&mut self) -> u32{
        let reference = self.east_cucumbers.clone();
        let mut moves = 0;
        reference.iter()
            .filter_map(|(x, y)| {
                let next_pos = if x + 1 == self.width {
                    (0, *y)
                } else {
                    (x + 1, *y)
                };
                if !reference.contains(&next_pos) 
                    && !self.south_cucumbers.contains(&next_pos) {
                    Some(((*x, *y), next_pos))
                } else {
                    None
                }
            })
            .for_each(|(remove, add)| {
                moves += 1;
                self.east_cucumbers.remove(&remove);
                self.east_cucumbers.insert(add);
            });
        moves
    }

    fn move_south_cucumbers(&mut self) -> u32 {
        let reference = self.south_cucumbers.clone();
        let mut moves = 0;
        reference.iter()
            .filter_map(|(x, y)| {
                let next_pos = if y + 1 == self.height {
                    (*x, 0)
                } else {
                    (*x, y + 1)
                };
                if !reference.contains(&next_pos) 
                    && !self.east_cucumbers.contains(&next_pos) {
                    Some(((*x, *y), next_pos))
                } else {
                    None
                }
            })
            .for_each(|(remove, add)| {
                moves += 1;
                self.south_cucumbers.remove(&remove);
                self.south_cucumbers.insert(add);
            });
        moves
    }
}

impl  Display for Map {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> { 
        for i in 0..=self.height {
            for j in 0..=self.width {
                if self.east_cucumbers.contains(&(j, i)) {
                    write!(formatter, ">");
                } else if self.south_cucumbers.contains(&(j, i)) {
                    write!(formatter, "v");
                } else {
                    write!(formatter, ".");
                }
            }
            writeln!(formatter);
        }
        writeln!(formatter);
        Ok(())
    }
}
