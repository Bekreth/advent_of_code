
#[derive(Debug)]
pub struct Player {
    id: u8,
    position: u16,
    pub score: u16,
}

impl Player {
    pub fn new(id: u8, start: u16) -> Self {
        Player {
            id: id,
            position: start,
            score: 0,
        }
    }

    pub fn rolled_value(&mut self, rolled: u16) {
        self.position += rolled;
        if self.position % 10 == 0 {
            self.position = 10;
        } else {
            self.position %= 10;
        }
        self.score += self.position as u16;
    }

}