use crate::State::{Empty, Unmatched, Matched, HasMatched, OverMatched};

#[derive(Debug)]
enum State {
    Empty,
    Unmatched,
    Matched,
    HasMatched,
    OverMatched
}

struct StateMachine {
    current_state: State,
    current_value: char,
}

impl StateMachine {
    fn add_digit(&mut self, digit: char) {
        match self.current_state {
            Empty => {
                self.current_state = Unmatched;
                self.current_value = digit;
            },
            Unmatched => {
                if self.current_value == digit {
                    self.current_state = Matched;
                } else {
                    self.current_value = digit;
                }
            },
            Matched => {
                if self.current_value == digit {
                    self.current_state = OverMatched;
                } else {
                    self.current_state = HasMatched;
                }
            },
            HasMatched => (),
            OverMatched => {
                if self.current_value != digit {
                    self.current_state = Unmatched;
                    self.current_value = digit;
                }
            },
        }
    }

    fn terminate(&self) -> bool {
        match self.current_state {
            HasMatched => true,
            Matched => true,
            _ => false
        }
    }
}


fn main() {
    let minimum = 264793;
    let maximum = 803935;

    let silver_collection = silver(minimum, maximum);
    println!("{}", silver_collection.len());
    println!("=====");
    let gold_collection = gold(minimum, maximum);
    println!("{:?}", gold_collection.len())
}

fn silver(minimum: i32, maximum: i32) -> Vec<i32> {
    println!("Silver");
    let range = minimum..maximum;
    return range.filter(strictly_increasing)
        .filter(contains_double)
        .collect();
}

fn gold(minimum: i32, maximum: i32) -> Vec<i32> {
    println!("Gold");
    let range = minimum..maximum;
    return range.filter(strictly_increasing)
        .filter(run_state_machine)
        .collect();
}

fn strictly_increasing(input: &i32) -> bool{
    let string_rep = input.to_string();
    for i in 0..(string_rep.len() - 1) {
        let i_1 = string_rep.chars().nth(i).unwrap();
        let i_2 = string_rep.chars().nth(i + 1).unwrap();
        if i_1 > i_2 {
            return false;
        }
    }
    true
}

fn contains_double(input: &i32) -> bool {
    let string_rep = input.to_string();
    for i in 0..(string_rep.len() - 1) {
        let i_1 = string_rep.chars().nth(i).unwrap();
        let i_2 = string_rep.chars().nth(i + 1).unwrap();
        if i_1 == i_2 {
            return true;
        }
    }
    false
}

fn run_state_machine(input: &i32) -> bool {
    let mut state_machine = StateMachine {
        current_value: '0',
        current_state: Empty,
    };
    for c in input.to_string().chars() {
        state_machine.add_digit(c);
    }
    return state_machine.terminate();
}





