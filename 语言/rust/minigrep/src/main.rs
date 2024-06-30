use std::env;
use std::process;
use minigrep::Config;

fn main() {
    let config = Config::new(env::args()).unwrap_or_else(|err| {
      eprintln!("Proble parasing arguments: {}", err);
        process::exit(1);
    });

    //println!("Searching for {}", config.query);
    //println!("In file {}", config.filename);
    if let Err(e) = minigrep::run(&config) {
        eprintln!("Applications error:{}", e);
        process::exit(1);
    }
}
