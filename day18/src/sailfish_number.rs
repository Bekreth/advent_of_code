use std::fmt::{Display, Error, Formatter};
use std::result::Result;

#[derive(Debug, PartialEq, Clone)]
enum SailfishNumber<T> {
    Leaf(T),
    Branch {
        left: Box<SailfishNumber<T>>,
        right: Box<SailfishNumber<T>>,
    }
}

enum Terminal {
    True,
    Left,
    Right,
    Neither,
    False,
}

impl SailfishNumber<u32> {
    pub fn add(self, add_right: SailfishNumber<u32>) -> Self {
        SailfishNumber::Branch {
            left: Box::new(self),
            right: Box::new(add_right),
        }
    }

    pub fn reduced(&mut self, depth: u8) {
        let (mut left, mut right) = match self {
            SailfishNumber::Branch{
                left: L,
                right: R,
            } => (
                (L, R)
            ),
            SailfishNumber::Leaf(value) => panic!("Shouldn't be here"),
        };


    }

    pub fn find_leftmost(self) -> u32 {
        match self {
            SailfishNumber::Leaf(v) => v,
            SailfishNumber::Branch{ 
                left: L,
                right: _
            } => (L.find_leftmost()),
        }
    }

    pub fn find_rightmost(self) -> u32 {
        match self {
            SailfishNumber::Leaf(v) => v,
            SailfishNumber::Branch{ 
                left: _,
                right: R
            } => (R.find_rightmost()),
        }
    }

    fn terminal_branch(self) -> Terminal {
        match self {
            SailfishNumber::Leaf(_) => Terminal::False,
            SailfishNumber::Branch{
                left: L,
                right: R,
            } => {    
                match (*L, *R) {
                    (SailfishNumber::Leaf(_),  SailfishNumber::Leaf(_)) => Terminal::True,
                    (_,  SailfishNumber::Leaf(_)) => Terminal::Left,
                    (SailfishNumber::Leaf(_), _) => Terminal::Right,
                    (_, _) => Terminal::Neither,
                }
            }
        } 
    }

    pub fn try_split(self, depth: u8) -> Self {
        let terminus = self.terminal_branch();
        match self {
            SailfishNumber::Leaf(_) => self,
            SailfishNumber::Branch {
                left: L,
                right: R,
            } => {
                if depth < 4 {
                    SailfishNumber::Branch {
                        left: Box::new(L.try_split(depth + 1)),
                        right: Box::new(R.try_split(depth + 1)),
                    }
                } else {
                    match terminus {
                        Terminal::Left => (),
                        Terminal::Right => (),
                        Terminal::Neither => (),
                        Terminal::True => (),
                        Terminal::False => (),
                    }
                    // if self.terminal_branch() {
                        // SailfishNumber::Branch {
                            // left: Box::new(L.try_split(depth + 1)),
                            // right: Box::new(R.try_split(depth + 1)),
                        // }
                    // }


                    SailfishNumber::Branch {
                        left: Box::new(L.try_split(depth + 1)),
                        right: Box::new(R.try_split(depth + 1)),
                    }
                }
            },
        }

    }

    pub fn try_explode(self) -> Self {
        match self {
            SailfishNumber::Branch{
                left: L,
                right: R,
            } => (
                SailfishNumber::Branch{
                    left: Box::new(L.try_explode()),
                    right: Box::new(R.try_explode()),
                }
            ),
            SailfishNumber::Leaf(value) => {
                if value > 10 {
                    let v = value / 2;
                    if value % 2 == 0 {
                        SailfishNumber::Branch{
                            left: Box::new(SailfishNumber::Leaf(v)),
                            right: Box::new(SailfishNumber::Leaf(v)),
                        }
                    } else {
                         SailfishNumber::Branch{
                            left: Box::new(SailfishNumber::Leaf(v)),
                            right: Box::new(SailfishNumber::Leaf(v + 1)),
                        }
                    }
                } else {
                    self
                }
            }
        }
    }
}

impl Display for SailfishNumber<u32> {
    fn fmt(&self, formatter: &mut Formatter) -> Result<(), Error> { 
        match self {
            SailfishNumber::Leaf(v) => write!(formatter, "{}", *v),
            SailfishNumber::Branch{
                left: b1,
                right: b2,
            } => {
                writeln!(formatter, "[");
                writeln!(formatter, "  {},", b1);
                writeln!(formatter, "  {}", b2);
                writeln!(formatter, "]")
            },
        }
    }
}


macro_rules! sail_fish_number {

    ([[$($t1:tt)*], [$($t2:tt)*]]) => {
SailfishNumber::Branch::<u32> {
    left: Box::new(
        sail_fish_number!([$($t1)*])
    ),
    right: Box::new(
        sail_fish_number!([$($t2)*])
    ),
};
    };

    ([[$($t1:tt)*], $t2:tt]) => {
SailfishNumber::Branch::<u32> {
    left: Box::new(
        sail_fish_number!([$($t1)*])
    ),
    right: Box::new(SailfishNumber::Leaf::<u32>($t2)),
};
    };

    ([$t1:tt, [$($t2:tt)*]]) => {
SailfishNumber::Branch::<u32> {
    left: Box::new(SailfishNumber::Leaf::<u32>($t1)),
    right: Box::new(
        sail_fish_number!([$($t2)*])
    ),
};
    };

    ([$t1:tt, $t2:tt]) => {
SailfishNumber::Branch::<u32> {
    left: Box::new(SailfishNumber::Leaf::<u32>($t1)),
    right: Box::new(SailfishNumber::Leaf::<u32>($t2)),
};
    };
}

#[cfg(test)]
mod test {
    use sailfish_number::SailfishNumber;

    #[test]
    fn test_expand() {
        let large_number = sail_fish_number!([0, 15]);
        let expected_sailfish = sail_fish_number!([0, [7,8]]);
        assert_eq!(large_number.try_explode(), expected_sailfish);

        let large_number = sail_fish_number!([11, 18]);
        let expected_sailfish = sail_fish_number!([[5, 6], [9, 9]]);
        assert_eq!(large_number.try_explode(), expected_sailfish);
    }

    #[test]
    fn test_find_extremes() {
        let something = sail_fish_number!([[[[6,4],[0,0]],[[8,2],5]],[[8,[2,4]],[4,[9,1]]]]);
        assert_eq!(something.find_leftmost(), 6);

        let something = sail_fish_number!([[[[6,4],[0,0]],[[8,2],5]],[[8,[2,4]],[4,[9,1]]]]);
        assert_eq!(something.find_rightmost(), 1);
    }

    #[test]
    fn test_terminal_branch() {
        let terminal = sail_fish_number!([1, 2]);
        assert_eq!(terminal.terminal_branch(), true);

        let terminal = sail_fish_number!([1, [2, 3]]);
        assert_eq!(terminal.terminal_branch(), false);

        let terminal = sail_fish_number!([[2, 3], 1]);
        assert_eq!(terminal.terminal_branch(), false);

        let terminal = sail_fish_number!([[2, 3], [1,2]]);
        assert_eq!(terminal.terminal_branch(), false);

    }

    #[test]
    fn test_split() {
        let do_nothing = sail_fish_number!([4, 5]);
        let expected_sailfish = sail_fish_number!([4, 5]);
        assert_eq!(do_nothing.try_split(0), expected_sailfish);

        let split_left = sail_fish_number!([[[[[9,8],1],2],3],4]);
        let expected_sailfish = sail_fish_number!([[[[0,9],2],3],4]);
        assert_eq!(split_left.try_split(0), expected_sailfish);

        let split_right = sail_fish_number!([7,[6,[5,[4,[3,2]]]]]);
        let expected_sailfish = sail_fish_number!([[[[0,9],2],3],4]);
        assert_eq!(split_right.try_split(0), expected_sailfish);

    }
}
