'use babel';

import {requirePackages} from 'atom-utils'
import {CompositeDisposable} from 'atom'
import _ from 'lodash'
import $ from 'jquery'
import parseJSON from 'jquery'

// let aa = {
//     bl(item){
//       var tree = "{";
//       if (item.id)
//       {
//         tree += '"id": "';
//         tree += item.id;
//       }
//
//       if (item.title)
//       {
//         tree += '",';
//         tree += '"text": "';
//         tree += item.title;
//       }
//
//       // if (item.type)
//       // {
//       //   tree += '",';
//       //   tree += '"type": "';
//       //   tree += item.type;
//       // }
//       //
//       // if (item.batchId)
//       // {
//       //   tree += '",';
//       //   tree += '"batchId": "';
//       //   tree += item.batchId;
//       // }
//       //
//       // if (item.tooltip)
//       // {
//       //   tree += '",';
//       //   tree += '"tooltip": "';
//       //   tree += item.tooltip;
//       // }
//
//       if (item.pth)
//       {
//         tree += '",';
//         tree += '"attributes": "';
//         tree += item.pth;
//       }
//
//       if(item.children){
//           tree += '",';
//           tree += '"children":';
//           tree += aa.jsonbl(item.children);
//       }else{
//           // tree = tree.Substring(0,tree.Length-1);
//           tree += '"';
//       }
//       tree += "}";
//       return tree;
//     },
//
//     jsonbl(data){
//         var easyTree = "[";
//         $.each(data,function(index,item){
//           if (index != 0)
//             easyTree += ',';
//           easyTree += aa.bl(item);
//          });
//          easyTree += "]";
//         return easyTree;
//     }
// }

export default class OpenFilesView {
  constructor(addIconToElement) {
    this.element = document.createElement('div');
		this.paneSub = new CompositeDisposable
  }

  serialize() {}

  // Tear down any state and detach
  destroy() {
    this.element.remove()
		this.paneSub.dispose()
    document.getElementById('foldersLabel').outerHTML = ''
  }

  includeLinkStyle(url) {
     var curPageUrl = window.document.location.href;
     var rootPath = '/' + curPageUrl.split("//")[1].split("/")[1] + '/' + curPageUrl.split("//")[1].split("/")[2] + '/';
     url = rootPath + url;
     var link = document.createElement("link");
     link.rel = "stylesheet";
     link.type = "text/css";
     link.href = url;
     document.getElementsByTagName("head")[0].appendChild(link);
  }

  includeScriptStyle(url) {
    var curPageUrl = window.document.location.href;
    var rootPath = '/' + curPageUrl.split("//")[1].split("/")[1] + '/' + curPageUrl.split("//")[1].split("/")[2] + '/';
    url = rootPath + url;
    var oScript = document.createElement("script");
    oScript.type = "text/javascript";
    oScript.src = url;//'${TplviewView.templatePath}/${url}';
    document.getElementsByTagName("head")[0].appendChild( oScript);
  }





	createOpenFiles(treeView) {
    let treeViewInstance = treeView.getTreeViewInstance()

    let treeViewHeader = document.createElement('div')
    treeViewHeader.setAttribute('id', 'foldersLabel');

		treeViewHeader.style.paddingLeft = '0px'
		treeViewHeader.style.marginTop = '0px'
		treeViewHeader.style.marginBottom = '0px'
    treeViewInstance.element.prepend(treeViewHeader)

    try
    {
      this.includeScriptStyle(".atom/packages/myTreeView/tree-view/jquery.min.js");
      this.includeScriptStyle(".atom/packages/myTreeView/tree-view/jquery.easyui.min.js");
      this.includeLinkStyle(".atom/packages/myTreeView/tree-view/themes/default/easyui.css");
      this.includeLinkStyle(".atom/packages/myTreeView/tree-view/themes/icon.css");
      // this.includeLinkStyle("/home/test/Downloads/atom-1.27.2-amd64/resources/app/apm/node_modules/mute-stream/coverage/lcov-report/base.css");
      // this.includeLinkStyle("/home/test/Downloads/atom-1.27.2-amd64/resources/app/apm/node_modules/mute-stream/coverage/lcov-report/prettify.css");
      // this.includeLinkStyle("/home/test/Downloads/atom-1.27.2-amd64/resources/app/apm/node_modules/first-mate/benchmark/bootstrap.css");
      // this.includeLinkStyle("/home/test/Downloads/atom-1.27.2-amd64/resources/app/apm/node_modules/first-mate/benchmark/bootstrap.min.css");
      var curPageUrl = window.document.location.href;
      var rootPath = '/' + curPageUrl.split("//")[1].split("/")[1] + '/' + curPageUrl.split("//")[1].split("/")[2] + '/';
      rootPath = rootPath + '.atom/packages/myTreeView/tree-view/tree.html';
      $("#foldersLabel").load(rootPath);
      this.includeScriptStyle(".atom/packages/myTreeView/tree-view/treeScript.js");
    }
    catch(err)
    {
      alert(err.message);
    }
//=====================================================================
    // try
    // {
    //   let a;
    //   $.getJSON("/home/test/my_Code/html/tree/jquery-easyui-1.5.5.2/tree.json",function(data){
    //     $.each(data,function(index,item){
    //         a = aa.jsonbl(item);
    //      });
    //   })
    //
    //   setTimeout(function(){
    //       // alert(a);
    //   },100);
    // }
    // catch(err)
    // {
    //   alert(err.message);
    // }








	}
}
