const SAMPLE: [u8; 5] = [3,4,3,1,2];
const INPUT: [u8; 300] = [
    5,3,2,2,1, 1,4,1,5,5, 1,3,1,5,1, 2,1,4,1,2, // 20
    1,2,1,4,2, 4,1,5,1,3, 5,4,3,3,1, 4,1,3,4,4, // 40
    1,5,4,3,3, 2,5,1,1,3, 1,4,3,2,2, 3,1,3,1,3, // 60
    1,5,3,5,1, 3,1,4,2,1, 4,1,5,5,5, 2,4,2,1,4, // 80
    1,3,5,5,1, 4,1,1,4,2, 2,1,3,1,1, 1,1,3,4,1, // 100
    4,1,1,1,4, 4,4,1,3,1, 3,4,1,4,1, 2,2,2,5,4, // 120
    1,3,1,2,1, 4,1,4,5,2, 4,5,4,1,2, 1,4,2,2,2, // 140
    1,3,5,2,5, 1,1,4,5,4, 3,2,4,1,5, 2,2,5,1,4, // 160
    1,5,1,3,5, 1,2,1,1,1, 5,4,4,5,1, 1,1,4,1,3, // 180
    3,5,5,1,5, 2,1,1,3,1, 1,3,2,3,4, 4,1,5,5,3, // 200
    2,1,1,1,4, 3,1,3,3,1, 1,2,2,1,2, 2,2,1,1,5, // 220
    1,2,2,5,2, 4,1,1,2,4, 1,2,3,4,1, 2,1,2,4,2, // 240
    1,1,5,3,1, 4,4,4,1,5, 2,3,4,4,1, 5,1,2,2,4, // 260
    1,1,2,1,1, 1,1,5,1,3, 3,1,1,1,1, 4,1,2,2,5, // 280
    1,2,1,3,4, 1,3,4,3,3, 1,1,5,5,5, 2,4,3,1,4  // 300
];

#[derive(Debug)]
struct LanternFish {
    age: u8,
    count: u128
}

impl LanternFish {
    fn new(starter_age: &u8) -> Self {
        return LanternFish {
            age: *starter_age,
            count: 1
        }
    }
}

fn main() {
    let mut fish_0 = LanternFish{age: 0, count: 0};
    let mut fish_1 = LanternFish{age: 1, count: 0};
    let mut fish_2 = LanternFish{age: 2, count: 0};
    let mut fish_3 = LanternFish{age: 3, count: 0};
    let mut fish_4 = LanternFish{age: 4, count: 0};
    let mut fish_5 = LanternFish{age: 5, count: 0};
    let mut fish_6 = LanternFish{age: 6, count: 0};
    let mut fish_7 = LanternFish{age: 7, count: 0};
    let mut fish_8 = LanternFish{age: 8, count: 0};

    let mut empty_start_vector: Vec<&mut LanternFish> = vec![
        &mut fish_0,
        &mut fish_1,
        &mut fish_2,
        &mut fish_3,
        &mut fish_4,
        &mut fish_5,
        &mut fish_6,
        &mut fish_7,
        &mut fish_8,
    ];
    let collection = INPUT.iter()
        .map(LanternFish::new)
        .fold(&mut empty_start_vector,|collector, fish| {
            collector[fish.age as usize].count += fish.count;
            return collector;
        });

    for _ in 0..80 {
        let zero: u128 = collection[0].count;
        for i in 0..8 {
            let previous_fish_count = collection[i+1].count;
            collection[i].count = previous_fish_count;
        }
        collection[8].count = zero;
        collection[6].count += zero;
    }

    let silver = collection.iter()
        .map(|fish| fish.count)
        .fold(0, |aggregator, current| aggregator + current);

    println!("Silver: {}", silver);

    for _ in 80..256 {
        let zero: u128 = collection[0].count;
        for i in 0..8 {
            let previous_fish_count = collection[i+1].count;
            collection[i].count = previous_fish_count;
        }
        collection[8].count = zero;
        collection[6].count += zero;
    }

    let gold = collection.iter()
        .map(|fish| fish.count)
        .fold(0, |aggregator, current| aggregator + current);

    println!("Gold: {}", gold);
}