function  ParseNode(item){
  var tree = "{";
  var keyValue;
  if (item.id)
  {
    tree += '"id": "';
    tree += item.id;
    keyValue = '{"id":' + '"' + item.id + '"';
  }

  if (item.title)
  {
    tree += '",';
    tree += '"text": "';
    tree += item.title;
    keyValue = keyValue + ',"title":' + '"' + item.title + '"';
  }

  if (item.type)
  {
    tree += '",';
    tree += '"type": "';
    tree += item.type;
    keyValue = keyValue + ',"type":' + '"' + item.type + '"';
  }

  if (item.batchId)
  {
    tree += '",';
    tree += '"batchId": "';
    tree += item.batchId;
    keyValue = keyValue + ',"batchId":' + '"' + item.batchId + '"';
  }

  if (item.tooltip)
  {
    tree += '",';
    tree += '"tooltip": "';
    tree += item.tooltip;
    keyValue = keyValue + ',"tooltip":' + '"' + item.tooltip + '"';
  }

  if (item.pth)
  {
    tree += '",';
    tree += '"pth": "';
    tree += item.pth;
    keyValue = keyValue + ',"pth":' + '"' + item.pth + '"';
  }

  keyValue = keyValue + '}';

  // alert(keyValue);

  tree += '",';
  tree += '"attributes": ';
  tree += keyValue;

  if(item.children){
      tree += ',';
      tree += '"children":';
      tree += ParseJson(item.children);
  }else{
      // tree = tree.Substring(0,tree.Length-1);
      tree += '';
  }
  tree += "}";
  return tree;
}

function  ParseJson(data){
  var easyTree = "[";
  $.each(data,function(index,item){
    if (index != 0)
      easyTree += ',';
    easyTree += ParseNode(item);
   });
   easyTree += "]";
  return easyTree;
}

let strJson;

function setValue()
{
    var curPageUrl = window.document.location.href;
    var rootPath = '/' + curPageUrl.split("//")[1].split("/")[1] + '/' + curPageUrl.split("//")[1].split("/")[2] + '/';
    rootPath = rootPath + '.atom/packages/myTreeView/tree-view/tree.json';

    $.getJSON(rootPath, function(data){
      $.each(data,function(index,item){
          // strJson = ParseJson(item);
          strJson = $.parseJSON(ParseJson(item));
       });
    });
}


// function  ParseNode(item){
//     var tree = new Object();
//
//     if (item.id)
//     {
//       tree.id = item.id;
//     }
//
//     if (item.title)
//     {
//       tree.text = item.title;
//     }
//
//     // if (item.type)
//     // {
//     //   tree += '",';
//     //   tree += '"type": "';
//     //   tree += item.type;
//     // }
//     //
//     // if (item.batchId)
//     // {
//     //   tree += '",';
//     //   tree += '"batchId": "';
//     //   tree += item.batchId;
//     // }
//     //
//     // if (item.tooltip)
//     // {
//     //   tree += '",';
//     //   tree += '"tooltip": "';
//     //   tree += item.tooltip;
//     // }
//
//     if (item.pth)
//     {
//       tree.attributes = item.pth;
//     }
//
//     if(item.children){
//         tree.children = ParseJson(item.children);
//     }else{
//         tree.children = [];
//     }
//     return tree;
// }
//
// function  ParseJson(data){
//   var easyTree = [];
//     $.each(data,function(index,item){
//       easyTree.push(ParseNode(item));
//       // easyTree[index] = ParseNode(item);
//      });
//   return easyTree;
// }
//
// let strJson = [];
//
// function setValue()
// {
//     $.getJSON("/home/test/my_Code/html/tree/jquery-easyui-1.5.5.2/tree.json",function(data){
//       $.each(data,function(index,item){
//           strJson = ParseJson(item);
//        });
//     });
//     setTimeout(function(){
//     },1000);
// }

setValue();

setTimeout(function(){
  // alert(strJson);
  $("#mytree").tree({
    data:strJson,
    onClick:function(node)
    {
      if (node.state)
      {
        node.checked = true;
        $(this).tree(node.state == 'closed' ? 'expand' : 'collapse', 	node.target);
        node.state = node.state === 'closed' ? 'closed' : 'open';
      }
    },
    onContextMenu: function(e, node)
    {
      e.stopPropagation();

      let parentNode = node;

      $('#menu').menu('show', {
        left: e.pageX,
        top:e.pageY
      });

      $('#menu').menu({
        onClick:function(node)
        {
           alert(JSON.stringify(parentNode.attributes));
        }
      });
      e.preventDefault();
    },
    onDblClick: function(node)
    {
        alert(JSON.stringify(node.attributes));
    }
  });
},1000);
