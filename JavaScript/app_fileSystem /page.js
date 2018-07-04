var parent = ""
function documentAndFolder(parent, type, child, childName, childPathName){
    this.parent = parent
    this.type = type
    this.child = child
    this.childName = childName
    this.childPathName = childPathName
}

var nodeArray = new Array()

function  addMenu() {
    const electron = require('electron')
    const remote = electron.remote
    const Menu = remote.Menu
    const MenuItem = remote.MenuItem
    const dialog = electron.dialog
    let menu = new Menu();

    menu.append(new MenuItem({ label: 'Add folder', click:function(){
        for(var i = 0; i < nodeArray.length; i++){
            if (nodeArray[i].parent == parent && nodeArray[i].childPathName == document.getElementById('m_name').value && nodeArray[i].type == "F")
            {
                alert("文件夹名重复")
                return
            }
        }

        var m_folderTh = document.createElement("th")
        var m_folderNameTh = document.createElement("th")
        var m_folder = document.createElement("img")
        var m_folderName = document.createElement("h")

        // var folderName = prompt("请输入文件夹名","")

        m_folderTh.appendChild(m_folder)
        m_folderNameTh.appendChild(m_folderName)

        m_folder.id = "F" + (new Date()).getTime();
        m_folderName.id = m_folder.id + "1";

        m_folder.onclick = function(m_folder){
            parent = m_folder.currentTarget.attributes["0"].nodeValue

            hideAll()

            document.getElementById('m_path').value = getPath(parent)

            for(var i = 0; i < nodeArray.length; i++)
            {
                if(nodeArray[i].parent == parent)
                {
                    showFolderAndDocument(nodeArray[i].child, nodeArray[i].childName)
                }
            }

        }

        // m_folder.oncontextmenu = function()

        m_folderName.innerHTML = document.getElementById('m_name').value

        m_folder.src = "./folder.png";

        document.getElementById('m_node').appendChild(m_folderTh)
        document.getElementById('m_nodeNeme').appendChild(m_folderNameTh)

        var node = new documentAndFolder(parent, "F", m_folder.id, m_folderName.id, m_folderName.innerHTML)

        nodeArray.push(node)
    }}));

    menu.append(new MenuItem({ type: 'separator'}));
    menu.append(new MenuItem({ label: 'Add document', click:function(){
        for(var i = 0; i < nodeArray.length; i++){
            if (nodeArray[i].parent == parent && nodeArray[i].childPathName == document.getElementById('m_name').value && nodeArray[i].type == "D")
            {
                alert("文件名重复")
                return
            }
        }

        var m_folderTh = document.createElement("th")
        var m_folderNameTh = document.createElement("th")
        var m_document = document.createElement("img")
        var m_documentName = document.createElement("h")

        m_folderTh.appendChild(m_document)
        m_folderNameTh.appendChild(m_documentName)

        m_document.id = "D" + (new Date()).getTime();
        m_documentName.id = m_document.id + "1";

        m_documentName.innerHTML = document.getElementById('m_name').value

        m_document.src = "./document.png";

        document.getElementById('m_node').appendChild(m_folderTh)
        document.getElementById('m_nodeNeme').appendChild(m_folderNameTh)

        var node = new documentAndFolder(parent, "D", m_document.id, m_documentName.id, m_documentName.innerHTML)

        nodeArray.push(node)
    }}));

    menu.append(new MenuItem({ type: 'separator' }));
    menu.append(new MenuItem({ label: 'Delete', click:function(){


        var fs = require('fs');
        var path = require('path');

        //解析需要遍历的文件夹，我这以E盘根目录为例
        var filePath = path.resolve('/home/test/my_Code/html/');

        //调用文件遍历方法


            //根据文件路径读取文件，返回文件列表
            fs.readdir(filePath,function(err,files){
                if(err){
                    console.warn(err)
                }else{
                    //遍历读取到的文件列表
                    files.forEach(function(filename){
                        //获取当前文件的绝对路径
                        var filedir = path.join(filePath,filename);
                        //根据文件路径获取文件信息，返回一个fs.Stats对象
                        fs.stat(filedir,function(eror,stats){
                            if(eror){
                                console.warn('获取文件stats失败');
                            }else{
                                var isFile = stats.isFile();//是文件
                                var isDir = stats.isDirectory();//是文件夹
                                if(isFile){
                                    console.log(filedir);
                                }
                                if(isDir){
                                    fileDisplay(filedir);//递归，如果是文件夹，就继续遍历该文件夹下面的文件
                                }
                            }
                        })
                    });
                }
            });



        // var pa = fs.readdirSync("/home/test/my_Code/html/");
        //
        // pa.forEach(function(ele,index){
        //     var info = fs.statSync(path+"/"+ele)
        //     if(info.isDirectory()){
        //         console.log("dir: "+ele)
        //         readDirSync(path+"/"+ele);
        //     }else{
        //         console.log("file: "+ele)
        //     }
        // })
        // var _path = path.join(__dirname, '..', '\\app\\html\\config\\record.txt');
        // var path1 = "d:\\ProjectsSpace\\ElectronProjects\\ElectronTest2\\app\\html\\config\\record.txt";
        // console.log(_path, path1);//测试路径对不对的
        // var fs = require('fs');
        // fs.readFile(_path, 'utf8', function (err, data) {
        // if (err) return console.log(err);
        // });
        //
        // fs.writeFile(_path, "electron + Javascript", function (err) {
        // if (!err)
        //   console.log("写入成功！")
        // })


    }}));

    window.addEventListener('contextmenu', function (e) {
        e.preventDefault()
        menu.popup(remote.getCurrentWindow())
    }, false)
}

function showFolderAndDocument(child, childName){
    var a = child.length
    document.getElementById(child).style.display = "block"
    document.getElementById(childName).style.display = "block"
}

function hideAll(){
    for(var i = 0; i < nodeArray.length; i++){
        document.getElementById(nodeArray[i].child).style.display = "none"
        document.getElementById(nodeArray[i].childName).style.display = "none"
    }
}

function parsePath(path, parent){
    if (path == "") {
        return true
    }

    if (path[0] == '/') {
        path = path.substr(1, path.length -1)
    }

    for (var i = 0; i < nodeArray.length; i++) {
        if (nodeArray[i].childPathName == path.split('/')[path.split('/').length - 1] && nodeArray[i].type == "F"){
            if (path.split('/').length == 1) {
                if (parent.id == "") {
                    parent.id = nodeArray[i].parent
                }
                return true
            }
            for (var j = 0; j < nodeArray.length; j++) {
                if (nodeArray[j].childPathName == path.split('/')[path.split('/').length - 2] && nodeArray[j].type == "F"){
                    if (nodeArray[i].parent == nodeArray[j].child) {
                        var mPath = ""
                        for (var k = 0; k < path.split('/').length - 1; k++) {
                            mPath = mPath + '/' + path.split('/')[k]
                        }
                        if (parent.id == "") {
                            parent.id = nodeArray[i].child
                        }
                        return parsePath(mPath.substr(1, mPath.length -1), parent)
                    }
                }
            }
            return false
        }
    }
    return false
}

function getPath(parent){
    for (var i = 0; i < nodeArray.length; i++) {
        if (parent == nodeArray[i].child) {
            if (nodeArray[i].parent == "") {
                return "/" + nodeArray[i].childPathName
            }
            return getPath(nodeArray[i].parent) + '/' + nodeArray[i].childPathName
        }
    }
}

function goBack(){
    var path = document.getElementById('m_path').value
    var mPath = ""
    for (var k = 0; k < path.split('/').length - 1; k++) {
        mPath = mPath + '/' + path.split('/')[k]
    }
    mPath = mPath.substr(1, mPath.length -1)
    document.getElementById('m_path').value = mPath

    var parent = new Object()
    parent.id = ""
    var status = parsePath(mPath, parent)

    if(status)
    {
        hideAll()

        for(var i = 0; i < nodeArray.length; i++)
        {
            if(nodeArray[i].parent == parent.id)
            {
                showFolderAndDocument(nodeArray[i].child, nodeArray[i].childName)
            }
        }
    }

}

function goForward(){

}


// function parsePath(path){
//     for (var i = 0; i < nodeArray.length; i++) {
//         if (nodeArray[i].childPathName == path.split('/')[path.split('/').lenth - 1] && nodeArray[i].type == "F"){
//             if(nodeArray[i].parent != ""){
//                 for (var j = 0; j < nodeArray.length; j++) {
//                     if(nodeArray[j].child == nodeArray[i].parent){
//                         var mPath
//                         for (var k = 0; k < path.split('/').lenth - 1; k++) {
//                             mPath = mPath + '/' + path.split('/')[k]
//                         }
//                         return parsePath(mPath)
//                     }
//                 }
//                 return false
//             }
//             else {
//                 return true
//             }
//         }
//         else {
//             return false
//         }
//     }
// }

// function createFolder(child, childName){
//     var m_folderTh = document.createElement("th")
//     var m_folderNameTh = document.createElement("th")
//     var m_folder = document.createElement("img")
//     var m_folderName = document.createElement("h")
//
//     // var folderName = prompt("请输入文件夹名","")
//
//     m_folderTh.appendChild(m_folder)
//     m_folderNameTh.appendChild(m_folderName)
//
//     m_folder.id = child
//
//     // m_folderTh.style = "word-wrap:break-word"
//     // m_folderNameTh.style = "word-wrap:break-word"
//
//     m_folder.onclick = function(m_folder){
//         parent = m_folder.currentTarget.attributes["0"].nodeValue
//         document.getElementById('m_node').innerHTML = ""
//         document.getElementById('m_nodeNeme').innerHTML = ""
//
//         // for(var i = 0; i < nodeArray.length; i++){
//         //     if(nodeArray[i].parent == parent && )
//         // }
//
//         for(var i = 0; i < nodeArray.length; i++){
//             if(nodeArray[i].parent == parent)
//             {
//                 if(nodeArray[i].type == "F"){
//                     console.log("aasaa");
//                     createFolder(nodeArray[i].child, nodeArray[i].childName)
//                 }
//                 else if (nodeArray[i].type == "D") {
//                     createDocument(nodeArray[i].child, nodeArray[i].childName)
//                 }
//             }
//         }
//
//     }
//
//     m_folderName.innerHTML = childName
//
//     m_folder.src = "./folder.png";
//
//     document.getElementById('m_node').appendChild(m_folderTh)
//     document.getElementById('m_nodeNeme').appendChild(m_folderNameTh)
// }
//
// function createDocument(child, childName){
//     var m_folderTh = document.createElement("th")
//     var m_folderNameTh = document.createElement("th")
//     var m_document = document.createElement("img")
//     var m_documentName = document.createElement("h")
//
//     m_folderTh.appendChild(m_document)
//     m_folderNameTh.appendChild(m_documentName)
//
//     m_document.id = child
//
//     m_documentName.innerHTML = childName
//
//     m_document.src = "./document.png";
//
//     document.getElementById('m_node').appendChild(m_folderTh)
//     document.getElementById('m_nodeNeme').appendChild(m_folderNameTh)
// }
