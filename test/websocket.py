import websockets
import asyncio


async def hello():
    async with websockets.connect("ws://127.0.0.1:8080") as websocket:  # 使用 127.0.0.1
        name = input("What's your name? ")

        await websocket.send(name)
        print(f"> {name}")

        greeting = await websocket.recv()
        print(f"< {greeting}")


if __name__ == "__main__":
    asyncio.run(hello())
