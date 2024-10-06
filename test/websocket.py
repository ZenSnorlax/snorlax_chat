import asyncio
import websockets
import aioconsole


async def send_message(websocket):
    while True:
        message = await aioconsole.ainput("Enter message to send: ")  # 使用异步输入
        await websocket.send(message)
        print(f"Sent: {message}")


async def receive_message(websocket):
    while True:
        try:
            response = await websocket.recv()
            print(f"Received: {response}")
        except websockets.ConnectionClosed as e:
            print(f"Connection closed: {e}")
            break


async def websocket_client():
    uri = "ws://localhost:8080"  # WebSocket 服务器的地址
    async with websockets.connect(uri) as websocket:
        send_task = asyncio.create_task(send_message(websocket))
        receive_task = asyncio.create_task(receive_message(websocket))

        # 等待发送和接收任务同时运行
        await asyncio.gather(send_task, receive_task)


# 运行客户端
asyncio.run(websocket_client())
