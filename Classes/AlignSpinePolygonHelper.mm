//
//  AlignSpinePolygonHelper.cpp
//  greewoo-game-toolbox
//
//  Created by greewoo on 4/15/16.
//
//

#include "AlignSpinePolygonHelper.h"
#import "AlignSpinePolygonTabViewController.h"


//AlignSpinePolygonHelper
const char* AlignSpinePolygonHelper::getSpineAtlasFilePath() {
    return [[[[AlignSpinePolygonTabViewController getInstance] spineAtlasFilePath] stringValue] UTF8String];
}

const char* AlignSpinePolygonHelper::getSpineJsonFilePath() {
    return [[[[AlignSpinePolygonTabViewController getInstance] spineJsonFilePath] stringValue] UTF8String];
}

const char* AlignSpinePolygonHelper::getPolygonJsonFilePath() {
    return [[[[AlignSpinePolygonTabViewController getInstance] polygonJsonFilePath] stringValue] UTF8String];
}

const char* AlignSpinePolygonHelper::getAnimationName() {
    return [[[[AlignSpinePolygonTabViewController getInstance] animationName] stringValue] UTF8String];
}

const char* AlignSpinePolygonHelper::getPolygonName() {
    return [[[[AlignSpinePolygonTabViewController getInstance] polygonName] stringValue] UTF8String];
}