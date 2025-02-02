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
pub fn gcd<T:Div<Output = T>+Rem<Output = T>+Ring+PartialOrd>(a0:T, b0:T)->T{
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

#[derive(Debug,Clone, Copy)]
pub struct Q{
    pub num:i64,
    pub denum:i64,
}

impl Q{
    pub fn simplify(&self)->Self{
        let num =self.num;
        let denum =self.denum;
        let g = 1;//gcd(num, denum);
        Self { num: num/g, denum:denum/g } 
    }
    pub fn new(num:i32, denum:i32)->Self{
        let g = gcd(num.abs(), denum);
        assert!(g>0);
        Self { num: (num/g)as i64, denum:(denum/g)as i64 }
    }
    pub fn new_i64(num:i64, denum:i64)->Self{
        let g = gcd(num, denum);
        assert!(g>0);
        assert!(num>0);
        assert!(denum>0);
        Self { num: (num/g)as i64, denum:(denum/g)as i64 } 
    }
    pub fn inverse(&self)->Self{
        return Self { num: self.denum, denum: self.num }
    }
    pub fn from_f64_prof(value:f64)->(Self, u64){
        let sign = value<0.0;
        let v = (value.abs()- value.abs().floor()).abs();
        let mut info=  (format!("{}",v).len()) as i32;
        let ipart = Self{num:(value-v) as i64, denum:1};
       // println!("value: {value},ipart:{:#?}", ipart);
        let mut out = Self{num:1, denum:1};
        let mut diff = (f64::from(out) -v).abs();
        let mut iters =0;
        for j in i32::MAX-info..i32::MAX{
            if diff == 0.0{
                break;
            }
            let mut min = (v*(j as f64)-1.0).floor()as i32;
            if min <= 0{
                min = 1;
            }
            let mut  max =(v*(j as f64)+1.0).ceil()as i32; 
            if max <= 0{
                max = 1;
            }
            for i in min..max{
                iters += 1;
                if (i-1) as f64/(j as f64)>v{
                    break;
                }
                let tmp = Self::new(i, j);
                let d = (f64::from(tmp)-v).abs();
                if d<diff{
                    diff = d;
                    out = tmp;
                }
            }
        }
        out = Self::new_i64(out.num+ipart.num*out.denum, out.denum);
        out = if sign{
            Self::new((out.num*-1) as i32, (out.denum) as i32)
        } else{
            Self::new((out.num) as i32 , (out.denum) as i32)
        };
        (out,iters)
    }
}
impl Add for Q{
    type Output = Self;
    fn add(self, rhs: Self) -> Self {
        assert!(self.denum>0 && self.num>0 && rhs.denum>0 && rhs.num>0);
        let out = Self::new_i64(self.num*rhs.denum+rhs.num*self.denum,rhs.denum*self.denum);
        out
    }
}
impl Mul for Q{
    type Output = Self;
    fn mul(self, rhs: Self) -> Self::Output {
        Self::new((self.num*rhs.num) as i32, (self.denum*rhs.denum) as i32)
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
        let info=  (format!("{}",value).len()-1) as i32;
        let v = value.abs();
        let mut out = Self{num:1, denum:1};
        let mut diff = (f64::from(out) -v).abs();
        for j in i32::MAX-info..i32::MAX{
            if diff == 0.0{
                break;
            }
            let min = (v*(j as f64)-1.0).floor()as i32;
            let max =(v*(j as f64)+1.0).ceil()as i32; 
            for i in min..max+1{
                if (i-1) as f64/(j as f64)>v{
                    break;
                }
                let tmp = Self{num:i as i64,denum:j as i64};
                let d = (f64::from(tmp)-v).abs();
                if d<diff{
                    diff = d;
                    out = tmp;
                }
            }
        }
        if sign{
            Self::new((out.num *-1) as i32, (out.denum) as i32)
        } else{
            Self::new((out.num) as i32 , (out.denum) as i32)
        }
    }
}

impl PartialEq for Q{
    fn eq(&self, other: &Self) -> bool {
        return self.denum== other.denum && self.num == other.num
    }
}