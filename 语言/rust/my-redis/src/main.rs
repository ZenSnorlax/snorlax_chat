use mini_redis::{Connection, Frame};
use tokio::net::{TcpListener, TcpStream};

#[tokio::main]
async fn main() {
    //bind the listener to the address
    //监听指定地址 等待Tcp连接起来
    let listener = TcpListener::bind("127.0.0.1:6379").await.unwrap();

    loop {
        //第二个被忽略的项中包含新连接的'IP'和端口信息
        let (socket, _) = listener.accept().await.unwrap();
        tokio::spawn(async move {
            process(socket).await;
        });
    }
}
async fn process(socket: TcpStream) {
    let mut connection = Connection::new(socket);
    if let Some(frame) = connection.read_frame().await.unwrap() {
        println!("GOT:{:?}", frame);
        //回复一个错误
        let response = Frame::Error("unimplemented".to_string());
        connection.write_frame(&response).await.unwrap();
    }
}
