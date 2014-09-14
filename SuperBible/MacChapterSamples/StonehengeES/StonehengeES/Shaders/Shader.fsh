//
//  Shader.fsh
//  StonehengeES
//
//  Created by Richard Wright on 3/16/13.
//  Copyright (c) 2013 Richard Wright. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
