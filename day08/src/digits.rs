
pub trait Digit {
    fn matches_input(&mut self, input: &str) -> bool;
    fn check_match(&self, input: &str) -> Option<u8>;
    fn get_mask(&self) -> u8;
}

fn assign_bitmask(value: &str) -> u8 {
    let mut output: u8 = 0;
    for c in value.chars() {
        match c {
            'a' => output |= (1 as u8) << 0,
            'b' => output |= (1 as u8) << 1,
            'c' => output |= (1 as u8) << 2,
            'd' => output |= (1 as u8) << 3,
            'e' => output |= (1 as u8) << 4,
            'f' => output |= (1 as u8) << 5,
            'g' => output |= (1 as u8) << 6,
            _ => ()
        }
    }
    return output;
}

fn count_bits(input: u8) -> u8 {
    let mut counter = 0;
    for i in 0..7 {
        if 1 << i & input != 0 {
            counter += 1;
        } 
    }
    return counter;
}

pub fn get_aparent<'a>() -> [Box<dyn Digit>; 4] {
    return [
        Box::new(One{char_bitmask: 0}),
        Box::new(Four{char_bitmask: 0}),
        Box::new(Seven{char_bitmask: 0}),
        Box::new(Eight{char_bitmask: 0})
    ];
}

pub fn get_order<'a, T: Digit + ?Sized>(hints: &[Box<T>; 4]) -> [Box<dyn Digit>; 6] {

    let mut one = 0;
    let mut four = 0;
    let mut seven = 0;

    for h in hints.iter() {
        let mask = h.get_mask();
        match count_bits(mask) {
            2 => one = mask,
            4 => four = mask,
            3 => seven = mask,
            _ => ()
        }
    }

    return [
        Box::new(Three{
            char_bitmask: 0,
            one_mask: one,
        }),
        Box::new(Zero{
            char_bitmask: 0,
            four_mask: four,
            seven_mask: seven,
        }),
        Box::new(Two{
            char_bitmask: 0,
            four_mask: four,
        }),
        Box::new(Five{
            char_bitmask: 0,
            one_mask: one,
            four_mask: four,
        }),
        Box::new(Nine{
            char_bitmask: 0,
            four_mask: four
        }),
        Box::new(Six{
            char_bitmask: 0,
            seven_mask: seven
        }),
    ];
}

struct Zero {
    char_bitmask: u8,
    four_mask: u8,
    seven_mask: u8,
}

impl Digit for Zero {
    fn matches_input(&mut self, input: &str) -> bool { 
        if input.len() != 6 {
            return false;
        }
        let input_bits = assign_bitmask(input); 
        let masked_seven = input_bits ^ (input_bits & self.seven_mask);
        if count_bits(masked_seven) != 3 {
            return false;
        }
        let masked_four = masked_seven ^ (masked_seven & self.four_mask);
        if count_bits(masked_four) != 2 {
            return false;
        }
        self.char_bitmask = assign_bitmask(input);
        return true;
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(0);
        } else {
            return None;
        }
    }

    fn get_mask(&self) -> u8 {
        return self.char_bitmask;
    }
}


struct One {
    char_bitmask: u8
}

impl Digit for One {
    fn matches_input(&mut self, input: &str) -> bool { 
        if input.len() == 2 {
            self.char_bitmask = assign_bitmask(input);
            return true;
        } else {
            return false;
        }
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(1);
        } else {
            return None;
        }
    }

    fn get_mask(&self) -> u8 {
        return self.char_bitmask;
    }
}

struct Two {
    char_bitmask: u8,
    four_mask: u8
}

impl Digit for Two {
    fn matches_input(&mut self, input: &str) -> bool { 
        if input.len() != 5 {
            return false;
        }
        let input_bits = assign_bitmask(input);
        let masked_value = input_bits ^ (input_bits & self.four_mask);
        if count_bits(masked_value) != 3 {
            return false;
        }
        self.char_bitmask = assign_bitmask(input);
        return true;
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(2);
        } else {
            return None;
        }
    }

    fn get_mask(&self) -> u8 {
        return self.char_bitmask;
    }
}


struct Three {
    char_bitmask: u8,
    one_mask: u8
}

impl Digit for Three {
    fn matches_input(&mut self, input: &str) -> bool { 
        if input.len() != 5 {
            return false
        }
        let masked = assign_bitmask(input) ^ self.one_mask;
        if count_bits(masked) == 3 {
            self.char_bitmask = assign_bitmask(input);
            return true
        } 
        return false;
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(3);
        } else {
            return None;
        }
    }

    fn get_mask(&self) -> u8 {
        return self.char_bitmask;
    }
}


struct Four {
    char_bitmask: u8
}

impl Digit for Four {
    fn matches_input(&mut self, input: &str) -> bool { 
        if input.len() == 4 {
            self.char_bitmask = assign_bitmask(input);
            return true;
        } else {
            return false;
        }
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(4);
        } else {
            return None;
        }
    }

    fn get_mask(&self) -> u8 {
        return self.char_bitmask;
    }
}

struct Five {
    char_bitmask: u8,
    one_mask: u8,
    four_mask: u8
}

impl Digit for Five {
    fn matches_input(&mut self, input: &str) -> bool { 
        if input.len() != 5 {
            return false;
        }
        let input_bits = assign_bitmask(input);
        let mut masked_value = input_bits ^ (input_bits & self.one_mask);
        if count_bits(masked_value) != 4 {
            return false;
        }
        masked_value = masked_value ^ (masked_value & self.four_mask);
        if count_bits(masked_value) != 2 {
            return false;
        }
        self.char_bitmask = assign_bitmask(input);
        return true;
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(5);
        } else {
            return None;
        }
    }

    fn get_mask(&self) -> u8 {
        return self.char_bitmask;
    }
}

struct Six {
    char_bitmask: u8,
    seven_mask: u8
}

impl Digit for Six {
    fn matches_input(&mut self, input: &str) -> bool { 
        if input.len() != 6 {
            return false;
        }
        let input_bits = assign_bitmask(input);
        let masked_value = input_bits ^ (input_bits & self.seven_mask);
        if count_bits(masked_value) != 4 {
            return false;
        }
        self.char_bitmask = assign_bitmask(input);
        return true;
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(6);
        } else {
            return None;
        }
    }

    fn get_mask(&self) -> u8 {
        return self.char_bitmask;
    }
}


struct Seven {
    char_bitmask: u8
}

impl Digit for Seven {
    fn matches_input(&mut self, input: &str) -> bool { 
        if input.len() == 3 {
            self.char_bitmask = assign_bitmask(input);
            return true;
        } else {
            return false;
        }
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(7);
        } else {
            return None;
        }
    }

    fn get_mask(&self) -> u8 {
        return self.char_bitmask;
    }
}


struct Eight {
    char_bitmask: u8
}

impl Digit for Eight {
    fn matches_input(&mut self, input: &str) -> bool { 
        if input.len() == 7 {
            self.char_bitmask = assign_bitmask(input);
            return true;
        } else {
            return false;
        }
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(8);
        } else {
            return None;
        }
    }

    fn get_mask(&self) -> u8 {
        return self.char_bitmask;
    }
}

struct Nine {
    char_bitmask: u8,
    four_mask: u8
}

impl Digit for Nine {
    fn matches_input(&mut self, input: &str) -> bool { 
        if input.len() != 6 {
            return false;
        }
        let masked_value = assign_bitmask(input) ^ self.four_mask;
        if count_bits(masked_value) != 2 {
            return false;
        }
        self.char_bitmask = assign_bitmask(input);
        return true;
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(9);
        } else {
            return None;
        }
    }

    fn get_mask(&self) -> u8 {
        return self.char_bitmask;
    }
}

