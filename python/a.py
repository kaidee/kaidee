# from subprocess import *

# def temp():
# 	pass
# print = temp

# print 'open subprocess'


import gzip
import zlib
import base64
import binascii
from StringIO import StringIO

x = '''H4sIAAAAAAAAA6WRubaiQABEc75icgKgu2kgmKBFNgWkAYFHxtYsPkRxAf3658x8
wtykTp2qqKouECvlCjcabBRUw5qpMlBkTWMFBhiBX4VYiKrIEGgwk2AJC1B/FDJR
gaIm1zX3+z/hhLjGqTkRQuJRmkOLtKQj4dfHb0SXTwdEzJDQpCYby9GvbNfs0iIL
xduwhJc6UgyOx84lVwajXc6Dn5mSw5NRhroRooffjzps0hlU7ulooiVSNLHrKnO3
DfpyCw38fJ2O3MKSKr+fVoa0tQN9c++ixXRWyMZzLND39A0r4L9t3x1FdbrgacAV
dl5jRqfYOrLhzlFvRFR9PXpLz0Dvkuvx1gqRed75pWQh+jikepJHdJn9sz3lZ3Lb
Ddm+XlMVrEnkyDYXA8uWNHum6aCMxHmCzrCU2Z4V91nJ+/meBD7iByunQflMPeR1
fDSswhK/ViohLxU4s42S/bafYZA5zIMCKoO2PWCDVnB/aP03/eYNuQnI5IiL3/F7
Y+qy61dyR20f+qMMuNfls/tfdDVuBttGnYUp2UzUjf4k/YN4smsbuXDT//XCPG0/
9/0ARoRNpEICAAA='''




# echo gzdecode(base64_decode('H4sIAAAAAAAAA6WRubaiQABEc75icgKgu2kgmKBFNgWkAYFHxtYsPkRxAf3658x8wtykTp2qqKouECvlCjcabBRUw5qpMlBkTWMFBhiBX4VYiKrIEGgwk2AJC1B/FDJRgaIm1zX3+z/hhLjGqTkRQuJRmkOLtKQj4dfHb0SXTwdEzJDQpCYby9GvbNfs0iILxduwhJc6UgyOx84lVwajXc6Dn5mSw5NRhroRooffjzps0hlU7ulooiVSNLHrKnO3DfpyCw38fJ2O3MKSKr+fVoa0tQN9c++ixXRWyMZzLND39A0r4L9t3x1FdbrgacAVdl5jRqfYOrLhzlFvRFR9PXpLz0Dvkuvx1gqRed75pWQh+jikepJHdJn9sz3lZ3LbDdm+XlMVrEnkyDYXA8uWNHum6aCMxHmCzrCU2Z4V91nJ+/meBD7iByunQflMPeR1fDSswhK/ViohLxU4s42S/bafYZA5zIMCKoO2PWCDVnB/aP03/eYNuQnI5IiL3/F7Y+qy61dyR20f+qMMuNfls/tfdDVuBttGnYUp2UzUjf4k/YN4smsbuXDT//XCPG0/9/0ARoRNpEICAAA='));

if __name__ == '__main__':
    s='H4sIAAAAAAAAA6WRubaiQABEc75icgKgu2kgmKBFNgWkAYFHxtYsPkRxAf3658x8 wtykTp2qqKouECvlCjcabBRUw5qpMlBkTWMFBhiBX4VYiKrIEGgwk2AJC1B/FDJR gaIm1zX3+z/hhLjGqTkRQuJRmkOLtKQj4dfHb0SXTwdEzJDQpCYby9GvbNfs0iIL xduwhJc6UgyOx84lVwajXc6Dn5mSw5NRhroRooffjzps0hlU7ulooiVSNLHrKnO3 DfpyCw38fJ2O3MKSKr+fVoa0tQN9c++ixXRWyMZzLND39A0r4L9t3x1FdbrgacAV dl5jRqfYOrLhzlFvRFR9PXpLz0Dvkuvx1gqRed75pWQh+jikepJHdJn9sz3lZ3Lb Ddm+XlMVrEnkyDYXA8uWNHum6aCMxHmCzrCU2Z4V91nJ+/meBD7iByunQflMPeR1 fDSswhK/ViohLxU4s42S/bafYZA5zIMCKoO2PWCDVnB/aP03/eYNuQnI5IiL3/F7 Y+qy61dyR20f+qMMuNfls/tfdDVuBttGnYUp2UzUjf4k/YN4smsbuXDT//XCPG0/ 9/0ARoRNpEICAAA='
    key = "H4sIAAAAAAAAAzPUUwjJSFVIzCsuTy1SKMlXyMlMS9VRKAGKleZllqUWFQN5iXkpCqlAdmVJRmZe uh4vFy+XkZ5Chaubk5tOhZOLK4h0c3J5v2f2sxnrn+xoeLls2pPdDU92drxYP/1xQxNIvbGegltm UXGJQpCbs0JeaW4S0Lb8NIWC/KISBWdzIwtHE0tjM2NnS0dLY0cTY0dzV3M3I2MjJ1NHUxNHkH4r N08/Rx9eLkeoQ4HuKyxNLS7JzM8r1lFwzs8rSUwuUfDMK8ssSU21UkhNzgB6Jb8sVTc5PwWovkYh xNMvMjTIBwDO8n7C8AAAAA=="
    s = base64.b64decode(s)

    # print 's:', s
    # xs = map(lambda x: ord(x), s)
    # print xs
    buf = StringIO(s)
    gziper = gzip.GzipFile(fileobj=buf)
    data2 = gziper.read()
    print data2


    h = 'da4fb5c6e93e74d3df8527599fa62642'
    k = '/Td6WFoAAATm1rRGAgAhARYAAAB0L+Wj4AFRAQVdABGICqfJeJWaXR0sjwRpdS7E +6IpZ7jEgwnjNXF1I+Am53CER4uNimC3eWr2cLkUF4wS790hhcFJDPibD3E6vykU wfVcZtkxf49xh2iethSwFIx3fmnT/Qzol3c2NzHNLm08op6oj6c6IymXQoTGUfjt QMm4Q8yuiGCX2iLAqUsg/SFnJNb1G4QuOWCVZSQwrNnHoZnAsJjXKdxW82xVSI5H T2GH19HrQWj7mAIv2hEG7rHr7Lvc5KrtVPN4+jGZQPbvWM4Mh+Sjx/wTyxQ14MW/ FgSVKDir3PXIfM3/4bPggO6EQc3KOgNzQl+E5ePAoI0wNh+KEohXqYVt4giRNm52 ypAgAAAAAAC8TejHH4hG6QABoQLSAgAAiuAM5LHEZ/sCAAAAAARZWg=='
    # a = binascii.a2b_base64(k)
    a = h.decode('base64')
    print a#.encode('utf-8')

    # print buf.getvalue()
    # x = gzip.GzipFile(fileobj=open('compresseddata.gz', 'rb'))
    # x = gzip.open('compresseddata.gz', 'rb')
    # print dir(x)
    # print x.read()
    # data = x.read(len(s))
    # print data
    # data = gzip.zlib.decompress(s, 16+gzip.zlib.MAX_WBITS)
    # data = gzip.zlib.decompress(s, -zlib.MAX_WBITS)
    # print dir(data)

    # print a
    # data = gzip.zlib.decompress(a, -gzip.zlib.MAX_WBITS)
    # print data

