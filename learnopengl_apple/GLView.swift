//
//  GLView.swift
//  learnopengl_apple
//
//  Created by haoshuai on 2022/8/16.
//

import UIKit
import GLKit
import OpenGLES

class GLView: UIView,GLKViewDelegate {
    
    private var openGLView:UnsafeMutableRawPointer?
    private var glkView: GLKView?
    private var context: EAGLContext?
    private var displayLink: CADisplayLink?
    
    convenience init() {
        self.init(frame: CGRect.zero)
    }
    
    override init(frame: CGRect) {
        super.init(frame: frame)

        if let context = EAGLContext(api: EAGLRenderingAPI.openGLES3),
           let vsPath = Bundle.main.path(forResource: "3.0.shader.vs", ofType: nil),
           let fsPath = Bundle.main.path(forResource: "3.0.shader.fs", ofType: nil)
         {
            self.context = context
            self.glkView = GLKView(frame: frame, context: context)
            self.glkView?.drawableColorFormat = .RGBA8888
            self.glkView?.drawableDepthFormat = .format24
            EAGLContext.setCurrent(context)
            
            self.addSubview(self.glkView!)
            self.glkView?.delegate = self

            if let openGLClass = OpenGL_init(vsPath,fsPath) {
                self.openGLView = openGLClass
            } else {
                fatalError("create opengl error")
            }
        } else {
            fatalError("create opengl context error")
        }
        
    }
    
    @objc func displayLink(_ sender: CADisplayLink?) {
        self.glkView?.display()
    }
    
    
    func glkView(_ view: GLKView, drawIn rect: CGRect) {
        guard let openGLClass = self.openGLView else {
            return
        }
//        NSLog("%@", #function)
        OpenGL_clear_color()
        OpenGL_update(openGLClass)
        OpenGL_render(openGLClass)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func layoutSubviews() {
        super.layoutSubviews()
    }
    
//    此方法的默认实现什么也不做。 子类可以覆盖它以在窗口更改时执行其他操作。
//    调用此方法时，window 属性可能为 nil，表示接收者当前未驻留在任何窗口中。 当接收器刚刚从其父视图中删除或接收器刚刚添加到未附加到窗口的父视图时，就会发生这种情况。 如果不感兴趣，则此方法的覆盖可能会选择忽略此类情况。
    override func didMoveToWindow() {
        NSLog("%@ ==> %@", #function, self.window ?? "nil")
        
        guard let openGLClass = self.openGLView else {
            return
        }
        
        let vertices:[Float] = [
            // positions          // colors           // texture coords
             0.5,  0.5, 0.0,   1.0, 0.0, 0.0,   1.0, 1.0, // top right
             0.5, -0.5, 0.0,   0.0, 1.0, 0.0,   1.0, 0.0, // bottom right
            -0.5, -0.5, 0.0,   0.0, 0.0, 1.0,   0.0, 0.0, // bottom left
            -0.5,  0.5, 0.0,   1.0, 1.0, 0.0,   0.0, 1.0  // top left
        ]
        
        let indices:[Int32] = [
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        ]
        
        let ptr0 = UnsafePointer<Float>(vertices)
        let ptr1 = UnsafePointer<Int32>(indices)
        OpenGL_vertex(openGLClass, ptr0, Int32(vertices.count), ptr1, Int32(indices.count))

        if
            let texturePath1 = Bundle.main.path(forResource: "container.jpg", ofType: nil),
            let texturePath2 = Bundle.main.path(forResource: "awesomeface.png", ofType: nil) {
            OpenGL_texture_image(openGLClass, texturePath1, texturePath2)
        }

        self.displayLink = CADisplayLink(target: self, selector: #selector(displayLink(_:)))
        self.displayLink?.frameInterval = 1
        displayLink?.add(to: RunLoop.current, forMode: .default)
    }
    
    deinit {
        
    }
    

}
