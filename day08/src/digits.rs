
pub trait Digit {
    fn matches_input(&mut self, input: &str) -> Option<bool>;
    fn check_match(&self, input: &str) -> Option<u8>;
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

pub fn get_aparent<'a>() -> [Box<dyn Digit>; 4] {
    return [
        Box::new(One{char_bitmask: 0}),
        Box::new(Four{char_bitmask: 0}),
        Box::new(Seven{char_bitmask: 0}),
        Box::new(Eight{char_bitmask: 0})
    ];
}

pub fn get_order<'a>() -> [Box<&'a dyn Digit>; 6] {
    return [
        Box::new(&Zero{char_bitmask: 0}),
        Box::new(&Two{char_bitmask: 0}),
        Box::new(&Three{char_bitmask: 0}),
        Box::new(&Five{char_bitmask: 0}),
        Box::new(&Six{char_bitmask: 0}),
        Box::new(&Nine{char_bitmask: 0}),
    ];
}

struct Zero {
    char_bitmask: u8
}

impl Digit for Zero {
    fn matches_input(&mut self, input: &str) -> Option<bool> { 
        return None;
        if input.len() != 6 {
            Some(false);
        }
        todo!()
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask != 0 {
            return Some(0);
        } else {
            return None;
        }
    }
}


struct One {
    char_bitmask: u8
}

impl Digit for One {
    fn matches_input(&mut self, input: &str) -> Option<bool> { 
        if input.len() == 2 {
            self.char_bitmask = assign_bitmask(input);
            return Some(true);
        } else {
            return Some(false);
        }
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(1);
        } else {
            return None;
        }
    }
}

struct Two {
    char_bitmask: u8
}

impl Digit for Two {
    fn matches_input(&mut self, input: &str) -> Option<bool> { 
        return None;
        if input.len() != 5 {
            return Some(false);
        }
        //TODO
        None
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask != 0 {
            return Some(2);
        } else {
            return None;
        }
    }
}


struct Three {
    char_bitmask: u8
}

impl Digit for Three {
    fn matches_input(&mut self, input: &str) -> Option<bool> { 
        return None;
        todo!()
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask != 0 {
            return Some(3);
        } else {
            return None;
        }
    }
}


struct Four {
    char_bitmask: u8
}

impl Digit for Four {
    fn matches_input(&mut self, input: &str) -> Option<bool> { 
        if input.len() == 4 {
            self.char_bitmask = assign_bitmask(input);
            return Some(true);
        } else {
            return Some(false);
        }
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(4);
        } else {
            return None;
        }
    }
}


struct Five {
    char_bitmask: u8
}

impl Digit for Five {
    fn matches_input(&mut self, input: &str) -> Option<bool> { 
        return None;
        todo!()
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask != 0 {
            return Some(5);
        } else {
            return None;
        }
    }
}


struct Six {
    char_bitmask: u8
}

impl Digit for Six {
    fn matches_input(&mut self, input: &str) -> Option<bool> { 
        return None;
        todo!()
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask != 0 {
            return Some(6);
        } else {
            return None;
        }
    }
}


struct Seven {
    char_bitmask: u8
}

impl Digit for Seven {
    fn matches_input(&mut self, input: &str) -> Option<bool> { 
        if input.len() == 3 {
            self.char_bitmask = assign_bitmask(input);
            return Some(true);
        } else {
            return Some(false);
        }
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(7);
        } else {
            return None;
        }
    }
}


struct Eight {
    char_bitmask: u8
}

impl Digit for Eight {
    fn matches_input(&mut self, input: &str) -> Option<bool> { 
        if input.len() == 7 {
            self.char_bitmask = assign_bitmask(input);
            return Some(true);
        } else {
            return Some(false);
        }
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask == assign_bitmask(input) {
            return Some(8);
        } else {
            return None;
        }
    }
}


struct Nine {
    char_bitmask: u8
}

impl Digit for Nine {
    fn matches_input(&mut self, input: &str) -> Option<bool> { 
        None
    }

    fn check_match(&self, input: &str) -> Option<u8> {
        if self.char_bitmask != 0 {
            return Some(9);
        } else {
            return None;
        }
    }
}

