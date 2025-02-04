use crate::numbers::*;
use std::{f64::consts::E, ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Sub, SubAssign}};
#[derive(Debug,Clone, Copy)]
pub struct Q{
    pub num:i64,
    pub denum:i64,
}

impl Q{
    pub fn simplify(&self)->Self{
        let num =self.num;
        let denum =self.denum;
        let g = gcd(num, denum);
        let sign = if denum<0{-1} else{1};
        Self { num: num/g*sign, denum:denum/g*sign } 
    }
    pub fn new(num:i32, denum:i32)->Self{
        let sign = if denum <0 {
            -1
        } else{
            1
        };
        if num == 0{
            return Self::zero();
        }
        let g = gcd(num.abs(), denum);
        Self { num: (num/g)as i64*sign, denum:(denum/g)as i64*sign }
    }
    pub fn new_i64(num:i64, denum:i64)->Self{
        let sign = if denum <0 {
            -1
        } else{
            1
        };
        if num == 0{
            return Self::zero();
        }
        let g = gcd(num, denum);
        Self { num: (num/g)as i64*sign, denum:(denum/g)as i64 *sign} 
    }
    pub fn inverse(&self)->Self{
        return Self::new_i64( self.denum,  self.num )
    }
    pub fn from_f64_prof(value:f64)->(Self, u64){
        let sign = value<0.0;
        let v = (value.abs()- value.abs().floor()).abs();
        let s = format!("{}",v);
        let info=  (s.len()) as i32;
        let mut iters =0;
        if info >10{
            iters = 2;
            let base:i32 = value.abs().floor() as i32;
            let mut second = 0;
            let mut denum = 1;
            let mut strs = s.split('.');
            let _ = strs.next().expect("msg");
            let s2 = strs.next();
            if let Some(mut l) = s2{
                if l.len()>9{
                    l = &l[0..9];
                }
                denum = 10_i64.pow(l.len() as u32);
                second = l.parse().expect("msg");
            }
            let sn = if sign{
                -1
            } else{
                1
            };
            return (Q::new(sn*base,1) +Q::new(sn*second, denum as i32), iters);
        }
        let ipart = Self::new_i64((value-v) as i64, 1);
       // println!("value: {value},ipart:{:#?}", ipart);
        let mut out = Self::one();
        let mut diff = (f64::from(out) -v).abs();
 
        for j in info-1..info*info*info/2{
            assert!(j>0);
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
                assert!(i>0);
                iters += 1;
                if (i-1) as f64/(j as f64)>v{
                    break;
                }
                let tmp = Self::new_i64(i as i64, j as i64);
                let d = (f64::from(tmp)-v).abs();
                if d<diff{
                    diff = d;
                    out = tmp;
                    if diff<0.0001{
                        break;
                    }
                } 
            }
        }
        out = Self::new_i64(out.num+ipart.num*out.denum, out.denum);
        out = if sign{
            Self::new((out.num*-1) as i32, (out.denum) as i32)
        } else{
            Self::new_i64(out.num, out.denum)
        };
        (out,iters)
    }
}
impl Add for Q{
    type Output = Self;
    fn add(self, rhs: Self) -> Self {
        if rhs.num == 0 {
            return self;
        }
        if self.num == 0{
            return rhs;
        }
        let out = Self::new_i64(self.num*rhs.denum+rhs.num*self.denum,rhs.denum*self.denum);
        out
    }
}
impl Sub for Q{ 
    type Output = Self;
    fn sub(self, rhs: Self) -> Self::Output {
        self + Self::new_i64(-rhs.num, rhs.denum)
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

impl AddAssign for Q{
    fn add_assign(&mut self, rhs: Self) {
        *self = *self+rhs;
    }
}
impl SubAssign for Q{
    fn sub_assign(&mut self, rhs: Self) {
        *self = *self-rhs;
    }
}
impl DivAssign for Q{
    fn div_assign(&mut self, rhs: Self) {
        *self = *self/rhs;
    }
}
impl MulAssign for Q{
    fn mul_assign(&mut self, rhs: Self) {
        *self = *self*rhs;
    }
}
impl Add<i32> for Q{
    type Output =Self;
    fn add(self, rhs: i32) -> Self::Output {
        self+Self::from(rhs)
    }
}
impl Sub<i32> for Q{
    type Output = Self;
    fn sub(self, rhs: i32) -> Self::Output {
        self -Self::from(rhs)
    }
}
impl Mul<i32> for Q{
    type Output = Self;
    fn mul(self, rhs: i32) -> Self::Output {
        self*Self::from(rhs)
    }
}
impl Div<i32> for Q{
    type Output =  Self;
    fn div(self, rhs: i32) -> Self::Output {
        self/ Self::from(rhs)
    } 
}
impl AddAssign<i32> for Q{
    fn add_assign(&mut self, rhs:i32) {
        *self = *self+rhs;
    }
}
impl SubAssign<i32> for Q{
    fn sub_assign(&mut self, rhs:i32) {
        *self = *self-rhs;
    }
}
impl DivAssign<i32> for Q{
    fn div_assign(&mut self, rhs: i32) {
        *self = *self/rhs;
    }
}
impl MulAssign<i32> for Q{
    fn mul_assign(&mut self, rhs: i32) {
        *self = *self*rhs;
    }
}
impl Add<f64> for Q{
    type Output =Self;
    fn add(self, rhs: f64) -> Self::Output {
        self+Self::from(rhs)
    }
}
impl Sub<f64> for Q{
    type Output = Self;
    fn sub(self, rhs: f64) -> Self::Output {
        self -Self::from(rhs)
    }
}
impl Mul<f64> for Q{
    type Output = Self;
    fn mul(self, rhs: f64) -> Self::Output {
        self*Self::from(rhs)
    }
}
impl Div<f64> for Q{
    type Output =  Self;
    fn div(self, rhs: f64) -> Self::Output {
        self/ Self::from(rhs)
    }
}
impl AddAssign<f64> for Q{
    fn add_assign(&mut self, rhs:f64) {
        *self = *self+rhs;
    }
}
impl SubAssign<f64> for Q{
    fn sub_assign(&mut self, rhs:f64) {
        *self = *self-rhs;
    }
}
impl DivAssign<f64> for Q{
    fn div_assign(&mut self, rhs: f64) {
        *self = *self/rhs;
    }
}
impl MulAssign<f64> for Q{
    fn mul_assign(&mut self, rhs:f64) {
        *self = *self*rhs;
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
        let v = (value.abs()- value.abs().floor()).abs();
        let s = format!("{}",v);
        let info=  (s.len()) as i32;
        if info >10{
            let base:i32 = value.abs().floor() as i32;
            let mut second = 0;
            let mut denum = 1;
            let mut strs = s.split('.');
            let _ = strs.next().expect("msg");
            let s2 = strs.next();
            if let Some(mut l) = s2{
                if l.len()>9{
                    l = &l[0..9];
                }
                denum = 10_i64.pow(l.len() as u32);
                second = l.parse().expect("msg");
            }
            let sn = if sign{
                -1
            } else{
                1
            };
            return Q::new(sn*base,1) +Q::new(sn*second, denum as i32);
        }
        let ipart = Self::new_i64((value-v) as i64, 1);
        let mut out = Self::one();
        let mut diff = (f64::from(out) -v).abs();
        for j in info-1..info*info*info/2{
            assert!(j>0);
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
                assert!(i>0);
                if (i-1) as f64/(j as f64)>v{
                    break;
                }
                let tmp = Self::new_i64(i as i64, j as i64);
                let d = (f64::from(tmp)-v).abs();
                if d<diff{
                    diff = d;
                    out = tmp;
                    if diff<0.0001{
                        break;
                    }
                } 
            }
        }
        out = Self::new_i64(out.num+ipart.num*out.denum, out.denum);
        out = if sign{
            Self::new((out.num*-1) as i32, (out.denum) as i32)
        } else{
            Self::new_i64(out.num, out.denum)
        };
        out
    }
}

impl From<i32> for Q{
    fn from(value: i32) -> Self {
        return Self { num: value as i64, denum: 1 };
    }
}
impl std::fmt::Display for Q{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f,"{}/{}", self.num, self.denum)
    }
}
impl PartialEq for Q{
    fn eq(&self, other: &Self) -> bool {
        return self.denum== other.denum && self.num == other.num
    }
}
impl PartialOrd for Q{
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        let p1 = self.num * other.denum;
        let p2 = other.num*self.denum;
        if p1>p2{
            Some(std::cmp::Ordering::Greater)
        } else if p1 == p2{
            Some(std::cmp::Ordering::Equal)
        } else{
            Some(std::cmp::Ordering::Less)
        }
    }
}
impl Identity for Q{
    fn one()->Self {
        Self { num: 1, denum: 1 } 
    }
}
impl Ring for Q{
    fn zero()->Self {
        Self { num: 0, denum: 1 }
    }
}

impl Field for Q{

}
impl Exp for Q{
    fn exp(self)->Self {
        let n = self.num;
        let denum = self.denum;
        let f = 1.0/(denum as f64);
        let g = E.powi(n as i32);
        let t = g.powf(1.0/f);
        Self::from(t)
    }
}