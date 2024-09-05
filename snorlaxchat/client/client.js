let websocket = null;

// 监听连接按钮点击事件
document.getElementById('connect').addEventListener('click', function() {
    // 如果已经存在连接，则不再重复连接
    if (websocket !== null && websocket.readyState === WebSocket.OPEN) {
        console.log("Already connected");
        return;
    }

    // 创建 WebSocket 连接
    websocket = new WebSocket('ws://localhost:9001');

    // WebSocket 连接成功时触发
    websocket.onopen = function() {
        console.log("WebSocket connection established.");

        // 插入HTML代码
        document.getElementById("content").innerHTML = `
            <section id="send_msg_div">
                <label for="send_msg">Message:</label>
                <input id="send_msg" type="text" placeholder="Type your message here">
                <button id="send">Send</button>
            </section>
            <section>
                <h2>Received Messages</h2>
                <div id="rev_msg"></div>
            </section>`;

        // 监听 send 按钮点击事件
        document.getElementById('send').addEventListener('click', function() {
            var message = document.getElementById('send_msg').value;

            // 发送消息前确保 WebSocket 连接已经打开
            if (websocket !== null && websocket.readyState === WebSocket.OPEN) {
                websocket.send(message);
                console.log("Sent message: " + message);
            } else {
                console.log("WebSocket is not connected.");
            }
        });
    };

    // 监听 WebSocket 错误
    websocket.onerror = function(
        error) { console.error("WebSocket error: " + error); };

    // WebSocket 连接关闭时触发
    websocket.onclose = function() {
        console.log("WebSocket connection closed.");
        websocket = null; // 连接关闭后将 websocket 设为 null
    };

    // 接收服务端发送的消息
    websocket.onmessage = function(event) {
        console.log("Received message: " + event.data);

        // 创建一个新的 <p> 元素
        var newMessage = document.createElement('p');
        // 设置新元素的文本内容为接收到的消息
        newMessage.textContent = event.data;

        // 将新元素追加到指定的元素中
        document.getElementById('rev_msg').appendChild(newMessage);
    };
});

// 监听 close 按钮点击事件
document.getElementById('close').addEventListener('click', function() {
    // 确保连接存在并且是打开状态时才关闭连接
    if (websocket !== null && websocket.readyState === WebSocket.OPEN) {
        websocket.close();
        document.getElementById("content").innerHTML = "";
    } else {
        console.log("WebSocket is not connected or already closed.");
    }
});
