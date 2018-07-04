const electron = require('electron')
const Menu = electron.Menu
const app = electron.app
const BrowserWindow = electron.BrowserWindow
const clipboard = electron.clipboard
const Tray = electron.Tray
const dialog = electron.dialog
const path = require('path')
const url = require('url')
let mainWindow
let child
let menu
function createWindow () {
   mainWindow = new BrowserWindow({width: 800, height: 600, show:true})
   // console.log(dialog.showOpenDialog({properties: ['openFile', 'openDirectory', 'multiSelections']}))
   // console.log(dialog.showSaveDialog({properties: ['openFile', 'openDirectory', 'multiSelections']}))
   // dialog.showMessageBox({message:'sadsadsadsadas'},function(){
   //     console.log('sadsadsad');
   // })
   mainWindow.loadURL(url.format({
       pathname: path.join(__dirname, './index.html'),
       protocol: 'file:',
       slashes: true
   }))

   // mainWindow.loadURL('file://' + __dirname + '/index.html')
   // mainWindow.loadURL('http://www.baidu.com')

   // 打开调试工具DevTools.
   // mainWindow.webContents.openDevTools()

   mainWindow.on('closed', function () {
       mainWindow = null
   })

   mainWindow.webContents.on('new-window', (event, url, frameName, disposition, options, additionalFeatures) => {
    if (frameName === 'modal') {
      // open window as modal
      event.preventDefault()
      Object.assign(options, {
        modal: true,
        parent: mainWindow,
        width: 100,
        height: 100
      })
      event.newGuest = new BrowserWindow(options)

      event.newGuest.loadURL("http://www.baidu.com")

    }
  })

}
app.on('ready', createWindow)

app.on('window-all-closed', function () {
   if (process.platform !== 'darwin') {
       app.quit()
   }
})

app.on('activate', function () {
   if (mainWindow === null) {
       createWindow()
   }
})
