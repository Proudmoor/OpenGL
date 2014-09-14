//
//  main.m
//  StonehengeES
//
//  Created by Richard Wright on 3/16/13.
//  Copyright (c) 2013 Richard Wright. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "AppDelegate.h"

int main(int argc, char *argv[])
{
	static char szParentDirectory[255];

	///////////////////////////////////////////////////////////////////////////   
	// Get the directory where the .exe resides
	char *c;
	strncpy( szParentDirectory, argv[0], sizeof(szParentDirectory) );
	szParentDirectory[254] = '\0'; // Make sure we are NULL terminated
	
	c = (char*) szParentDirectory;

	while (*c != '\0')     // go to end 
	c++;

	while (*c != '/')      // back up to parent 
	c--;

	*c++ = '\0';           // cut off last part (binary name) 

	///////////////////////////////////////////////////////////////////////////   
	// Change to directory. Any data added to the project will be placed here.
	chdir(szParentDirectory);


    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
