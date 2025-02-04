
use std::{f64::consts::E, fmt::Debug, ops::{Add, AddAssign, Div, Mul, MulAssign, Rem, Sub, SubAssign}};

pub trait Identity{
    fn one()->Self;
}
pub trait Ring: Add<Output = Self>+Sub<Output= Self> + SubAssign+Mul<Output = Self>+AddAssign+MulAssign+Clone+PartialEq+Debug{
    fn zero()->Self;
    fn derivitive()->Self{
        Self::zero()
    }
}
pub trait Field:Ring+Identity+Div<Output = Self>{

}
impl Ring for f64{
    fn zero()->Self {
        return 0.0;
    }
}
impl Ring for f32 {
    fn zero()->Self {
        return 0.0;
    }
}
impl Ring for u128{
    fn zero()->Self {
        return 0;
    }
}
impl Ring for u64{
    fn zero()->Self {
        return 0;
    }
}
impl Ring for u32{
    fn zero()->Self {
        return 0;
    }
}
impl Ring for u16{
    fn zero()->Self {
        return 0;
    }
}
impl Ring for u8{
    fn zero()->Self {
        return 0;
    }
}
impl Ring for i128{
    fn zero()->Self {
        return 0;
    }
}
impl Ring for i64{
    fn zero()->Self {
        return 0;
    }
}
impl Ring for i32{
    fn zero()->Self {
        return 0;
    }
}
impl Ring for i16{
    fn zero()->Self {
        return 0;
    }
}
impl Ring for i8{
    fn zero()->Self {
        return 0;
    }
}
impl Identity for f64{
    fn one()->Self{
        return 1.0;
    }
}
impl Identity for f32{
    fn one()->Self{
        return 1.0;
    }
}

impl Identity for u128{
    fn one()->Self{
        return 1;
    }
}
impl Identity for u64{
    fn one()->Self{
        return 1;
    }
}

impl Identity for u32{
    fn one()->Self{
        return 1;
    }
}
impl Identity for u16{
    fn one()->Self{
        return 1;
    }
}
impl Identity for u8{
    fn one()->Self{
        return 1;
    }
}
impl Identity for i128{
    fn one()->Self{
        return 1;
    }
}
impl Identity for i64{
    fn one()->Self{
        return 1;
    }
}
impl Identity for i32{
    fn one()->Self{
        return 1;
    }
}
impl Identity for i16{
    fn one()->Self{
        return 1;
    }
}
impl Identity for i8{
    fn one()->Self{
        return 1;
    }
}
impl Field for f32{

}
impl Field for f64{

}
pub trait Exp {
    fn exp(self)->Self;
    fn cos(self)->Self;
    fn sin(self)->Self;
}
impl Exp for f32{
    fn exp(self)->Self {
        self.exp()
    }
    fn cos(self)->Self {
        self.cos()
    }
    fn sin(self)->Self {
        self.sin()
    }
}
impl Exp for f64{
    fn exp(self)->Self {
        self.exp()
    }
    fn cos(self)->Self {
        self.cos()
    }
    fn sin(self)->Self {
        self.sin()
    }
}
impl Exp for i8{
    fn exp(self)->Self {
        return pow(E, self as u128) as Self
    }
    fn cos(self)->Self {
        (self as f64).cos().round() as Self
    }
    fn sin(self)->Self {
        (self as f64).sin().round() as Self
    }
}
impl Exp for i16{
    fn exp(self)->Self {
        return pow(E, self as u128) as Self
    }
    fn cos(self)->Self {
        (self as f64).cos().round() as Self
    }
    fn sin(self)->Self {
        (self as f64).sin().round() as Self
    }
}
impl Exp for i32{
    fn exp(self)->Self {
        return pow(E, self as u128) as Self
    }
    fn cos(self)->Self {
        (self as f64).cos().round() as Self
    }
    fn sin(self)->Self {
        (self as f64).sin().round() as Self
    }
}
impl Exp for i64{
    fn exp(self)->Self {
        return pow(E, self as u128) as Self
    }
    fn cos(self)->Self {
        (self as f64).cos().round() as Self
    }
    fn sin(self)->Self {
        (self as f64).sin().round() as Self
    }
}
impl Exp for i128{
    fn exp(self)->Self {
        return pow(E, self as u128) as Self
    }
    fn cos(self)->Self {
        (self as f64).cos().round() as Self
    }
    fn sin(self)->Self {
        (self as f64).sin().round() as Self
    }
}
impl Exp for u8{
    fn exp(self)->Self {
        return pow(E, self as u128) as Self
    }
    fn cos(self)->Self {
        (self as f64).cos().round() as Self
    }
    fn sin(self)->Self {
        (self as f64).sin().round() as Self
    }
}
impl Exp for u16{
    fn exp(self)->Self {
        return pow(E, self as u128) as Self
    }
    fn cos(self)->Self {
        (self as f64).cos().round() as Self
    }
    fn sin(self)->Self {
        (self as f64).sin().round() as Self
    }
}
impl Exp for u32{
    fn exp(self)->Self {
        return pow(E, self as u128) as Self
    }
    fn cos(self)->Self {
        (self as f64).cos().round() as Self
    }
    fn sin(self)->Self {
        (self as f64).sin().round() as Self
    }
}
impl Exp for u64{
    fn exp(self)->Self {
        return pow(E, self as u128) as Self
    }
    fn cos(self)->Self {
        (self as f64).cos().round() as Self
    }
    fn sin(self)->Self {
        (self as f64).sin().round() as Self
    }
}
impl Exp for u128{
    fn exp(self)->Self {
        return pow(E, self as u128) as Self
    }
    fn cos(self)->Self {
        (self as f64).cos().round() as Self
    }
    fn sin(self)->Self {
        (self as f64).sin().round() as Self
    }
}
pub fn gcd<T:Ring+Div<Output = T>+Identity+Rem<Output = T>+PartialOrd>(a0:T, b0:T)->T{
    let mut a = a0;
    let mut b = b0;
    if b>a{
        return gcd(b,a);
    }
    else if a== b{
        return a;
    }
    loop{
        let r = a.clone()%b.clone();
        if r == T::zero(){
            return b;
        } else{
            a = b;
            b = r;
        }
    }
}

pub fn pow<T:Ring>(v:T, count: u128)->T{
    let mut out = v.clone();
    for _ in 0..count-1{
        out *= v.clone()
    }
    out
}

pub fn exp<T:Exp>(v:T)->T{
    v.exp()
}
pub fn cos<T:Exp>(v:T)->T{
    v.cos()
}
pub fn sin<T:Exp>(v:T)->T{
    v.sin()
}