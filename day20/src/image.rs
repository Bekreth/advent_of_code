use std::fmt::{Display, Formatter, Error};
use std::str::Lines;

pub struct Image {
    processor: Vec<bool>,
    zero_value: bool,
    toggles_infinity: bool,
    data: Vec<Vec<bool>>,
}

impl Image {
    pub fn new(lines: &mut Lines<'_>) -> Self {
        let key = lines.next().expect("key");
        lines.next();

        let processor = key.chars().map(|c| {
            match c {
                '#' => true,
                '.' => false,
                _ => false,
            }
        })
        .collect::<Vec<bool>>();

        let zero_value = match key.chars().next().expect("should have gotten value") 
        {
            '#' => true,
            '.' => false,
            _ => false,
        };
        let last_value = match key.chars().last().expect("should have gotten last") {
            '#' => true,
            '.' => false,
            _ => false,
        };

        let first_line = lines.next().expect("Failed to parse");
        let width = first_line.len();

        let mut output = vec![
            vec![false; 10 + width];
            // vec![zero_value; 20 + width];
            10 + width
        ];
        first_line.chars().enumerate().for_each(|(j, c)| {
            match c {
                '#' => output[5][j + 5] = true,
                '.' => output[5][j + 5] = false,
                _ => (),
            }
        });

        lines.enumerate().for_each(|(i, line)|{
            line.chars().enumerate().for_each(|(j, c)| {
                match c {
                    '#' => output[i + 6][j + 5] = true,
                    '.' => output[i + 6][j + 5] = false,
                    _ => (),
                }
            });
        });


        Image {
            processor: processor,
            zero_value: zero_value,
            toggles_infinity: zero_value != last_value,
            data: output,
        }
    }

    pub fn iterate(&self) -> Self {

        let width = self.data.len();
        let height = self.data[0].len();

        let mut new_data = vec![
            vec![
                self.zero_value;
                // false;
                height + 2
            ];
            width + 2
        ];

        for i in 1..(width - 1) {
            for j in 1..(height - 1) {
                let index = self.calculate_index(i, j);
                // println!("x: {}, y: {}, d: {}, index: {}", i, j, self.data[i][j], index);
                new_data[i + 1][j + 1] = self.processor[index];
            }
        }

        Image {
            processor: self.processor.clone(),
            zero_value: if self.toggles_infinity { !self.zero_value } else { self.zero_value },
            toggles_infinity: self.zero_value,
            data: new_data,
        }
    }

    fn calculate_index(&self, x: usize, y: usize) -> usize {
        let mut collected: usize = 0;
        let mut counter = 8;
        for i in (x - 1)..=(x + 1) {
            for j in (y - 1)..=(y + 1) {
                if self.data[i][j] {
                    collected |= 1 << counter;
                }
                counter -= 1;
            }
        }
        collected
    }

    pub fn count(self) -> usize {
        self.data.iter()
            .map(|x| {
                x.iter().filter(|v| **v)
                    .count()
            })
            .sum()
    }

}

impl Display for Image {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> { 
        self.data.iter()
            .for_each(|v| {
                v.iter()
                    .for_each(|g| {
                        if *g {
                            write!(formatter, "#");
                        } else {
                            write!(formatter, ".");
                        }
                    });
                writeln!(formatter, "");
            });
        Ok(())
    }
}
