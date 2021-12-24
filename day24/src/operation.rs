
pub trait Operator {
    fn apply(self, value1: i128, value2: i128) -> i128;
}

pub enum Operations {
    Add,
    Multiply,
    Divide,
    Modulo,
    Equal,
}

impl Operator for Operations {
    fn apply(self, value1: i128, value2: i128) -> i128 {
        match self {
            Operations::Add => value1 + value2,
            Operations::Multiply => value1 * value2,
            Operations::Divide => value1 / value2,
            Operations::Modulo => value1 % value2,
            Operations::Equal => if value1 == value2 { 1 } else { 0 },
        }
    }
}
