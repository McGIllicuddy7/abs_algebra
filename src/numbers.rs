use core::num;
use std::ops::{Add, AddAssign, Div, Mul, MulAssign, Rem};
pub trait Identity{
    fn one()->Self;
}
pub trait Ring: Add+Mul+AddAssign+MulAssign+Clone+PartialEq{
    fn zero()->Self;
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
pub fn gcd<T:Div<Output = T>+Rem<Output = T>+Ring+PartialOrd>(a:T, b:T)->T{
    if b>a{
        return gcd(b,a);
    } else if a== b{
        return a;
    }
    let r = a%b.clone();
    if r == T::zero(){
        return b;
    } else{
        return gcd(b, r);
    }
}

#[derive(Debug,Clone, Copy)]
pub struct Q{
    pub num:i32,
    pub denum:i32,
}

impl Q{
    pub fn simplify(&self)->Self{
        let num =self.num;
        let denum =self.denum;
        let g = gcd(num, denum);
        Self { num: num/g, denum:denum/g } 
    }
    pub fn new(num:i32, denum:i32)->Self{
        let g = gcd(num, denum);
        Self { num: num/g, denum:denum/g }
    }
    pub fn inverse(&self)->Self{
        return Self { num: self.denum, denum: self.num }
    }
    pub fn from_f64_prof(value:f64)->(Self, u64){
        let sign = value<0.0;
        let info=  (format!("{}",value).len()-1) as i32;
        let v = value.abs();
        let mut out = Self{num:1, denum:1};
        let mut diff = (f64::from(out) -v).abs();
        let mut iters =0;
        for j in i32::MAX-info..i32::MAX{
            if diff == 0.0{
                break;
            }
            let min = (v*(j as f64)-1.0).floor()as i32;
            let max =(v*(j as f64)+1.0).ceil()as i32; 
            for i in min..max+1{
                iters += 1;
                if (i-1) as f64/(j as f64)>v{
                    break;
                }
                let tmp = Self{num:i,denum:j};
                let d = (f64::from(tmp)-v).abs();
                if d<diff{
                    diff = d;
                    out = tmp;
                }
            }
        }
        if sign{
            (Self::new(out.num *-1, out.denum),iters)
        } else{
            (Self::new(out.num , out.denum),iters)
        }
    }
}
impl Add for Q{
    type Output = Self;
    fn add(self, rhs: Self) -> Self {
        Self::new(self.num*rhs.denum+rhs.num*self.denum,self.denum*rhs.denum)
    }
}
impl Mul for Q{
    type Output = Self;
    fn mul(self, rhs: Self) -> Self::Output {
        Self::new(self.num*rhs.num, self.denum*rhs.denum)
    }
}
impl Div for Q{
    type Output =  Self;
    fn div(self, rhs: Self) -> Self::Output {
        self * rhs.inverse()
    }
}

impl From<Q> for f64{
    fn from(value: Q) -> Self {
        return value.num as f64/value.denum as f64;
    }
}
impl From<f64> for Q{
    fn from(value: f64) -> Self {
        let sign = value<0.0;
        let v = value.abs();
        let mut out = Self{num:1, denum:1};
        let mut diff = (f64::from(out) -v).abs();
        for j in 1..i32::MAX{
            if diff == 0.0{
                break;
            }
            for i in 0..i32::MAX{
                if (i-1) as f64/(j as f64)>v{
                    break;
                }
                let tmp = Self{num:i,denum:j};
                let d = (f64::from(tmp)-v).abs();
                if d<diff{
                    diff = d;
                    out = tmp;
                }
            }
        }
        if sign{
            Self::new(out.num *-1, out.denum)
        } else{
            Self::new(out.num , out.denum)
        }
    }
}

impl PartialEq for Q{
    fn eq(&self, other: &Self) -> bool {
        return self.denum== other.denum && self.num == other.num
    }
}