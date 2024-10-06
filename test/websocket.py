import asyncio
import websockets

async def hello():
    uri = "ws://localhost:8080"  # 确保这里的端口与服务器一致
    async with websockets.connect(uri) as websocket:
        await websocket.send("Hello, Server!")
        response = await websocket.recv()
        print(f"Received from server: {response}")

asyncio.run(hello())
