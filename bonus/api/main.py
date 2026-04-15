from fastapi import FastAPI, Response, status
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
async def login(login: LoginModel, response: Response):
    send_command(f"LOGIN {login.username}")
    buffer = recvall()
    if buffer.startswith(b"250"):
        return {"message": "Success"}
    response.status_code = status.HTTP_400_BAD_REQUEST
    return {"message": f"{buffer}"}

@app.post("/logout")
async def logout(response: Response):
    send_command(f"LOGOUT")
    buffer = recvall()
    if buffer.startswith(b"251"):
        return {"message": "Success"}
    response.status_code = status.HTTP_400_BAD_REQUEST
    return {"message": f"{buffer}"}

class SendModel(BaseModel):
    uuid: str
    body: str

@app.post("/send")
async def send(message: SendModel, response: Response):
    send_command(f"MESSAGE_SEND {message.uuid} {len(message.body)} {message.body}")
    buffer = recvall()
    if buffer.startswith(b"200"):
        return {"message": "Success"}
    response.status_code = status.HTTP_400_BAD_REQUEST
    return {"message": f"{buffer}"}

