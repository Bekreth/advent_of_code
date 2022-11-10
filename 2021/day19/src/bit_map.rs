use std::ops::{
    Shl,
    BitOr,
};

// const U128_EDGE: u128 = 1 << 127;

#[derive(Copy, Clone)]
pub struct BitMap {
    points: [u128; 100]
}

impl BitOr<BitMap> for BitMap {
    type Output = BitMap;

    fn bitor(self, input: Self) -> Self { 
        let mut output = [0 as u128; 100];
        for i in 0..100 {
            output[i] = self.points[i] | input.points[i];
        }
        BitMap {
            points: output,
        }
    }
}

impl Shl<u128> for BitMap {
    type Output = BitMap;
    fn shl(self, rhs: u128) -> Self { 
        /*
        if rhs >= self.calculate_headroom() {
            panic!("Overrun the limits of the u12800: {}", self.calculate_headroom());
        }
        */

        let index_shift: usize = rhs as usize / 128;
        let bit_shift = rhs % 128;
        let mut output = [0 as u128; 100];
        for i in 0..100 {
            let reference = self.points[i];
            let shifted: (u128,  u128) = (
                reference >> 128 - bit_shift,
                reference << bit_shift,
            );
            if i + index_shift + 1 >= 100 {
                break;
            }
            output[i + index_shift] |= shifted.1;
            output[i + index_shift + 1] = shifted.0;
        }
        BitMap{
            points: output,
        }
    }

}


impl BitMap {
    pub fn new(values: Vec<u128>) -> Self {
        BitMap{
            points: values.iter()
                .map(|v| {
                    let iter_count = v / 128;
                    if iter_count >= 100 {
                        panic!("Number too large")
                    }
                    let modulo = v % 128;
                    (iter_count as usize, 1 << modulo)
                })
                .fold([0 as u128; 100], |mut accumulator, (index, shifted)| {
                    accumulator[index] |= shifted;
                    accumulator
                })
        }
    }

    pub fn count_overlap(self, input: Self) -> u32 {
        let target = self | input;
        target.points.iter()
            .map(BitMap::count_u128)
            .sum()
    }

    fn count_u128(v1: &u128) -> u32 {
        let mut counter = 0;
        for i in 0..128 {
            if v1 & (1 << i) != 0 {
                counter += 1;
            } 
        }
        counter
    }

    fn calculate_headroom(&self) -> u128 {
        let mut top = 0;
        let mut top_bit = 0;
        for i in 0..100 {
            let top_point = self.points[99 - i];
            if top_point == 0 {
                continue;
            }
            top = i;
            for j in 0..128 {
                if top_point | (1 << j) != 0 {
                    top_bit = j;
                }
            }
        }
        let max_bit = top * 128 + top_bit;
        12_800 - (max_bit as u128)
    }
}


#[cfg(test)]
mod tests {
    use bit_map::BitMap;

    #[test]
    fn check_mask() {
        let bit_map = BitMap::new(vec![0, 3, 200, 500]);
        let mut expected = [0 as u128; 100];
        expected[0] |= 1 << 0;
        expected[0] |= 1 << 3;
        expected[1] |= 1 << 72;
        expected[3] |= 1 << 116;
        assert_eq!(bit_map.points, expected);
    }

    #[test]
    fn test_bit_shift() {
        let bit_map = BitMap::new(vec![0, 3, 200, 500]);
        let mut expected = [0 as u128; 100];
        expected[0] |= 1 << 0;
        expected[0] |= 1 << 3;
        expected[1] |= 1 << 72;
        expected[3] |= 1 << 116;
        assert_eq!(bit_map.points, expected);

        let new_map = bit_map << 130;

        let mut new_expected = [0 as u128; 100];
        new_expected[1] |= 1 << 2;
        new_expected[1] |= 1 << 5;
        new_expected[2] |= 1 << 74;
        new_expected[4] |= 1 << 118;
        assert_eq!(new_map.points, new_expected);
    }
}