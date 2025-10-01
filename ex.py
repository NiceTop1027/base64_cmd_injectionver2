import base64

def naaaaani(s):
    arr = bytearray(s, 'latin1')
    for i in range(len(arr)):
        x = arr[i] ^ 0x55
        arr[i] = ((x << 1) & 0xFF) | (x >> 7)
    return bytes(arr)

cmd = "cd home; cd ctf; ls -al; cat flag.txt"
enc = naaaaani(cmd)
b64enc = base64.b64encode(enc).decode()
print("Base64 Encoded:", b64enc)

