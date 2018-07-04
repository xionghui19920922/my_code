// var parent = ""
var fs = require('fs');
var path = require('path')

function documentAndFolder(child, childName, childPathName, path){
    // this.parent = parent
    // this.type = type
    this.child = child
    this.childName = childName
    this.childPathName = childPathName
    this.path = path
}

var nodeArray = new Array()

function inputChange(){
    e = event ? event :(window.event ? window.event : null);
    if(e.keyCode==13){
        let filePath = document.getElementById('m_path').value

        fs.exists(filePath, function(exists) {
            if (!exists) {
                alert("路径不存在")
                return
            }
            else {
                fileSearchAndShow(filePath);
            }
        });
    }
}

function fileSearchAndShow(filePath){
    document.getElementById('m_frame').innerHTML = ""
    nodeArray = []

    var file = fs.readdirSync(filePath)
    var fileFolder = []
    var fileDocument = []
    var files = []

    for(var i = 0;i<file.length;i++){

        if (file[i][0] == ".") {
            continue
        }

        var filedir = path.join(filePath,file[i]);

        var stats = fs.statSync(filedir)

        var isFile = stats.isFile();
        var isDir = stats.isDirectory();
        if(isFile){
            fileDocument.push(file[i])
        }
        if(isDir){
            fileFolder.push(file[i])
        }
    }

    fileFolder.sort(function(first, second){return first.toLowerCase()>second.toLowerCase()?1:-1;})
    fileDocument.sort(function(first, second){return first.toLowerCase()>second.toLowerCase()?1:-1;})

    files = fileFolder.concat(fileDocument)

    for(var i = 0;i<files.length;i++){

        if (files[i][0] == ".") {
            continue
        }

        var filedir = path.join(filePath,files[i]);

        var stats = fs.statSync(filedir)

        var isFile = stats.isFile();
        var isDir = stats.isDirectory();
        if(isFile){
            createDocument(filePath, files[i])
        }
        if(isDir){
            createFolder(filePath, files[i])
        }
    }

    for(var i = 0; i < nodeArray.length; i++)
    {
        if(nodeArray[i].path == filePath)
        {
            document.getElementById(nodeArray[i].child).style.display = "block"
            document.getElementById(nodeArray[i].childName).style.display = "block"
        }
    }

    var divItem = document.getElementById('m_frame').getElementsByTagName('div')
    var maxHeight = divItem[0].offsetHeight
    for (var i = 3; i < divItem.length; i = i+3) {
        if (maxHeight < divItem[i].offsetHeight) {
            maxHeight = divItem[i].offsetHeight
        }
    }

    for (var i = 0; i < divItem.length; i=i+3) {
        divItem[i].style.height = maxHeight + "px"
    }

}

function createFolder(filePath, fileName){
    var m_folderDiv = document.createElement("div")
    var m_folderNameDiv = document.createElement("div")
    var m_Div = document.createElement("div")
    var m_folder = document.createElement("img")
    var m_folderName = document.createElement("p")

    m_Div.name = "m_div"

    m_Div.style.float = "left"
    m_Div.style.margin = "15px"
    m_Div.style.width = "140px"
    // m_Div.style.background = "#ddd"
    // m_Div.style = "background-color:#ddd"
    // m_folderDiv.style.height = "60px"

    m_folderDiv.align = "center"
    m_folderNameDiv.style = "text-align:center"
    // m_folderName.style.width = "80px"
    m_folderName.style = "word-wrap:break-word"


    m_folderDiv.appendChild(m_folder)
    m_folderNameDiv.appendChild(m_folderName)
    m_Div.appendChild(m_folderDiv)
    m_Div.appendChild(m_folderNameDiv)
    document.getElementById('m_frame').appendChild(m_Div)

    m_folder.id = fileName + (new Date()).getTime();
    m_folderName.id = m_folder.id + "1";

    m_folder.style.display = "none"
    m_folderName.style.display = "none"

    m_folder.ondblclick = function(m_folder){
        var id = m_folder.currentTarget.attributes["0"].nodeValue

        hideAll()
        let mPath
        for (var i = 0; i < nodeArray.length; i++) {
            if (nodeArray[i].child == id) {
                mPath = path.join(nodeArray[i].path, nodeArray[i].childPathName)
                fileSearchAndShow(mPath)
                break
            }
        }
        document.getElementById('m_path').value = mPath
    }

    m_folderName.innerHTML = fileName

    m_folder.src = "./folder.png";

    var node = new documentAndFolder(m_folder.id, m_folderName.id, m_folderName.innerHTML, filePath)

    nodeArray.push(node)

    return m_folder.id
}

function createDocument(filePath, fileName){
    var m_folderDiv = document.createElement("div")
    var m_folderNameDiv = document.createElement("div")
    var m_Div = document.createElement("div")
    var m_document = document.createElement("img")
    var m_documentName = document.createElement("p")

    m_Div.name = "m_div"

    m_folderDiv.appendChild(m_document)
    m_folderNameDiv.appendChild(m_documentName)
    m_Div.appendChild(m_folderDiv)
    m_Div.appendChild(m_folderNameDiv)
    document.getElementById('m_frame').appendChild(m_Div)

    m_Div.style.float = "left"
    m_Div.style.margin = "15px"
    m_Div.style.width = "140px"
    // m_folderDiv.style.height = "60px"
    m_folderDiv.align = "center"
    m_folderNameDiv.style = "text-align:center"

    m_documentName.style = "word-wrap:break-word"


    // m_Div.style.background = "#ddd"

    m_document.id = fileName + (new Date()).getTime();
    m_documentName.id = m_document.id + "1";

    m_document.style.display = "none"
    m_documentName.style.display = "none"

    m_documentName.innerHTML = fileName

    m_document.src = "./document.png";

    var node = new documentAndFolder(m_document.id, m_documentName.id, m_documentName.innerHTML, filePath)

    nodeArray.push(node)
}

// function showFolderAndDocument(child, childName){
//     var a = child.length
//     document.getElementById(child).style.display = "block"
//     document.getElementById(childName).style.display = "block"
// }

function hideAll(){
    for(var i = 0; i < nodeArray.length; i++){
        document.getElementById(nodeArray[i].child).style.display = "none"
        document.getElementById(nodeArray[i].childName).style.display = "none"
    }
}

function getPath(parent){
    for (var i = 0; i < nodeArray.length; i++) {
        if (parent == nodeArray[i].child) {
            return nodeArray[i].path
            // if (nodeArray[i].parent == "") {
            //     return "/" + nodeArray[i].childPathName
            // }
            // return getPath(nodeArray[i].parent) + '/' + nodeArray[i].childPathName
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
    fileSearchAndShow(mPath)
}

// function parsePath(path, parent){
//     if (path == "") {
//         return true
//     }
//
//     if (path[0] == '/') {
//         path = path.substr(1, path.length -1)
//     }
//
//     for (var i = 0; i < nodeArray.length; i++) {
//         if (nodeArray[i].childPathName == path.split('/')[path.split('/').length - 1] && nodeArray[i].type == "F"){
//             if (path.split('/').length == 1) {
//                 if (parent.id == "") {
//                     parent.id = nodeArray[i].parent
//                 }
//                 return true
//             }
//             for (var j = 0; j < nodeArray.length; j++) {
//                 if (nodeArray[j].childPathName == path.split('/')[path.split('/').length - 2] && nodeArray[j].type == "F"){
//                     if (nodeArray[i].parent == nodeArray[j].child) {
//                         var mPath = ""
//                         for (var k = 0; k < path.split('/').length - 1; k++) {
//                             mPath = mPath + '/' + path.split('/')[k]
//                         }
//                         if (parent.id == "") {
//                             parent.id = nodeArray[i].child
//                         }
//                         return parsePath(mPath.substr(1, mPath.length -1), parent)
//                     }
//                 }
//             }
//             return false
//         }
//     }
//     return false
// }

// function goForward(){
//
// }
//
// function  addMenu() {
//     const electron = require('electron')
//     const remote = electron.remote
//     const Menu = remote.Menu
//     const MenuItem = remote.MenuItem
//     const dialog = electron.dialog
//     let menu = new Menu();
//
//     menu.append(new MenuItem({ label: 'Add folder', click:function(){
//         for(var i = 0; i < nodeArray.length; i++){
//             if (nodeArray[i].parent == parent && nodeArray[i].childPathName == document.getElementById('m_name').value && nodeArray[i].type == "F")
//             {
//                 alert("文件夹名重复")
//                 return
//             }
//         }
//
//         var m_folderTh = document.createElement("th")
//         var m_folderNameTh = document.createElement("th")
//         var m_folder = document.createElement("img")
//         var m_folderName = document.createElement("h")
//
//         // var folderName = prompt("请输入文件夹名","")
//
//         m_folderTh.appendChild(m_folder)
//         m_folderNameTh.appendChild(m_folderName)
//
//         m_folder.id = "F" + (new Date()).getTime();
//         m_folderName.id = m_folder.id + "1";
//
//         m_folder.onclick = function(m_folder){
//             parent = m_folder.currentTarget.attributes["0"].nodeValue
//
//             hideAll()
//
//             document.getElementById('m_path').value = getPath(parent)
//
//             for(var i = 0; i < nodeArray.length; i++)
//             {
//                 if(nodeArray[i].parent == parent)
//                 {
//                     showFolderAndDocument(nodeArray[i].child, nodeArray[i].childName)
//                 }
//             }
//
//         }
//
//         // m_folder.oncontextmenu = function()
//
//         m_folderName.innerHTML = document.getElementById('m_name').value
//
//         m_folder.src = "./folder.png";
//
//         document.getElementById('m_node').appendChild(m_folderTh)
//         document.getElementById('m_nodeNeme').appendChild(m_folderNameTh)
//
//         var node = new documentAndFolder(parent, "F", m_folder.id, m_folderName.id, m_folderName.innerHTML)
//
//         nodeArray.push(node)
//     }}));
//
//     menu.append(new MenuItem({ type: 'separator'}));
//     menu.append(new MenuItem({ label: 'Add document', click:function(){
//         for(var i = 0; i < nodeArray.length; i++){
//             if (nodeArray[i].parent == parent && nodeArray[i].childPathName == document.getElementById('m_name').value && nodeArray[i].type == "D")
//             {
//                 alert("文件名重复")
//                 return
//             }
//         }
//
//         var m_folderTh = document.createElement("th")
//         var m_folderNameTh = document.createElement("th")
//         var m_document = document.createElement("img")
//         var m_documentName = document.createElement("h")
//
//         m_folderTh.appendChild(m_document)
//         m_folderNameTh.appendChild(m_documentName)
//
//         m_document.id = "D" + (new Date()).getTime();
//         m_documentName.id = m_document.id + "1";
//
//         m_documentName.innerHTML = document.getElementById('m_name').value
//
//         m_document.src = "./document.png";
//
//         document.getElementById('m_node').appendChild(m_folderTh)
//         document.getElementById('m_nodeNeme').appendChild(m_folderNameTh)
//
//         var node = new documentAndFolder(parent, "D", m_document.id, m_documentName.id, m_documentName.innerHTML)
//
//         nodeArray.push(node)
//     }}));
//
//     menu.append(new MenuItem({ type: 'separator' }));
//     menu.append(new MenuItem({ label: 'Delete', click:function(){
//
//     }}));
//
//     window.addEventListener('contextmenu', function (e) {
//         e.preventDefault()
//         menu.popup(remote.getCurrentWindow())
//     }, false)
// }

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
