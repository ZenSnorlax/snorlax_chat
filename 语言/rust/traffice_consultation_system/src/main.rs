use std::collections::HashMap;
use std::io;

// 定义交通信息结构体
#[derive(Debug)]
struct TrafficInfo {
    road_condition: String,
    detour: String,
}

// 定义交通咨询系统结构体
struct TrafficConsultationSystem {
    data: HashMap<String, TrafficInfo>,
}

impl TrafficConsultationSystem {
    // 创建一个新的咨询系统
    fn new() -> TrafficConsultationSystem {
        TrafficConsultationSystem {
            data: HashMap::new(),
        }
    }

    // 添加交通信息
    fn add_traffic_info(&mut self, location: &str, info: TrafficInfo) {
        self.data.insert(location.to_string(), info);
    }

    // 获取交通信息
    fn get_traffic_info(&self, location: &str) -> Option<&TrafficInfo> {
        self.data.get(location)
    }
}

fn main() {
    // 初始化交通咨询系统
    let mut system = TrafficConsultationSystem::new();

    // 添加一些交通信息示例
    system.add_traffic_info(
        "Intersection A",
        TrafficInfo {
            road_condition: "Heavy traffic",
            detour: "Take Route B",
        },
    );
    system.add_traffic_info(
        "Intersection B",
        TrafficInfo {
            road_condition: "Clear",
            detour: "No detour needed",
        },
    );

    // 提示用户输入位置
    println!("Enter your current location:");
    let mut location = String::new();
    io::stdin().read_line(&mut location).expect("Failed to read line");

    // 去除输入中的换行符
    location = location.trim().to_string();

    // 根据用户输入获取交通信息
    if let Some(traffic_info) = system.get_traffic_info(&location) {
        println!("Traffic Information for {}: {:?}", &location, traffic_info);
    } else {
        println!("Traffic information not available for {}", &location);
    }
}

