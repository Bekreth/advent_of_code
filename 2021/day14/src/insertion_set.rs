pub struct InsertionSet {
    pub insertion_rule: Vec<([char; 2], char)>,
}

impl InsertionSet {
    pub fn new() -> Self {
        InsertionSet {
            insertion_rule: vec![],
        }
    }

    pub fn add_insertion_rule(&mut self, rule_string: &str) {
        let chars = rule_string.chars()
            .collect::<Vec<char>>();
        let rule: [char; 2] = [
            chars[0],
            chars[1],
        ];
        self.insertion_rule.push((
            rule,
            chars[6],
        ))
    }

}