pub struct FloorMap {
    data: Vec<Vec<u8>>
}

impl FloorMap {
    pub fn new(content: String) -> Self {
        let map_data = content.lines()
            .map(|line| {
                line.chars()
                    .map(|c| c.to_digit(10).expect("failed to parse char") as u8)
                    .collect::<Vec<u8>>()
            })
            .collect::<Vec<Vec<u8>>>();
        FloorMap {
            data: map_data,
        }
    }

    pub fn find_low_points(&self) -> Vec<(usize, usize, u8)> {
        let output = self.data.iter()
            .enumerate()
            .map(|(i, vec_row)| {
                let output: Vec<(usize, usize, u8)> = vec_row.iter()
                    .enumerate()
                    .filter_map(|(j, _)| is_local_minimum(&self.data, i, j))
                    .collect::<Vec<(usize, usize, u8)>>();
                output
            })
            .flatten()
            .collect::<Vec<(usize, usize, u8)>>();

        return output;
    }

    pub fn calculate_basin(&self, i: usize, j: usize) -> Vec<(usize, usize, u8)> {
        let value = self.data[i][j];
        let collector = vec![(i, j, value)];
        let mut child_values: Vec<(usize, usize, u8)> = scan_adjacent(&self.data, i, j)
            .iter()
            .filter(|(_, _, target)| value < *target && *target != 9)
            .map(|(i, j, _)| self.calculate_basin(*i, *j))
            .flatten()
            .fold(collector, |mut acc, point| {
                acc.push(point);
                acc
            });
        child_values.sort();
        child_values.dedup();
        return child_values;
    }
}

fn is_local_minimum(data: &Vec<Vec<u8>>, i: usize, j: usize) -> Option<(usize, usize, u8)> {
    let value = data[i][j];
    match scan_adjacent(data, i, j)
        .iter()
        .find(|(_, _, target)| value >= *target)
    {
        Some(_) => None,
        None => Some((i, j, value)),
    }
}

fn scan_adjacent(data: &Vec<Vec<u8>>, i: usize, j: usize) -> Vec<(usize, usize, u8)>{
    let mut output = vec![];

    let height = data[0].len();
    if j > 0 {
        let target = data[i][j - 1];
        output.push((i, j - 1, target));
    }

    let length = data.len();
    if i > 0 {
        let target = data[i - 1][j];
        output.push((i - 1, j, target));
    }
    if i < length - 1 {
        let target = data[i + 1][j];
        output.push((i + 1, j, target));
    }

    if j < height - 1 {
        let target = data[i][j + 1];
        output.push((i, j + 1, target));
    }

    return output;
}