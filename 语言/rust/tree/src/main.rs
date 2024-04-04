use std::cell::RefCell;
use std::rc::{Rc, Weak};
#[derive(Debug)]
#[allow(dead_code)]
struct Node {
    value: i32,
    parent: RefCell<Weak<Node>>,
    childrens: RefCell<Vec<Rc<Node>>>,
}
impl Node {
    fn chang_parent(&self, parent: Rc<Node>) {
        let root = Rc::downgrade(&parent);
        *self.parent.borrow_mut() = root;
    }
    fn chang_children(&self, children: Rc<Node>) {
        self.childrens.borrow_mut().push(children.clone());
    }
}

fn main() {
    let leaf = Rc::new(Node {
        value: 3,
        parent: RefCell::new(Weak::new()),
        childrens: RefCell::new(vec![]),
    });
    let barnch = Rc::new(Node {
        value: 2,
        parent: RefCell::new(Weak::new()),
        childrens: RefCell::new(vec![]),
    });

    barnch.chang_parent(leaf.clone());
    leaf.chang_children(barnch.clone());
    //match barnch.parent.borrow().upgrade() {
      //  Some(s) => println!("branch.parent:{:?}", s),
        //None => println!("None"),
    //}
    println!("branch:{:?}", *barnch);
    
    //println!("leaf:{:?}",*leaf);
}
