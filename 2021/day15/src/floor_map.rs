
pub struct FloorMap {
    risk_map: Vec<Vec<u8>>,
    pub maxes: (usize, usize),
    pub upper_limit: u16,
}

impl FloorMap {
    pub fn new(lines: String) -> Self {
        let risks: Vec<Vec<u8>> = lines.lines()
            .map(|line| {
                line.chars().map(|c| 
                    c.to_digit(10).expect("Failed to risk") as u8
                )
                .collect::<Vec<u8>>()
            })
            .collect::<Vec<Vec<u8>>>();
        let maxes = (risks.len() - 1, risks[0].len() - 1);
        let mut upper_limit: u16 = 0;
        for i in 0..(maxes.0 + 1) {
            upper_limit += risks[i][0] as u16;
            upper_limit += risks[0][i] as u16;
        }
        println!("Farthest quadrent {:?}", maxes);
        println!("upper limit {:?}", upper_limit);
        FloorMap{
            risk_map: risks,
            maxes: maxes,
            upper_limit: upper_limit,
        }
    }

    pub fn find_adjacent(&self, position: (usize, usize)) -> Vec<((usize, usize), u8)> {
        let (x, y) = position;

        let mut output = vec![];

        if x != 0 { 
            let joined = ((x - 1, y), self.risk_map[x - 1][y]);
            output.push(joined);
        }
        if x != self.maxes.0 { 
            let joined = ((x + 1, y), self.risk_map[x + 1][y]);
            output.push(joined);
        }
        if y != 0 { 
            let joined = ((x, y - 1), self.risk_map[x][y - 1]);
            output.push(joined);
        }
        if y != self.maxes.1 {
            let joined = ((x, y + 1), self.risk_map[x][y + 1]);
            output.push(joined);
        }

        return output;
    }
}