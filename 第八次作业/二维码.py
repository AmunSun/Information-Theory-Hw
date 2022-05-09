import qrcode
# 放入网址
input_data = "https://towardsdatascience.com/face-detection-in-10-lines-for-beginners-1787aa1d9127"

qr = qrcode.QRCode(
        version=1,
        box_size=10,
        border=5)
qr.add_data(input_data)
qr.make(fit=True)
img = qr.make_image(fill='black', back_color='white')
img.save('qrcode001.png')
