use ::std::env;
use ::std::fs;
fn main() {
    let args: Vec<String> = env::args().collect();
    let config = Config::new(&args);
    println!("Searching for {} in {}", config.query, config.file_path);
    let contents =
        fs::read_to_string(config.file_path).expect("Should haven been able to read the fiel");
    println!("with text:\n{}", contents);
}
struct Config {
    query: String,
    file_path: String,
}
impl Config {
    fn new(args: &Vec<String>) -> Config {
        if args.len() < 3 {
            panic!("not enough arguments");
        }
        let query = args[1].clone();
        let file_path = args[2].clone();
        Config { query, file_path }
    }
}
