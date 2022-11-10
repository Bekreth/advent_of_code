use std::fs;
use std::u32;
use std::env;

struct Window {
    total: u32
}

struct WindowAggregator {
    previous_depth: u32,
    depth_increases: u32,
    windows: Vec<Option<Window>>,
    window_head: usize,
    max_head: usize
}

impl WindowAggregator {
    fn new(max_head: usize) -> Self {
        WindowAggregator{
            previous_depth: u32::MAX,
            depth_increases: 0,
            windows: (0..max_head).map(|_|None).collect::<Vec<Option<Window>>>(),
            window_head: 0,
            max_head: max_head,
        }
    }

    fn add_measurement(&mut self, measurement: u32) {
        match &self.windows[self.window_head] {
            Some(w) => {
                if w.total > self.previous_depth {
                    self.depth_increases += 1;
                }
                self.previous_depth = w.total;
            },
            None => ()
        }
        for window in self.windows.iter_mut() {
            match window {
                Some(w) => w.total += measurement,
                None => ()
            }
        }
        let new_window = Window{total: measurement};
        self.windows[self.window_head] = Some(new_window);
        self.window_head += 1;
        self.window_head %= self.max_head;
    }

    fn finalize(&mut self) {
        for _ in 0..self.max_head {
            self.add_measurement(0);
        }
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");
    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");


    let mut silver_aggregator = WindowAggregator::new(1);
    let mut gold_aggregator = WindowAggregator::new(3);
    for (_, line) in contents.lines().enumerate() {
        let measurement = line.parse().unwrap();
        gold_aggregator.add_measurement(measurement);
        silver_aggregator.add_measurement(measurement);
    }
    silver_aggregator.finalize();
    gold_aggregator.finalize();

    println!("Silver: number of depth increases: {}", silver_aggregator.depth_increases);
    println!("Gold  : number of depth increases: {}", gold_aggregator.depth_increases);
}
