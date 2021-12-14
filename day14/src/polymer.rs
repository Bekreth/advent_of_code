use insertion_set::InsertionSet;

use std::fmt::{Display, Formatter, Error};
use std::vec;

pub struct PolymerChain {
    chain: Vec<char>,
}

impl PolymerChain {
    pub fn new(line: &str) -> Self {
        PolymerChain {
            chain: line.chars()
                .collect::<Vec<char>>(),
        }
    }

    pub fn insert(&mut self, rules: &InsertionSet) {
        let mut next_chain = vec![];
        for i in 1..self.chain.len() {
            let pair = [self.chain[i - 1], self.chain[i]];
            next_chain.push(pair[0]);
            match rules.insertion_rule
                .iter()
                .find(|(rule, _)| pair == *rule) 
            {
                Some((_, value)) => next_chain.push(*value),
                None => ()
            }
        }
        let final_char = self.chain.last().expect("Should'a gotten last");
        next_chain.push(*final_char);
        self.chain = next_chain;
    }
}

impl Display for PolymerChain {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> {
        let mut counter: [u16; 26] = [0; 26];
        self.chain.iter()
            .map(|c| {
                let mut v = [0 as u8];
                c.encode_utf8(&mut v);
                v[0] -= 65;
                return v;
            })
            .for_each(|v| counter[v[0] as usize] += 1);

        counter.sort();
        let least = counter.iter()
            .filter(|v| **v > 0)
            .take(1)
            .next()
            .expect("Failed to find a minimum");

        writeln!(
            formatter, 
            "Most {}, Least {}, Difference {}", 
            counter[25], least, counter[25] - least,
        )
    }
}