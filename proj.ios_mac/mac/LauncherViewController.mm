//
//  LauncherViewController.m
//  greewoo-game-toolbox
//
//  Created by greewoo on 4/13/16.
//
//

#import "LauncherViewController.h"

#include "AppDelegate.h"
#include "cocos2d.h"

@interface LauncherViewController ()
@property (assign) IBOutlet NSTextField *spineAtlasFilePath;
@property (assign) IBOutlet NSTextField *spineJsonFilePath;
@property (assign) IBOutlet NSTextField *polygonJsonFilePath;

@end

@implementation LauncherViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
    
    NSLog(@"viewDidLoad");
}


- (void) viewWillAppear {
    NSLog(@"viewWillAppear");
}

- (NSString*) openDialog {
    int i; // Loop counter.
    
    // Create the File Open Dialog class.
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    // Enable the selection of files in the dialog.
    [openDlg setCanChooseFiles:YES];
    
    // Enable the selection of directories in the dialog.
    [openDlg setCanChooseDirectories:YES];
    
    // Display the dialog.  If the OK button was pressed,
    // process the files.
    if ( [openDlg runModalForDirectory:nil file:nil] == NSOKButton )
    {
        // Get an array containing the full filenames of all
        // files and directories selected.
        NSArray* files = [openDlg filenames];
        
        // Loop through all the files and process them.
        for( i = 0; i < [files count]; i++ )
        {
            NSString* fileName = [files objectAtIndex:i];
            
            // Do something with the filename.
            return fileName;
        }
    }
    return nil;
}

- (IBAction)spineAtlasClick:(id)sender {
    NSLog(@"spineAtlasClick");
    NSString* path = [self openDialog];
    if (path!=nil) [_spineAtlasFilePath setStringValue:path];
}

- (IBAction)spineJsonClick:(id)sender {
    NSLog(@"spineJsonClick");
    NSString* path = [self openDialog];
    if (path!=nil) [_spineJsonFilePath setStringValue:path];
}

- (IBAction)polygonJsonClick:(id)sender {
    NSLog(@"polygonJsonClick");
    NSString* path = [self openDialog];
    if (path!=nil) [_polygonJsonFilePath setStringValue:path];
}

- (IBAction)runClick:(id)sender {
    NSLog(@"runClick");
    AppDelegate app;
    cocos2d::Application::getInstance()->run();
}

@end
