```shell
curl -O http://www.lua.org/ftp/lua-5.3.1.tar.gz &&
tar -zxf lua-5.3.1.tar.gz &&
cd lua-5.3.1 &&
make linux &&
make test &&
sudo make install &&
cd .. &&
rm -rf lua-5.3.1.tar.gz lua-5.3.1
```
