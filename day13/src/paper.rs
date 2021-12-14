use input_data::{InputData};
use std::fmt::{Display, Formatter, Error};

pub struct Paper {
    dot_list: Vec<(u16, u16)>,
    fold_count: u8
}

fn reflected_value(input: u16, hinge_point: u16) -> u16 { 
    let minor_point = input - hinge_point;
    hinge_point - minor_point
}

impl Paper {
    pub fn new() -> Self {
        return Paper {
            dot_list: vec![],
            fold_count: 0
        }
    }

    pub fn handle_input_data(&mut self, input: InputData) {
        match input {
            InputData::Point(x, y) => self.dot_list.push((x, y)),
            InputData::FoldX(x) => {
                self.fold_count += 1;
                let new_list: Vec<(u16, u16)> = self.dot_list
                    .iter()
                    .map(|point| {
                        if point.0 > x {
                            (reflected_value(point.0, x), point.1)
                        } else {
                            *point
                        }
                    })
                    .fold(vec![], |mut acc, point| {
                        if !acc.contains(&point) {
                            acc.push(point);
                        }
                        acc
                    });
                self.dot_list = new_list;
            },
            InputData::FoldY(y) => {
                self.fold_count += 1;
                let new_list: Vec<(u16, u16)> = self.dot_list
                    .iter()
                    .map(|point| {
                        if point.1 > y {
                            (point.0, reflected_value(point.1, y))
                        } else {
                            *point
                        }
                    })
                    .fold(vec![], |mut acc, point| {
                        if !acc.contains(&point) {
                            acc.push(point);
                        }
                        acc
                    });
                self.dot_list = new_list;            
            }
        }
        if self.fold_count == 1 {
            println!("Silver: {}", self.dot_list.len());
        }
    }
}

impl Display for Paper {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> { 
        let mut max_x: u16 = 0;
        let mut max_y: u16 = 0;
        self.dot_list.iter().for_each(|(x, y)| {
            if *x > max_x {max_x = *x}
            if *y > max_y {max_y = *y}
        });
        max_x += 1;
        max_y += 1;
        let mut output: Vec<Vec<bool>> = vec![vec![false; max_y as usize]; max_x as usize];
        self.dot_list.iter()
            .map(|(x, y)| (*x as usize, *y as usize))
            .for_each(|(x, y)| output[x][y] = true);

        writeln!(formatter);
        for i in 0..max_x {
            for j in 0..max_y {
                let value = if output[i as usize][j as usize] {
                    "#"
                } else {
                    "."
                };
                write!(formatter,  "{}", value);
            }
            writeln!(formatter);
        }
        Ok(())
    }
}