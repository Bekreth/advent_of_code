use bit_stream::BitStream;
use std::iter::Take;

#[derive(Debug)]
struct Header {
    version: u8,
    id: u8,
    id_type: IType,
}

#[derive(Debug)]
enum IType {
    BitCounter,
    PacketCounter,
    Literal,
}

#[derive(Debug)]
pub struct Packet {
    header: Header,
    content: Content,
}

#[derive(Debug)]
enum Content {
    Literal(u64),
    SubPacket(Box<Packet>),
}

impl Header {
    fn new<T>(bit_stream: &mut T) -> Self 
    where T: Iterator<Item = bool>
    {
        let mut version: u8 = 0;
        let mut id: u8 = 0;

        for i in 0..3 {
            match bit_stream.next() {
                None => panic!("Should have gotten"),
                Some(true) => version |= 1 << (2 - i),
                _ => (),
            }
        }
        for i in 0..3 {
            match bit_stream.next() {
                None => panic!("Should have gotten"),
                Some(true) => id |= 1 << (2 - i),
                _ => (),
            }
        }

        let id_type = if id == 4 {
            IType::Literal
        } else {
            match bit_stream.next() {
                None => panic!("Should have gotten"),
                Some(true) => IType::PacketCounter,
                Some(false) => IType::BitCounter,
            }
        };

        Header {
            version: version,
            id: id,
            id_type: id_type,
        }
    }
}

impl Packet {
    pub fn new<T>(bit_stream: &mut T) -> Self 
    where T: Iterator<Item = bool>
    {
        let header = Header::new::<T>(bit_stream);
        let content = match header.id_type {
            IType::Literal => parse_packet_literal::<T>(bit_stream),
            IType::BitCounter => {
                let bit_width = parse_wide_bit::<T>(bit_stream, 15);
                let mut sub_packet_bits = bit_stream.take(bit_width as usize);
                let packet = Packet::new(&mut sub_packet_bits);
                Content::SubPacket(Box::new(packet))
            },
            IType::PacketCounter => {
                // let packet_count = parse_wide_bit(bit_stream, 15);
                todo!()
            }
        };
        Packet {
            header: header,
            content: content,
        }
    }
}

fn parse_wide_bit<T>(bit_stream: &mut T, width: u8) -> u16 
    where T: Iterator<Item = bool>
    {
    let mut output: u16 = 0;
    for i in 0..width {
        match bit_stream.next() {
            None => panic!("Should have gotten"),
            Some(true) => output |= 1 << (2 - i),
            _ => (),
        }
    }
    output
}

fn parse_packet_literal<T>(bit_stream: &mut T) -> Content 
    where T: Iterator<Item = bool>
    {
    let mut packet_collector = vec![];
    let mut should_break = false;
    loop {
        let mut sub_component: u8 = 0;
        for i in 0..5 {
            match bit_stream.next() {
                None => panic!("Should have gotten"),
                Some(b) => {
                    if i == 0 {
                        if !b { should_break = true }
                    } else if b { sub_component |= 1 << (4 - i) }
                },
            }
        }
        packet_collector.push(sub_component);
        if should_break { break }
    }
    let size = packet_collector.len();
    let value = packet_collector.iter()
        .enumerate()
        .fold(0 as u64, |mut acc, (index, value)| {
            acc |= (*value as u64) << (size - index - 1) * 4;
            // println!("{:#010b}", acc);
            acc
        });
    Content::Literal(value)
}