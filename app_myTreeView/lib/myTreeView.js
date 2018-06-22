'use babel';

import { requirePackages } from 'atom-utils'
import OpenFilesView from './myTreeView-view'

let addIconToElement;

export default {
  openFilesView: null,
  activate(state) {
    // try
    // {
    let parent = document.getElementsByClassName("tree-view-root full-menu list-tree has-collapsable-children focusable-panel")[0];
    let child = parent.childNodes[0];
    parent.removeChild(child);
    // }
    // catch(err)
    // {
    //   alert(err.message);
    // }


		requirePackages('tree-view').then(([treeView]) => {
			this.openFilesView = new OpenFilesView(addIconToElement)
			if (treeView) {
				this.openFilesView.createOpenFiles(treeView)
			}
		})
	},

  deactivate() {
    return this.openFilesView.destroy();
  },

  serialize() {},
}
