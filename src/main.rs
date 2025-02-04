
use std::f64::consts::{E, PI};


use numbers::*;
use q::*;


pub mod numbers;
pub mod q;
fn main() {
    println!("{}", pow(2, 10));
    println!("{}", Q::from(0.5.exp())-exp(Q::new(1,2)));
}
