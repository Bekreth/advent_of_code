use std::fs;
use std::env;

fn count_occurance(vector: &Vec<u16>) -> Vec<i32> {
    vector.iter().map(|b| {
        let mut output = vec![0; 16];
        for i in 0..16 {
            let shift = 1 << (15 - i);
            if b & shift > 0 {
                output[i] = 1;
            } else {
                output[i] = -1;
            }
        }
        output
    })
    .reduce(|b1: Vec<i32>, b2: Vec<i32>| {
        let mut output = vec![0; b1.len()];
        for (i, _) in b1.iter().enumerate() {
            output[i] = b1[i] + b2[i];
        }
        return output;
    }).expect("Failed to count")
}

fn calculate_mask(vector: &[i32]) -> (u16, u16) {
    let mut gamma: u16 = 0;
    let mut epsilon: u16 = 0;
    for i in 0..31 {
        let shift = 1 << vector.len() -1 - i;
        if vector[i] > 0 {
            gamma |= shift;
        } else if vector[i] < 0 {
            epsilon |= shift;
        } else {
            gamma |= shift;
            epsilon |= shift;
        }
        if i == vector.len() - 1 {
            break;
        }
    }
    return (gamma, epsilon);
}

fn fileter_bin(
    bin_lines: &Vec<u16>,
    bit_width: usize, 
    bit_count: u8,
    high_side: bool
) -> u16 {
    if bin_lines.len() <= 1 { return bin_lines[0]}
    let expectation: u16 = 1 << bit_width - 1 - bit_count as usize;
    let (high, low) = calculate_mask(&count_occurance(bin_lines));
    let mask = if high_side {high} else {low};
    let filtered_lines = bin_lines.iter()
        .filter(|line| {
            let xnor = !(*line ^ mask);
            let and = expectation & xnor;
            return and > 0;
        })
        .map(|b| *b)
        .collect::<Vec<u16>>();

    return fileter_bin(
        &filtered_lines, 
        bit_width,
        bit_count + 1, 
        high_side,
    )
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");

    let bin_lines = fs::read_to_string(filename)
        .expect("Unable to read file")
        .lines()
        .map(|line| isize::from_str_radix(line, 2).unwrap() as u16)
        .collect::<Vec<u16>>();
    let bin_width = fs::read_to_string(filename)
        .expect("Unable to read file")
        .lines()
        .next()
        .expect("msg: &str")
        .len();
    
    let occurances = count_occurance(&bin_lines);
    let (_, counts) = occurances.split_at(16 - bin_width);
    let (gamma, epsilon): (u16, u16) = calculate_mask(counts);

    println!("Silver: g - {} e - {} p - {}", 
        gamma, epsilon, gamma as u32 * epsilon as u32);

    let oxygen = fileter_bin(&bin_lines, bin_width, 0, true);
    let co2 = fileter_bin(&bin_lines, bin_width, 0, false);
    
    println!("Gold: o - {} x - {} p - {}",
        oxygen, co2, oxygen as u32 * co2 as u32);
}