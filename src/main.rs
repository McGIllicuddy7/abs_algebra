use std::num::ParseIntError;

use numbers::*;
use rand::{rng, Rng};

pub mod numbers;
fn main() {
    let mut count = 0;
    let mut average_counts =0;
    let mut dels = 0.0;
    for _ in 0..5{
        let mut fl:f64 =rng().random();
        let mut il:i64 = rng().random();
        il = il.abs()%32;
        il =0;
        fl += il as f64;
        fl += 0.5;
        let (v, n) = Q::from_f64_prof(fl);
        let del =  (f64::from(v)-fl).abs();
        dels += del;
        if del>0.0001{
            println!("del:{del}, fl:{fl}, v_value:{}, v:{:#?}",f64::from(v), v);
        }
        count += 1;
        average_counts += n;
    }
    println!("on average took: {} iterations, {} delta", average_counts as f64/ (count as f64), dels/(count as f64));
     let (q,_) = Q::from_f64_prof(8./100.);
     println!("q:{:#?}\nf:{}",q,f64::from(q));
    let q1 = Q::new(1,2);
    let q2 = Q::new(3,2);
    println!("q1:{:#?}, q2:{:#?}, q1+q2{:#?}", q1, q2, q1+q2);
}
