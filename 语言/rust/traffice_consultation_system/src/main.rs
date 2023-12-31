use std::collections::HashMap;  
use std::io;  
  
#[derive(Debug)]
#[allow(dead_code)]
struct TrafficInfo {  
    road_condition: String,  
    detour: String,  
}  
  
struct TrafficConsultationSystem {  
    data: HashMap<String, TrafficInfo>,  
}  
  
impl TrafficConsultationSystem {  
    fn new() -> TrafficConsultationSystem {  
        TrafficConsultationSystem {  
            data: HashMap::new(),  
        }  
    }  
  
    fn add_traffic_info(&mut self, location: &str, info: TrafficInfo) {  
        self.data.insert(location.to_string(), info);  
    }  
  
    fn get_traffic_info(&self, location: &str) -> Option<&TrafficInfo> {  
        self.data.get(location)  
    }  
}  
  
fn main() {  
    let mut system = TrafficConsultationSystem::new();  
  
    system.add_traffic_info(  
        "Intersection A",  
        TrafficInfo {  
            road_condition: "Heavy traffic".to_string(),  
            detour: "Take Route B".to_string(),  
        },  
    );  
    system.add_traffic_info(  
        "Intersection B",  
        TrafficInfo {  
            road_condition: "Clear".to_string(),  
            detour: "No detour needed".to_string(),  
        },  
    );  
  
    println!("Enter your current location:");  
    let mut location = String::new();  
    if let Ok(read) = io::stdin().read_line(&mut location) {  
        if read > 0 { // 检查读取的字节数，确保输入不为空行  
            location = location.trim().to_string(); // 去除换行符并转换为字符串  
            if let Some(traffic_info) = system.get_traffic_info(&location) {  
                println!("Traffic Information for {}: {:?}", &location, traffic_info);  
            } else {  
                println!("Traffic information not available for {}", &location);  
            }  
        } else { // 如果读取的字节数为0，说明用户输入了空行，这里可以给出提示或跳过这一部分处理。这里简单地打印一个警告信息。  
            println!("Warning: Empty input received.");  
        }  
    } else { // 读取失败，给出错误信息并退出程序。这里简单地打印一个错误信息并终止程序。注意，这只是一个示例，实际应用中可能需要更详细的错误处理。  
        println!("Error reading input line.");  
        std::process::exit(1); // 退出程序，返回状态码1。实际应用中可能需要更合适的错误处理逻辑。  
    }  
}

