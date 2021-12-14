use std::fs;
use std::env;


const OPENING: [char; 4] = ['{', '[', '(', '<'];
// const CLOSING: [char; 4] = ['}', ']', ')', '>'];

#[derive(Clone)]
enum Either {
    Left(Vec<char>),
    Right(Vec<char>, char),
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename = args.get(1).expect("missing filename");

    let content = fs::read_to_string(filename)
        .expect("failed to read file");

    let mut parsed_data: Vec<Either> = content.lines()
        .map(|line| {
            let mut stack = vec![];
            for c in line.chars() {
                if OPENING.contains(&c) {
                    stack.push(c);
                } else {
                    let previous = stack.pop().expect("expected a pop");
                    let matches = match (previous, c) {
                        ('[', ']') => true,
                        ('(', ')') => true,
                        ('{', '}') => true,
                        ('<', '>') => true,
                        _ => false,
                    };
                    if !matches {
                        stack.push(previous);
                        return Either::Right(stack, c)
                    }
                }
            }
            return Either::Left(stack)
        })
        .collect();
    
    let silver: u32 = parsed_data.iter_mut()
        .filter_map(|v| {
            match v {
                Either::Left(_) => None,
                Either::Right(stack, c) => Some((stack, c))
            }
        })
        .map(|(_, c)| {
            match c {
                ')' => 3,
                ']' => 57,
                '}' => 1197,
                '>' => 25137,
                _ => 0
            }
        })
        .sum();
    println!("Silver: {}", silver);

    let mut gold_candidates: Vec<u64> = parsed_data.iter_mut()
        .filter_map(|v| {
            match v {
                Either::Left(stack) => Some(stack),
                Either::Right(_, _) => None,
            }
        })
        .map(|stack| {
            let mut closing_bracket: Vec<char> = vec![];
            loop {
                match stack.pop() {
                    Some(c) => match c {
                        '[' => (closing_bracket.push(']')),
                        '(' => (closing_bracket.push(')')),
                        '{' => (closing_bracket.push('}')),
                        '<' => (closing_bracket.push('>')),
                        _ => (),
                    }
                    None => return closing_bracket,
                }
            }
        })
        .map(|stack| {
            let mut output: u64 = 0;
            for c in stack {
                output *= 5;
                let next_step = match c {
                    ')' => 1,
                    ']' => 2,
                    '}' => 3,
                    '>' => 4,
                    _ => 0
                };
                output += next_step;
            }
            return output;
        })
        .collect::<Vec<u64>>();
    gold_candidates.sort();
    println!("Gold: {}", gold_candidates[gold_candidates.len() / 2]);
}
