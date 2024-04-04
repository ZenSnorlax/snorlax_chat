use std::sync::Arc;
use std::sync::Mutex;
use std::thread;
use std::usize;
fn main() {
    //定义读者计数器
    let count = Arc::new(Mutex::new(0));
    //定义读写 写写互斥量
    let file = Arc::new(Mutex::new(1));
}
