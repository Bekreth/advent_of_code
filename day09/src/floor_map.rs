use std::fmt::Write as FmtWrite;
use std::io::Write as IoWrite;

pub struct FloorMap {
    data: Vec<Vec<u16>>
}

impl FloorMap {
    pub fn new(content: String) -> Self {
        let map_data = content.lines()
            .map(|line| {
                line.chars()
                    .map(|c| c.to_digit(10).expect("failed to parse char") as u16)
                    .collect::<Vec<u16>>()
            })
            .collect::<Vec<Vec<u16>>>();
        FloorMap {
            data: map_data,
        }
    }

    pub fn find_low_points(self) -> Vec<(usize, usize, u16)> {
        let output = self.data.iter()
            .enumerate()
            .map(|(i, vec_row)| {
                let output: Vec<(usize, usize, u16)> = vec_row.iter()
                    .enumerate()
                    .filter_map(|(j, _)| is_local_minimum(&self.data, i, j))
                    .collect::<Vec<(usize, usize, u16)>>();
                output
            })
            .flatten()
            .collect::<Vec<(usize, usize, u16)>>();

        return output;
    }

    pub fn calculate_basin() -> u16 {

        todo!()
    }

}

fn is_local_minimum(data: &Vec<Vec<u16>>, i: usize, j: usize) -> Option<(usize, usize, u16)> {
    let value = data[i][j];
    let mut writer = String::new();

    let height = data[0].len();
    if j > 0 {
        let target = data[i][j - 1];
        writeln!(&mut writer, "---{}---", target);
        if value >= target { 
            return None
        }
    }

    let length = data.len();
    if i > 0 {
        let target = data[i - 1][j];
        write!(&mut writer, "{}", target);
        if value >= target {
            return None
        }
    } else {
        write!(&mut writer, "-");
    }
    write!(&mut writer, "-:{}:-", value);
    if i < length - 1 {
        let target = data[i + 1][j];
        write!(&mut writer, "{}", target);
        if value >= target { 
            return None
        }
    } else {
        write!(&mut writer, "-");
    }
    writeln!(&mut writer, "");

    if j < height - 1 {
        let target = data[i][j + 1];
        writeln!(&mut writer, "---{}---", target);
        if value >= target {
            return None
        }
    } else {
        writeln!(&mut writer, "-------");
    }

    // println!("==\n{} ({}, {})\n==", writer, i, j);

    Some((i, j, value))
}