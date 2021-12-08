use std::fs;
use std::env;

mod digits;

use digits::{Digit, get_order, get_aparent};

struct Something {

}

impl Something {
    fn new() -> Self {
        return Something{}
    }
}

fn main() {
    let mut order = get_order();
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");

    let file_data = fs::read_to_string(filename)
        .expect("Unable to read file");
    
    let silver = file_data.lines()
        .map(|line| {
            let mut splits = line.split(" | ").take(2);
            (splits.next().expect("Lead"), splits.next().expect("Follow"))
        })
        .map(|(lead, follow)| {
            (
                lead.split(" ").collect::<Vec<&str>>(),
                follow.split(" ").collect::<Vec<&str>>(),
            )
        })
        .map(|(lead, follow)| {
            let mut order = get_aparent();

            lead.iter()
                .for_each(|l| {
                    order.iter_mut().for_each(|o| {o.matches_input(l);});
                });

            let output: Vec<u8> = follow.iter().enumerate()
                .map(|(i, f)| {
                    let mut inner_out: Vec<u8> = vec![10; follow.len()];
                    for o in &order {
                        match o.check_match(f) {
                            Some(value) => {
                                inner_out[i] = value;
                                break;
                            },
                            None => ()
                        }
                    }
                    return inner_out;
                })
                .fold(vec![10; follow.len()], |acc, elem| {
                    let mut output = vec![10; follow.len()];
                    for i in 0..follow.len() {
                        if elem[i] != 10 {
                            output[i] = elem[i];
                        } else {
                            output[i] = acc[i];
                        }
                    }
                    return output;
                });
            return output;
        })
        .fold(0, |acc, elem| {
            let c = elem.iter()
                .filter(|v| {
                    return **v == 1 || 
                        **v == 4 ||
                        **v == 7 ||
                        **v == 8
                })
                .count();
            return acc + c;
        });

    println!("Silver: {}", silver);
}

/*

  0:      1:      2:      3:      4:
 aaaa    ....    aaaa    aaaa    ....
b    c  .    c  .    c  .    c  b    c
b    c  .    c  .    c  .    c  b    c
 ....    ....    dddd    dddd    dddd
e    f  .    f  e    .  .    f  .    f
e    f  .    f  e    .  .    f  .    f
 gggg    ....    gggg    gggg    ....

  5:      6:      7:      8:      9:
 aaaa    aaaa    aaaa    aaaa    aaaa
b    .  b    .  .    c  b    c  b    c
b    .  b    .  .    c  b    c  b    c
 dddd    dddd    ....    dddd    dddd
.    f  e    f  .    f  e    f  .    f
.    f  e    f  .    f  e    f  .    f
 gggg    gggg    ....    gggg    gggg

*/