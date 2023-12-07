use std::collections::HashMap;
use std::io::{self, BufRead};

fn score(hand: &str) -> u32 {
  let counts: Vec<_> = hand.chars().map(|card| hand.chars().filter(|&c| c == card).count() as u32).collect();

  if counts.contains(&5) {
    return 6;
  }
  if counts.contains(&4) {
    return 5;
  }
  if counts.contains(&3) {
    if counts.contains(&2) {
      return 4;
    }
    return 3;
  }
  if counts.iter().filter(|&&x| x == 2).count() == 4 {
    return 2;
  }
  if counts.contains(&2) {
    return 1;
  }
  0
}

fn replacements(hand: &str) -> Vec<String> {
  if hand.is_empty() {
    return vec!["".to_string()];
  }

  let first_char_replacements: Vec<String> = if hand.starts_with('J') {
    "23456789TQKA".chars().map(|x| x.to_string()).collect()
  } else {
    vec![hand.chars().next().unwrap().to_string()]
  };

  first_char_replacements
    .into_iter()
    .flat_map(|x| replacements(&hand[1..]).iter().map(move |y| x.clone() + y).collect::<Vec<String>>())
    .collect::<Vec<String>>()
}

fn classify(hand: &str) -> u32 {
  replacements(hand).iter().map(|x| score(x)).max().unwrap_or(0)
}

fn strength(hand: &str, letter_map: &HashMap<char, char>) -> (u32, Vec<char>) {
  let classified = classify(hand);
  let mapped_hand: Vec<_> = hand.chars().map(|card| *letter_map.get(&card).unwrap_or(&card)).collect();
  (classified, mapped_hand)
}

fn main() {
  let mut letter_map = HashMap::new();
  letter_map.insert('T', 'A');
  letter_map.insert('J', '.');
  letter_map.insert('Q', 'C');
  letter_map.insert('K', 'D');
  letter_map.insert('A', 'E');

  let mut plays = Vec::new();

  for line in io::stdin().lock().lines() {
    if let Ok(line) = line {
      let mut iter = line.split_whitespace();
      if let (Some(hand), Some(bid)) = (iter.next(), iter.next()) {
        plays.push((hand.to_string(), bid.parse::<u32>().unwrap_or(0)));
      }
    }
  }

  plays.sort_by_key(|play| strength(&play.0, &letter_map));

  let mut total = 0;

  for (rank, (_hand, bid)) in plays.iter().enumerate() {
    total += (rank + 1) as u32 * *bid;
  }

  println!("{}", total);
}
