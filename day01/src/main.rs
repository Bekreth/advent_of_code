use std::fs;
use std::u32;
use std::env;

#[derive(Debug)]
struct Window {
    total: u32
}

struct WindowAggregator {
    previous_depth: u32,
    depth_increases: u32,
    windows: [Option<Window>; 3],
    window_head: usize,
}

impl WindowAggregator {
    fn new() -> Self {
        WindowAggregator{
            previous_depth: u32::MAX,
            depth_increases: 0,
            windows: [None, None, None],
            window_head: 0,
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
        self.window_head %= self.windows.len();
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let filename =args.get(1).expect("missing filename");
    let contents = fs::read_to_string(filename)
        .expect("Unable to read file");


    let mut aggregator = WindowAggregator::new();
    for (_, line) in contents.lines().enumerate() {
        let measurement = line.parse().unwrap();
        aggregator.add_measurement(measurement);
    }
    aggregator.add_measurement(0);
    aggregator.add_measurement(0);

    println!("number of depth increases: {}", aggregator.depth_increases);
}
