mod target;
mod trajectory;

use crate::target::{Target, SAMPLE, INPUT};
use crate::trajectory::Trajectory;

use std::env;
use std::fs;

fn main() {
    let args: Vec<String> = env::args().collect();
    let runtime =args.get(1).expect("missing filename");
    let target: Target = match runtime.as_str() {
        "sample" => SAMPLE,
        "input" => INPUT,
        _ => panic!("nope"),
    };

    let silver_y = target.calculate_max_y();
    let silver_x = target.calculate_max_x(silver_y);
    let tra = Trajectory {
        launch: (silver_x, silver_y),
        target: target,
    };
    // println!("{}", tra);
    println!("Silver: ({}, {}), height {}", silver_x, silver_y, tra.max_y_height());
}
