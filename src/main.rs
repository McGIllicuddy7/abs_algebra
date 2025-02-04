


pub use numbers::*;
pub use q::*;
pub use matrix::*;

pub mod numbers;
pub mod q;
pub mod matrix;
fn main() {
    let m = Matrix::new([[2.0,0.0],[0.0,2.0]]);
    println!("{}",m.inverse()*m);
}
