use cave::CaveSystem;

mod silver;
mod gold;

use cave::Cave;
pub use walker::silver::SilverWalker;
pub use walker::gold::GoldWalker;

pub trait Walker : Sized {
    fn possible_next_steps(&self, cave_system: &CaveSystem) -> Vec<Self>;
    fn finished(&self) -> bool;
    fn previously_visited(&self) -> Vec<Cave>;
}