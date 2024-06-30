use std::boxed::Box;

trait Product {
    fn get_description(&self) -> String;
}

struct CPU;

impl Product for CPU {
    fn get_description(&self) -> String {
        "This is a CPU".to_string()
    }
}

struct GPU;

impl Product for GPU {
    fn get_description(&self) -> String {
        "This is a GPU".to_string()
    }
}

struct RAM;

impl Product for RAM {
    fn get_description(&self) -> String {
        "This is a RAM".to_string()
    }
}

trait ProductFactory {
    fn create_product(&self) -> Box<dyn Product>;
}

struct CPUFactory;

impl ProductFactory for CPUFactory {
    fn create_product(&self) -> Box<dyn Product> {
        Box::new(CPU)
    }
}

struct GPUFactory;

impl ProductFactory for GPUFactory {
    fn create_product(&self) -> Box<dyn Product> {
        Box::new(GPU)
    }
}

struct RAMFactory;

impl ProductFactory for RAMFactory {
    fn create_product(&self) -> Box<dyn Product> {
        Box::new(RAM)
    }
}

fn get_product_description(factory: &dyn ProductFactory) {
    let product = factory.create_product();
    println!("{}", product.get_description());
}

fn main() {
    let cpu_factory = CPUFactory;
    let gpu_factory = GPUFactory;
    let ram_factory = RAMFactory; // 添加新的 RAMFactory

    get_product_description(&cpu_factory); // 输出：This is a CPU
    get_product_description(&gpu_factory); // 输出：This is a GPU
    get_product_description(&ram_factory); // 输出：This is a RAM
}
