use spatial::Point;

#[derive(Debug)]
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
}