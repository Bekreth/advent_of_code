
pub struct Target {
    pub x_bounds: (i16, i16),
    pub y_bounds: (i16, i16),
}

pub const SAMPLE: Target = Target {
    x_bounds: (20, 30),
    y_bounds: (-10, -5),
};

pub const INPUT: Target = Target {
    x_bounds: (32, 65),
    y_bounds: (-225, -177),
};

impl Target {
    pub fn minimum_x(&self) -> i16 {
        let mut limit = 0;
        let mut counter = 1;
        loop {
            if limit >= self.x_bounds.0 {
                break;
            }
            limit += counter;
            counter += 1;
        }
        counter
    }

    pub fn calculate_max_x(&self, y_speed: i16) -> i16 {
        let target_steps = (y_speed * 2) + 2;

        let mut best_solution = 0;
        for i in (self.minimum_x() - 1)..=self.x_bounds.1 {
            let mut x_speed = i;
            let mut total_distance = 0;
            for j in 0..target_steps {
                if x_speed > 0 {
                    total_distance += x_speed;
                    x_speed -= 1;
                }
                if total_distance > self.x_bounds.1 {
                    break;
                }
            }
            if total_distance > self.x_bounds.1 {
                continue;
            }
            if i > best_solution {
                best_solution = i;
            }
        }

        best_solution
    }

    pub fn calculate_max_y(&self) -> i16 {
        (self.y_bounds.0 * -1) - 1
    }

    pub fn contains(&self, point: &(i16, i16)) -> bool {
        if point.0 >= self.x_bounds.0 && point.0 <=self.x_bounds.1  {
            if point.1 >= self.y_bounds.0 && point.1 <= self.y_bounds.1 {
                return true;
            }
        }
        false
    }

    fn calculate_step_count(&self, mut x_speed: i16) -> (usize, usize) {
        let mut x_position = 0;
        let mut step_min: usize = 0;
        let mut step: usize = 0;
        loop {
            if x_position > self.x_bounds.1 {
                break;
            }
            if x_speed == 0 {
                step = usize::MAX;
                break;
            }
            if step_min == 0 && x_position >= self.x_bounds.0 {
                step_min = step;
            }
            x_position += x_speed;
            x_speed -= 1;
            step += 1;
        }
        (step_min, step)
    }
}