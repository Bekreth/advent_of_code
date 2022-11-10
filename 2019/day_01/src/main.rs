use std::fs::File;
use std::io::Read;

fn main() {
    silver();
    println!("=======");
    gold();
}

fn silver() {
    println!("Silver");
    let fuel_requirement: i64 = read_input_file(&String::from("input.txt"))
        .split("\n")
        .map(|line| String::from(line))
        .map(get_module_mass)
        .map(calculate_fuel_requirements)
        .sum();

    println!("{:?}", fuel_requirement);
}

fn gold() {
    println!("Gold");
    let fuel_requirement: i64 = read_input_file(&String::from("input.txt"))
        .split("\n")
        .map(|line| String::from(line))
        .map(get_module_mass)
        .map(calculate_fuel_requirements)
        .map(compensate_for_fuel)
        .sum();

    println!("{:?}", fuel_requirement);
}

fn read_input_file(file_name: &String) -> String {
    let mut file = File::open(file_name).expect("Failed to read data");
    let mut file_contents = String::new();
    file.read_to_string(&mut file_contents).expect("Failed to read data");
    return file_contents
}

fn get_module_mass(module_size: String) -> i64 {
    let line_mass: i64 = module_size.parse().unwrap();
    return line_mass;
}

fn calculate_fuel_requirements(module_mass: i64) -> i64 {
    let x = module_mass / 3;
    return x - 2;
}

fn compensate_for_fuel(fuel_weight: i64) -> i64 {
    let additional_fuel = calculate_fuel_requirements(fuel_weight);
    if additional_fuel <= 0 {
        return fuel_weight
    } else {
        return fuel_weight + compensate_for_fuel(additional_fuel)
    }
}
