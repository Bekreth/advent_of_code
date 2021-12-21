use bit_map::BitMap;
use spatial::Point;

#[derive(Clone, Debug)]
pub struct Scanner {
    id: u8,
    beacons: Vec<Point>,
    location: Point,
}

impl Scanner {
    pub fn new(id: u8) -> Self {
        Scanner {
            id: id,
            beacons: vec![],
            location: Point::default(),
        }
    }

    pub fn append(&mut self, point: Point) {
        self.beacons.push(point);
    }

    pub fn bit_maps(&self) -> (Shifter, Shifter, Shifter) {
        let mut x_offset = self.beacons[0].x;
        let mut y_offset = self.beacons[0].y;
        let mut z_offset = self.beacons[0].z;

        self.beacons.iter()
            .for_each(|b| {
                if b.x < x_offset { x_offset = b.x }
                if b.y < y_offset { y_offset = b.y }
                if b.z < z_offset { z_offset = b.z }
            });

        if x_offset < 0 { x_offset = x_offset * -1 }
        if y_offset < 0 { y_offset = y_offset * -1 }
        if z_offset < 0 { z_offset = z_offset * -1 }

        let collected_points = self.beacons.iter()
            .map(|b| (
                (x_offset + b.x) as u128,
                (y_offset + b.y) as u128,
                (z_offset + b.z) as u128,
            ))
            .fold(
                (vec![], vec![], vec![]), 
                |mut acc: (Vec<u128>, Vec<u128>, Vec<u128>), b| {
                    acc.0.push(b.0);
                    acc.1.push(b.1);
                    acc.2.push(b.2);
                    acc
                }
            );
        
        (
            Shifter {
                bit_map: BitMap::new(collected_points.0),
                offset: x_offset as u32,
            },
            Shifter {
                bit_map: BitMap::new(collected_points.1),
                offset: y_offset as u32,
            },
            Shifter {
                bit_map: BitMap::new(collected_points.2),
                offset: z_offset as u32,
            },
        )
    }
}

pub struct Shifter {
    bit_map: BitMap,
    offset: u32,
}