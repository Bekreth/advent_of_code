
pub struct BitStream {
    bit_dex: usize,
    index: usize,
    data: Vec<u8>,
}

impl BitStream {
    pub fn new(line: String) -> Self {
        BitStream {
            bit_dex: 0,
            index: 0,
            data: (0..line.len())
                .step_by(2)
                .map(|i| u8::from_str_radix(&line[i..i + 2], 16).expect(""))
                .collect::<Vec<u8>>()
        }
    }
}

impl Iterator for BitStream {
    type Item = bool;

    fn next(&mut self) -> Option<Self::Item> {
        if self.index < self.data.len() * 8 {
            let int = self.data[self.index];
            let shift = 7 - (self.bit_dex % 8);
            self.bit_dex += 1;
            if self.bit_dex == 8 {
                self.bit_dex = 0;
                self.index += 1;
            }
            if int & (1 << shift) == 0 {
                Some(false)
            } else {
                Some(true)
            }
        } else {
            None
        }
    }
}