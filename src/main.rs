use numbers::*;
use rand::{rng, Rng};

pub mod numbers;
fn main() {
    let mut count = 0;
    let mut average_counts =0;
    for i in 0..10_000{
        let fl:f64 =rng().random();
        let (v, n) = Q::from_f64_prof(fl);
        assert!((f64::from(v)-fl).abs()<0.000001);
        println!("{i}");
        count += 1;
        average_counts += n;
    }
    println!("on average took: {} iterations", average_counts as f64/ (count as f64));
    println!("{:#?}",Q::from(1./3.));
}
