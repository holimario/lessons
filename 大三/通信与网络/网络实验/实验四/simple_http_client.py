import socket

BUFFER_SIZE = 1024

url = "www.beijing.gov.cn"

# 显式请求DNS解析地址对应的IP
add_info = socket.getaddrinfo(url, 80, socket.AF_INET, socket.SOCK_STREAM)
host_info = add_info[0][-1]  # [(family, type, proto, canonname, sockaddr)]，此处选择第一个DNS地址
print("DNS: ", host_info)


def recv_all(sock):
    """
    将socket接收到的所有信息拼接起来
    """
    data = b""
    while True:
        try:
            sock.settimeout(2)
            part = sock.recv(BUFFER_SIZE)
            if len(part) == 0:
                break
        except:
            break
        data += part
    return data


# 建立到HTTP服务器的连接

# 初始化socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 建立与目标服务器的80端口的socket；此处也可直接输入url与端口号元组:s.connect((url,80))
s.connect(host_info)

# 发送HTTP请求

# 组装最简单的HTTP请求
simple_http_request = f"GET / HTTP/1.1\r\nHost: {url}\r\nKeep-alive: Close\r\n\r\n"
# 将HTTP请求编码为二进制数据并通过socket发送
s.send(simple_http_request.encode())
# 接收HTTP原始响应
res = recv_all(s)
s.close()
print("HTTP原始响应: ", res)

# 解析HTTP响应

# 通过\r\n\r\n分割找到headers与body
sep = b"\r\n\r\n"
head = res[: res.find(sep)].decode()
headers = {}  # headers解析为dict结构
for line in head.split("\r\n")[1:]:
    point_index = line.find(":")
    headers[line[:point_index].strip().lower()] = line[point_index + 1 :].strip()
print("HTTP响应头: ", headers)
body = res[res.find(sep) + 4 :]

# 保存结果(注意，这里以比特形式写入)
f = open("result.html", "wb")
# 处理transfer-encoding: chunked的情况
# 参考资料：https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Transfer-Encoding#directives
# 感兴趣的同学可以了解
if headers.get("transfer-encoding", "").lower() == "chunked":
    while len(body) > 0:
        chunk_prefix = body[: body.find(b"\r\n")]
        body = body[len(chunk_prefix) + len(b"\r\n") :]
        chunk_size = int(chunk_prefix.decode(), base=16)
        print(chunk_size)
        f.write(body[:chunk_size])
        body = body[chunk_size:]
        if body.startswith(b"\r\n"):
            body = body[len(b"\r\n") :]
else:
    f.write(body)
f.close()

