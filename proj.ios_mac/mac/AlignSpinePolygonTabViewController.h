//
//  AlignSpinePolygonTabViewController.h
//  greewoo-game-toolbox
//
//  Created by greewoo on 4/16/16.
//
//

#import <Cocoa/Cocoa.h>

@interface AlignSpinePolygonTabViewController : NSViewController

@property (assign) IBOutlet NSTextField *spineAtlasFilePath;
@property (assign) IBOutlet NSTextField *spineJsonFilePath;
@property (assign) IBOutlet NSTextField *polygonJsonFilePath;
@property (assign) IBOutlet NSTextField *animationName;
@property (assign) IBOutlet NSTextField *polygonName;

+ (AlignSpinePolygonTabViewController*) getInstance;

@end
