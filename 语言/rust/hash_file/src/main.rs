use rand::Rng;
use std::collections::HashMap;

const MAX_SIZE: usize = 100;

// 定义目录表条目
struct Item {
    address: Option<*const Block>,
    order: usize,
}

// 定义记录
#[derive(Clone)]
struct Record {
    name: String,
    age: String,
    city: String,
}

// 定义磁盘块
struct Block {
    record: Option<Record>,
}

// 定义目录表
struct Table {
    items: Vec<Item>,
    key_word: String,
}

// 定义文件
struct File {
    records: Vec<Record>,
}

// 定义磁盘
struct Disk {
    blocks: Vec<Block>,
}

// 自定义hash函数
fn hash(key: &str) -> usize {
    key.bytes().fold(0, |hash_value, c| (hash_value * 31 + c as usize) % MAX_SIZE)
}

// 构造文件
fn build_file(size: usize) -> File {
    File {
        records: vec![
            Record {
                name: String::new(),
                age: String::new(),
                city: String::new(),
            };
            size
        ],
    }
}

// 构造目录表
fn build_table(size: usize) -> Table {
    Table {
        items: vec![
            Item {
                address: None,
                order: 0,
            };
            size
        ],
        key_word: String::new(),
    }
}

// 构造磁盘
fn build_disk(size: usize) -> Disk {
    Disk {
        blocks: vec![
            Block {
                record: None,
            };
            size
        ],
    }
}

// 将磁盘块地址随机赋值到目录表中， 若当前条目中已存在磁盘块地址， 重新随机生成
fn store_address(disk: &Disk, table: &mut Table) {
    let mut rng = rand::thread_rng();
    for item in &mut table.items {
        loop {
            let rand_index = rng.gen_range(0..disk.blocks.len());
            let address = &disk.blocks[rand_index] as *const Block;
            if !table.items.iter().any(|x| x.address == Some(address)) {
                item.address = Some(address);
                break;
            }
        }
    }
}

// 使用线性探测法， 构造hash表 table, 而后根据table 条目中的磁盘块地址，
// 将Record 存放在磁盘块中, 并使file.records[i], table.items[j].order = i +
// 1, 为 0代表 没有相应的record映射
fn write_disk(file: &File, disk: &mut Disk, table: &mut Table) {
    for (i, record) in file.records.iter().enumerate() {
        let mut hash_value = hash(&record.name);
        loop {
            let item = &mut table.items[hash_value];
            if item.address.is_some() {
                let address = item.address.unwrap();
                unsafe {
                    (*address as *mut Block).record = Some(record.clone());
                }
                item.order = i + 1;
                break;
            }
            hash_value = (hash_value + 1) % MAX_SIZE;
        }
    }
}

// 从table 表的条目选取order!=0的条目， 根据item.address,
// 将磁盘块存放到文件record中， 并使item.order file.records[item.order - 1] =
// item.address
fn read_disk(file: &mut File, table: &Table) {
    for item in &table.items {
        if let Some(address) = item.address {
            if item.order != 0 {
                unsafe {
                    let block = &*(address as *const Block);
                    if let Some(record) = &block.record {
                        file.records[item.order - 1] = record.clone();
                    }
                }
            }
        }
    }
}

// 模拟实现， 其中file.size = MAX_SIZE /2 , disk.size = MAX_SIZE / 2, table.size
// = MAX_SIZE
fn main() {
    let file_size = MAX_SIZE / 2;
    let disk_size = MAX_SIZE / 2;
    let table_size = MAX_SIZE;

    let mut file = build_file(file_size);
    let mut disk = build_disk(disk_size);
    let mut table = build_table(table_size);

    // Fill the file with some records
    for i in 0..file_size {
        file.records[i].name = format!("Name{}", i);
        file.records[i].age = format!("{}", 20 + i);
        file.records[i].city = format!("City{}", i);
    }

    store_address(&disk, &mut table);
    write_disk(&file, &mut disk, &mut table);
    read_disk(&mut file, &table);

    // 输出文件内容
    for (i, record) in file.records.iter().enumerate() {
        println!("Record {}: Name = {}, Age = {}, City = {}", i, record.name, record.age, record.city);
    }
}
