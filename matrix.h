/*use std::ops::{Add, AddAssign, Index, IndexMut, Mul, MulAssign, Sub, SubAssign};

pub use crate::numbers::*;
#[derive(PartialEq, Debug)]
pub struct Matrix<T:Ring+Identity>{
    data: Box<[T]>, 
    height:usize, 
    width:usize,
}
impl <T:Clone+Ring+Identity> Clone for Matrix<T>{
    fn clone(&self) -> Self {
        Self { data: self.data.clone(), height: self.height.clone(), width: self.width.clone() }
    }
}
impl <T:std::fmt::Display + Identity+ Ring> std::fmt::Display for Matrix<T>{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let mut out = "[".to_string();
        for i in 0..self.height{
            let mut tmp = "[".to_string();
            for j in 0..self.width{
                tmp += &format!("{}", self.get(j,i));
                if j != self.width-1{
                    tmp += ",";
                }
            }
            tmp += "]";
            out += &tmp;
        }
        out += "]";
        write!(f, "{}",out)
    }
}
impl <T:Ring+Identity>Index<usize> for Matrix<T> {
    type Output = [T];
    fn index(&self, index: usize) -> &Self::Output {
        assert!(index<self.height);
        &self.data[index*self.width..(index+1)*self.width]
    }
}
impl <T:Ring+Identity>IndexMut<usize> for Matrix<T> {
    fn index_mut(&mut self, index: usize) -> &mut Self::Output {
        assert!(index<self.height);
        &mut self.data[index*self.width..(index+1)*self.width]
    }
}
impl <T:Ring+Identity>Add for Matrix<T>{
    type Output = Self;
    fn add(self, rhs: Self) -> Self::Output {
        if rhs.height == 1 && rhs.width == 1{
            return self.clone() + Self::identity(self.height, self.width)*rhs.get(0, 0).clone();
        }
        if self.height == 1 && self.width == 1{
            return Self::identity(self.height, self.width)*self.get(0, 0).clone()+rhs; 
        }
        assert!(self.height == rhs.height);
        assert!(self.width == rhs.width);
        let mut bx = Vec::new();
        bx.reserve_exact(self.width*self.height);
        for i in 0..self.data.len(){
            bx.push(self.data[i].clone()+rhs.data[i].clone());
        }
        Self{data:bx.into_boxed_slice(), height:self.height, width:self.width}
    }
}
impl <T:Ring+Identity>AddAssign for Matrix<T>{
    fn add_assign(&mut self, rhs: Self) {
        *self = self.clone()+rhs;
    }
}
impl <T:Ring+Identity>Sub for Matrix<T>{
    type Output = Self;
    fn sub(self, rhs: Self) -> Self::Output {
        if rhs.height == 1 && rhs.width == 1{
            return self.clone() - Self::identity(self.height, self.width)*rhs.get(0, 0).clone();
        }
        if self.height == 1 && self.width == 1{
            return Self::identity(self.height, self.width)*self.get(0, 0).clone()-rhs; 
        }
        assert!(self.height == rhs.height);
        assert!(self.width == rhs.width);
        let mut bx = Vec::new();
        bx.reserve_exact(self.width*self.height);
        for i in 0..self.data.len(){
            bx.push(self.data[i].clone()-rhs.data[i].clone());
        }
        Self{data:bx.into_boxed_slice(), height:self.height, width:self.width}
    }
}
impl <T:Ring+Identity>SubAssign for Matrix<T>{
    fn sub_assign(&mut self, rhs: Self) {
        *self = self.clone()-rhs;
    }
}
impl <T:Ring+Identity>Mul for Matrix<T>{
    type Output = Self;
    fn mul(self, rhs: Self) -> Self::Output {
        if rhs.width == 1 && rhs.height == 1 {
            return self * rhs.get(0, 0).clone();
        }
        if self.width == 1 && self.height == 1{
            return rhs*self.get(0, 0).clone();
        }
        assert!(self.width == rhs.height);
        let mut  out = Self::zeroed(self.height, rhs.width);
        for i in 0..out.width{
            for j in 0..out.height{
                for k in 0..self.width{
                    out.data[j*out.width+i] += self.data[j*self.width+k].clone()*rhs.data[k*rhs.width+i].clone(); 
                }
            }
        }
        return out;
    }
}
impl <T:Ring+Identity>MulAssign for Matrix<T>{
    fn mul_assign(&mut self, rhs: Self) {
        *self = self.clone()*rhs;
    }
}
impl <T:Ring+Identity> Mul<T> for Matrix<T>{
    type Output=Self;
    fn mul(self, rhs: T) -> Self::Output {
        let mut out = self.clone();
        for i in &mut out.data{
            *i*= rhs.clone();
        }
        out
    }
} 
impl <T:Ring+Identity> Matrix<T> {
    pub fn zeroed(height:usize, width:usize)->Self{
        let mut vs = Vec::new();
        vs.reserve_exact(height*width);
        for _ in 0..height*width{
            vs.push(T::zero());
        }
        Self{data:vs.into_boxed_slice(), height, width}
    }
    pub fn identity(height:usize, width:usize)->Self{
        let mut vs = Vec::new();
        vs.reserve_exact(height*width);
        for i in 0..height{
            for j in 0..width{
                if i == j{
                    vs.push(T::one())
                } else{
                    vs.push(T::zero());
                }

            }

        }
        Self{data:vs.into_boxed_slice(), height, width} 
    }
    pub fn get(&self, x:usize, y:usize)->&T{
        &self[y][x]
    }
    pub fn set(&mut self, x:usize, y:usize, v:T){
        self[y][x] = v;
    }
    pub fn swap_rows(&mut self, r0:usize, r1:usize){
        for i in 0..self.width {
            let tmp0 = self.get(i, r0).clone();
            let tmp1 = self.get(i, r1).clone();
            self.set(i, r1, tmp0);
            self.set(i, r0, tmp1);
        }
    }
    pub fn scale_row(&mut self, row:usize, scale:T){
        for i in 0..self.width{
            self[row][i] *= scale.clone();
        }
    }
    pub fn sub_rows(&mut self, r0:usize, r1:usize, scale:T){
        for i in 0..self.width{
            let tmp0 = self.get(i, r0).clone()*scale.clone();
            let tmp1 = self.get(i, r1).clone();
            self.set(i, r1, tmp1-tmp0);
        }
    }
    pub fn add_rows(&mut self, r0:usize, r1:usize, scale:T){
        for i in 0..self.width{
            let tmp0 = self.get(i, r0).clone()*scale.clone();
            let tmp1 = self.get(i, r1).clone();
            self.set(i, r1, tmp1+tmp0);
        } 
    }
    pub fn new<const HEIGHT:usize, const WIDTH:usize>(v:[[T; WIDTH]; HEIGHT])->Self{
        let mut bx = Vec::new();
        for i in v{
            for j in i{
                bx.push(j);
            }
        }
        Self { data: bx.into_boxed_slice(), height: HEIGHT, width: WIDTH }
    } 
    pub fn new_from_slice(v:&[T], height:usize, width:usize)->Self{
        Self{data: v.into(), height, width}
    }
    pub fn new_from_vec(v:Vec<T>, height:usize, width:usize)->Self{
        Self{data: v.into(), height, width}
    }
    pub fn new_from_vec_vec(v:Vec<Vec<T>>)->Self{
        let height = v.len();
        let width = v[0].len();
        Self{data:v.into_iter().flatten().collect::<Vec<T>>().into_boxed_slice(), height, width}
    }
}



#[allow(unused)]
impl <T:Field> Matrix<T>{
    pub fn pair_row_reduce(source:Matrix<T>, target:Matrix<T>)->(Matrix<T>, Matrix<T>) {
        let mut mtrx = source.clone();
        let mut out = target.clone();
        for i in 0..mtrx.width {
            let mut r = i;
            let mut degen = false;
            while *mtrx.get(i, r) == T::zero() {
                r = r+1;
                if r >= mtrx.height {
                    degen = true;
                    break;
                }
            }
            if degen {
                continue;
            }
            if r != i {
                out.swap_rows(r, i);
                mtrx.swap_rows(r, i);
            }
            let v = mtrx.get(i, i).clone();
            mtrx.scale_row(i, T::one()/v.clone());
            out.scale_row(i, T::one()/v.clone());
            for j in 0..mtrx.height{
                if j == i {
                    continue
                }
                let mlt = mtrx.get(i, j).clone();
                mtrx.sub_rows(i, j, mlt.clone());
                out.sub_rows(i, j, mlt.clone());
            }
        }
        return (mtrx, out)
    }
    pub fn row_reduce(matrx:Matrix<T>)->Matrix<T> {
        let mut mtrx = matrx.clone();
        for i in 0..mtrx.width {
            let mut r = i;
            let mut degen = false;
            while *mtrx.get(i, r) == T::zero(){
                r+=1;
                if r >= mtrx.height {
                    degen = true;
                    break;
                }
            }
            if degen {
                continue
            }
            if r != i {
                mtrx.swap_rows(r, i);
            }
            let v = mtrx.get(i, i).clone();
            mtrx.scale_row(i, T::one()/v.clone());
            for j in 0..mtrx.height {
                if j == i {
                    continue
                }
                let mlt = mtrx.get(i, j).clone();
                mtrx.sub_rows(i, j, mlt);
            }
        }
        return mtrx;
    }
    pub fn determinant(&self)->T{
        let mut mtrx = self.clone();
        let mut out = T::one();
        for i  in 0..mtrx.width {
            let mut r = i;
            let mut degen= false;
            while *mtrx.get(i,r) ==  T::zero() {
                r = r+1;
                if r >= mtrx.height {
                    degen = true;
                    break;
                }
            }
            if degen {
                return T::zero();
            }
            if r != i {
                mtrx.swap_rows(r, i);
                out *= (T::zero()-T::one());
            }
            let v = mtrx.get(i, i).clone();
            mtrx.scale_row(i, T::one()/v.clone());
            out *= v.clone();
            for j in 0..mtrx.height{
                if j == i {
                    continue
                }
                let mlt = mtrx.get(i, j).clone();
                if mlt == T::zero() {
                    continue;
                }
                mtrx.sub_rows(i, j, mlt.clone());
            }
        }
        return out
    }
    pub fn to_upper_triangular(&self)->Matrix<T> {
        let mut mtrx = self.clone();
        for i in 0..mtrx.width {
            let mut r = i;
            let mut degen = false;
            while *mtrx.get(i, r) == T::zero() {
                r = r+1;
                if r >= mtrx.height {
                    degen = true;
                    break;
                }
            }
            if degen {
                continue
            }
            if r != i {
                mtrx.swap_rows(r, i)
            }
            let v = mtrx.get(i, i).clone();
            mtrx.scale_row(i, T::one()/v);
            for j in r..self.height {
                if j == i {
                    continue;
                }
                let mlt = mtrx.get(i, j).clone();
                mtrx.sub_rows(i, j, mlt);
            }
        }
        for i in 0..mtrx.width {
            let mut r = i;
            let mut degen = false;
            while *mtrx.get(i, r) == T::zero() {
                r = r+1;
                if r >= mtrx.height {
                    degen = true;
                    break;
                }
            }
            if degen {
                continue;
            }
            if r != i {
                mtrx.swap_rows(r, i);
            }
            let v = mtrx.get(i, i).clone();
            mtrx.scale_row(i, T::one()/v);
            for j in r..mtrx.height {
                if j == i {
                    continue
                }
                let mlt = mtrx.get(i, j).clone();
                mtrx.sub_rows(i, j, mlt);
            }
        }
        return mtrx
    }
    pub fn inverse(&self)-> Matrix<T> {
        let (_, out) = Matrix::pair_row_reduce(self.clone(), Self::identity(self.height, self.width));
        return out
    }
    pub fn eigenvalues(&self)->Vec<T>{
        assert!(self.height == self.width);
        todo!();
    }
    pub fn eigenvectors(&self)->Vec<Matrix<T>>{
        todo!()
    }
}

impl <T:Ring+Identity>Ring for Matrix<T>{
    fn zero()->Self {
        Self { data: Box::new([T::zero()]), height: 1, width: 1 }
    }
}

impl <T:Ring+Identity> Identity for Matrix<T>{
    fn one()->Self {
        Self { data: Box::new([T::one()]), height: 1, width: 1 } 
    }
}
    */