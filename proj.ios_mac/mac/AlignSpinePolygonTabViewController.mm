//
//  AlignSpinePolygonTabViewController.m
//  greewoo-game-toolbox
//
//  Created by greewoo on 4/16/16.
//
//

#import "AlignSpinePolygonTabViewController.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "AlignSpinePolygonHelper.h"


@interface AlignSpinePolygonTabViewController ()

@end

@implementation AlignSpinePolygonTabViewController


static AlignSpinePolygonTabViewController* _instance = nil;

+ (AlignSpinePolygonTabViewController*) getInstance {
    return _instance;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
    
    NSLog(@"viewDidLoad");
    _instance = self;
    
    [self funcHelperWithValue: [[NSUserDefaults standardUserDefaults]
                                stringForKey:@"spine-atlas"] textField: _spineAtlasFilePath];
    [self funcHelperWithValue: [[NSUserDefaults standardUserDefaults]
                                stringForKey:@"spine-json"] textField: _spineJsonFilePath];
    [self funcHelperWithValue: [[NSUserDefaults standardUserDefaults]
                                stringForKey:@"polygon-json"] textField: _polygonJsonFilePath];
    [self funcHelperWithValue: [[NSUserDefaults standardUserDefaults]
                                stringForKey:@"animation-name"] textField: _animationName];
    [self funcHelperWithValue: [[NSUserDefaults standardUserDefaults]
                                stringForKey:@"polygon-name"] textField: _polygonName];
}

- (void) funcHelperWithValue: (NSString*) value key: (NSString*) key textField: (NSTextField*) textField {
    [self funcHelperWithValue: value textField: textField];
    if (value!=nil) {
        [[NSUserDefaults standardUserDefaults] setObject:value forKey:key];
    }
}

- (void) funcHelperWithValue: (NSString*) value textField: (NSTextField*) textField {
    if (value!=nil) {
        [textField setStringValue:value];
    }
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
    [self funcHelperWithValue: [self openDialog] key:@"spine-atlas" textField: _spineAtlasFilePath];
}

- (IBAction)spineJsonClick:(id)sender {
    NSLog(@"spineJsonClick");
    [self funcHelperWithValue: [self openDialog] key:@"spine-json" textField: _spineAtlasFilePath];
}

- (IBAction)polygonJsonClick:(id)sender {
    NSLog(@"polygonJsonClick");
    [self funcHelperWithValue: [self openDialog] key:@"polygon-json" textField: _spineAtlasFilePath];
}

- (IBAction)runClick:(id)sender {
    NSLog(@"runClick");
    
    NSAssert(![[_spineAtlasFilePath stringValue] isEqualToString:@"Spine atlas file path"], @"Please select spine atlas file");
    NSAssert(![[_spineJsonFilePath stringValue] isEqualToString:@"Spine json file path"], @"Please select spine json file");
    NSAssert(![[_polygonJsonFilePath stringValue] isEqualToString:@"Polygon json file path"], @"Please select polygon json file");
    
    AppDelegate app;
    cocos2d::Application::getInstance()->run();
}

- (IBAction)animationNameAction:(id)sender {
    NSLog(@"animationNameAction");
    [self funcHelperWithValue:[_animationName stringValue] key:@"animation-name" textField: _animationName];
}

- (IBAction)polygonNameAction:(id)sender {
    NSLog(@"polygonNameAction");
    [self funcHelperWithValue:[_polygonName stringValue] key:@"polygon-name" textField: _polygonName];
}

@end
