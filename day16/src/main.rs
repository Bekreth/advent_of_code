mod bit_stream;
mod packet;

use bit_stream::BitStream;
use packet::Packet;

use std::fs;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");

    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");

    let mut bit_stream = BitStream::new(contents); 
    let packet = Packet::new(&mut bit_stream);

    println!("Silver: {:?}", packet);
}
