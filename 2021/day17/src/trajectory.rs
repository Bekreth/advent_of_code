use std::fmt::{Display, Formatter, Error};
use crate::target::Target;

pub struct Trajectory {
    pub launch: (i16, i16),
    pub target: Target,
}

impl Trajectory {
    pub fn max_y_height(self) -> i16 {
        let mut y_speed = self.launch.1;
        let mut height = 0;
        loop {
            height += y_speed;
            y_speed -= 1;
            if y_speed == 0 {
                break;
            }
        }
        height
    }
}


impl Display for Trajectory {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> { 
        let mut arc = vec![];
        let target_steps = (self.launch.1 * 2) + 2;
        let mut max_height = 0;
        let mut x_speed = self.launch.0;
        let mut y_speed = self.launch.1;
        let mut position = (0, 0);
        for i in 0..target_steps {
            position = (
                position.0 + x_speed,
                position.1 + y_speed,
            );
            if x_speed > 0 {
                x_speed -= 1;
            }
            y_speed -= 1;
            if y_speed == 0 {
                max_height = position.1;
            }
            arc.push(position.clone());
        }

        max_height += 1;

        for y in (self.target.y_bounds.0 - 1)..=max_height {
            let yy = (max_height + self.target.y_bounds.0 - 1) - y;
            write!(formatter, "{} : ", if yy < 0 {-1 * yy % 10} else { yy % 10});
            for x in 0..=(self.target.x_bounds.1 + 1) {
                let point = (x, yy);
                if point == (0, 0) {
                    write!(formatter, "S");
                } else if arc.contains(&point) {
                    write!(formatter, "#");
                } else if self.target.contains(&point) {
                    write!(formatter, "T");
                } else {
                    write!(formatter, ".");
                }
            }
            writeln!(formatter);
        }
        writeln!(formatter);
        write!(formatter, "  : ");
        for x in 0..=(self.target.x_bounds.1 + 1) {
            write!(formatter, "{}", x%10);
        }
        writeln!(formatter);


        Ok(())
    }

}
