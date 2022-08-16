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
        let glView = GLView(frame: UIScreen.main.bounds)
        self.view.addSubview(glView)
        // Do any additional setup after loading the view.
    }


}

