use std::thread::JoinHandle;
use std::sync::mpsc;
use std::fs;
use std::env;
use chrono::Utc;
use threadpool::ThreadPool;
extern crate chrono;
extern crate threadpool;

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
    let mut collection = INPUT.iter()
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

/*
fn from_6() -> u128 {
    return 3_989_468_462
}

struct Work<'a> { 
    fish: Box<&'a mut LanternFish>,
    count_down: u8
}
*/

/*
fn new_work<'a>(input: u8) -> Work<'a> {
    return Work {
        fish: Box::new(&mut LanternFish{age: input}),
        count_down: 100
    }
}
*/

/*
fn main() {
    let (work_queue, work_dequeue) = mpsc::channel::<Work>();
    let (count_out, count_in) = mpsc::channel::<()>(); 

    let pool = ThreadPool::with_name("worker".into(), 10);
    let mut workers = vec![];

    for i in 0..10 {
        let work_out = work_queue.clone();
        let (work_sender, work_reciever) = mpsc::channel::<Work>();
        let count_exporter = count_out.clone();
        pool.execute(move || {
            for work in work_reciever.iter() {
                if work.count_down == 0 {
                    count_exporter.send(()).expect("Failed to send count")
                }
                match work.fish.age_down() {
                    Some(mut new_fish) => {
                        let new_work = Work {
                            fish: Box::new(&mut new_fish),
                            count_down: work.count_down-1,
                        };
                        work_out.send(new_work);
                    },
                    None => (),
                }
                work_out.send(Work{
                    fish: work.fish, 
                    count_down: work.count_down-1
                }).expect("Failed to send fish")
            }
        });
        workers.push(work_sender);
    }


    let fan_out = std::thread::spawn(move || {
        let mut pool_counter = 0;
        for work in work_dequeue {
            workers[pool_counter].send(work).expect("");
            pool_counter += 1;
            pool_counter %= 10;
        }
    });

    let count_fish = std::thread::spawn(move || {
        let mut output: u128 = 0;
        for i in count_in {
            output += 1;
        }
        return output;
    });

    // SAMPLE.iter()
        // .map(|age| LanternFish{age: *age})
        // .map(|fish| Work{fish: &mut fish, count_down: 80})
        // .for_each(|work| work_queue.send(work).expect("Failed to send work"));
    
    for v in SAMPLE.iter() {
        // let fish: LanternFish = &mut LanternFish{age: *v};
        // let work = new_work(*v);
        // work_queue.send(work).expect("msg: &str");
    }

    pool.join();
    fan_out.join();

    let total = count_fish.join();
    println!("Fish counted: {}", total.expect("Failed to count fish"));

}
*/