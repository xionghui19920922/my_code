// $("#mytree").tree({
//   url: '${pageContext.request.contextPath}/sysmenu/all',
//   loadFilter: function(data){
//     alert('asd');
//       return jsonbl(data);
//   }
// });
//
// function  bl(item){
//   var tree = new Object();
//
//   if (item.id)
//   {
//     tree.id = item.id;
//   }
//
//   if (item.title)
//   {
//     tree.text = item.title;
//   }
//
//   if (item.pth)
//   {
//     tree.attributes = item.pth
//   }
//
//   if(item.children){
//     tree.children = jsonbl(item.children);
//   }else{
//     tree.children = [];
//   }
//   return tree;
// }
//
// function jsonbl(data){
//     var easyTree = [];
//     $.each(data,function(index,item){
//       easyTree[index] = bl(item);
//     });
//    return easyTree;
// }
