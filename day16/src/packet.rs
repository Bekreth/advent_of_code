use bit_stream::BitStream;

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
    fn new(bit_stream: &mut BitStream) -> Self {
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
                Some(true) => IType::BitCounter,
                Some(false) => IType::PacketCounter,
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
    pub fn new(bit_stream: &mut BitStream) -> Self {
        let header = Header::new(bit_stream);
        let content = match header.id_type {
            IType::Literal => parse_packet_literal(bit_stream),
            IType::BitCounter => todo!(),
            IType::PacketCounter => todo!(),
        };
        Packet {
            header: header,
            content: content,
        }
    }
}

fn parse_packet_literal(bit_stream: &mut BitStream) -> Content {
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