use std::collections::HashMap;

fn classify(hand: &str) -> u32 {
  let mut counts: HashMap<char, u32> = HashMap::new();
  for card in hand.chars() {
    *counts.entry(card).or_insert(0) += 1;
  }

  let counts_vec: Vec<u32> = counts.values().cloned().collect();

  if counts_vec.contains(&5) {
    return 6;
  }
  if counts_vec.contains(&4) {
    return 5;
  }
  if counts_vec.contains(&3) {
    if counts_vec.contains(&2) {
      return 4;
    }
    return 3;
  }
  if counts_vec.iter().filter(|&&count| count == 2).count() == 4 {
    return 2;
  }
  if counts_vec.contains(&2) {
    return 1;
  }
  return 0;
}

fn strength(hand: &str) -> (u32, Vec<char>) {
  let letter_map: HashMap<char, char> = [('T', 'A'), ('J', 'B'), ('Q', 'C'), ('K', 'D'), ('A', 'E')]
    .iter()
    .cloned()
    .collect();

  let classified_hand = hand
    .chars()
    .map(|card| letter_map.get(&card).cloned().unwrap_or(card))
    .collect();

  (classify(hand), classified_hand)
}

fn main() {
  let mut plays: Vec<(String, u32)> = Vec::new();

  if let Ok(lines) = std::fs::read_to_string("input.txt") {
    for line in lines.lines() {
      let mut iter = line.split_whitespace();
      if let (Some(hand), Some(bid)) = (iter.next(), iter.next()) {
        plays.push((hand.to_string(), bid.parse().unwrap()));
      }
    }
  }

  plays.sort_by_key(|play| strength(&play.0));

  let mut total: u32 = 0; // Specify the type of `total` as `u32`

  for (rank, (_hand, bid)) in plays.into_iter().enumerate() {
    total += (rank + 1) as u32 * bid; // Cast `rank + 1` to `u32`
  }

  println!("{}", total);
}
