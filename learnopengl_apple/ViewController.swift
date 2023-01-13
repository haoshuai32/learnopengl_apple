//
//  ViewController.swift
//  learnopengl_apple
//
//  Created by haoshuai on 2022/8/16.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        let glView = GLView(frame: CGRect(x: 0, y: 50, width: UIScreen.main.bounds.width, height: UIScreen.main.bounds.width))
        self.view.addSubview(glView)
        // Do any additional setup after loading the view.
    }


}

