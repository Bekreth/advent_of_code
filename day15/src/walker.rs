use floor_map::{FloorMap};
use std::cmp::Ordering;


#[derive(Clone, Debug)]
pub struct Walker {
    position: (usize, usize),
    total_risk: u16,
    visited: Vec<(usize, usize)>
}

impl Walker {
    pub fn new() -> Self {
        Walker {
            position: (0, 0),
            total_risk: 0,
            visited: vec![]
        }
    }

    pub fn next_step(&self, floor_map: &FloorMap) -> Vec<Self> {
        let mut new_points = floor_map.find_adjacent(self.position)
            .iter()
            .filter(|(point, _)| !self.visited.contains(point))
            .map(|(point, risk)| {
                let mut visited = self.visited.clone();
                visited.push(*point);
                Walker {
                    position: *point,
                    total_risk: self.total_risk + *risk as u16,
                    visited: visited,
                }
            })
            .collect::<Vec<Self>>();
        new_points.sort_by(min_length);
        return new_points;
    }

    pub fn too_risky(&self, max_risk: u16, end: (usize, usize)) -> bool {
        let (x, y) = self.position;
        let best_remainder: u16 = (end.0 - x) as u16 + (end.1 - y) as u16;
        self.total_risk + best_remainder >= max_risk
    }

    pub fn completed(&self, end: (usize, usize)) -> Option<u16> {
        if self.position == end {
            Some(self.total_risk)
        } else {
            None
        }
    }
}

fn min_length(w1: &Walker, w2: &Walker) -> Ordering {
    let (x, y) = (999, 999);
    let (x1, y1) = w1.position;
    let (x2, y2) = w2.position;

    let l1: u32 = (x-x1 as u32)^2 + (y-y1 as u32)^2;
    let l2: u32 = (x-x2 as u32)^2 + (y-y2 as u32)^2;

    l2.cmp(&l1)
}