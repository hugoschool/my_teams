from fastapi import FastAPI
from pydantic import BaseModel

import socket

BUFFER_SIZE = 4096

# Connect directly on start
# Causes to crash if port not opened
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 4242))
s.settimeout(0.1)

def send_command(string):
    s.send(f"{string}\r\n".encode())

def recvall():
    data = b''
    while True:
        try:
            part = s.recv(BUFFER_SIZE)
            data += part
            if len(part) == 0:
                break
        except:
            break
    return data

# Ignore "protocol initialized" message
_ = recvall()

app = FastAPI()

class LoginModel(BaseModel):
    username: str

@app.post("/login")
async def login(login: LoginModel):
    send_command(f"LOGIN {login.username}")
    buffer = recvall()
    if buffer.startswith(b"250"):
        return {"message": "Success"}
    return {"message": "Failed"}

@app.post("/logout")
async def logout():
    send_command(f"LOGOUT")
    buffer = recvall()
    print(buffer)
    if buffer.startswith(b"251"):
        return {"message": "Success"}
    return {"message": "Failed"}
