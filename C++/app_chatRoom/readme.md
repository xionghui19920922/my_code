1. 客户端是Qt项目，直接用Qtcreate打开就行
2. 服务器搭建需要安装node
    </br>搭建步骤：
    </br>先到https://github.com/socketio/socket.io上clone socket.io
    </br>再执行以下命令：
        </br>$ cd socket.io
        </br>$ npm install
        </br>$ cd examples/chat
        </br>$ npm install
        </br>$ npm start
3. 主要功能就是通过socketio实现C++客户端与js的服务器的通讯,包括文字信息以及图片信息
