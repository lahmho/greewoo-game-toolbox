#include "AlignSpinePolygonScene.h"
#include "AlignSpinePolygonHelper.h"
#include "spine/spine-cocos2dx.h"


USING_NS_CC;

Scene* AlignSpinePolygonLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = AlignSpinePolygonLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool AlignSpinePolygonLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(AlignSpinePolygonLayer::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //draw assisting lines
    DrawNode* linesDrawNode = DrawNode::create();
    linesDrawNode->drawLine(Point(visibleSize.width/2, 0), Point(visibleSize.width/2, visibleSize.height), Color4F(1,0,0,0.5));
    linesDrawNode->drawLine(Point(0, visibleSize.height/2), Point(visibleSize.width, visibleSize.height/2), Color4F(1,0,0,0.5));
    this->addChild(linesDrawNode);
    
    //add info point label
    _infoPointLabel = Label::createWithTTF("(0,0)", "fonts/Marker Felt.ttf", 32);
    _infoPointLabel->setPosition((Point) visibleSize-Point(50,50));
    addChild(_infoPointLabel);
    
    //draw spine skeleton animation
    CCLOG("spine info:\n%s\n%s\n%s",AlignSpinePolygonHelper::getSpineJsonFilePath(), AlignSpinePolygonHelper::getSpineAtlasFilePath(), AlignSpinePolygonHelper::getAnimationName());
    auto skeletonAnimation = spine::SkeletonAnimation::createWithFile(AlignSpinePolygonHelper::getSpineJsonFilePath(), AlignSpinePolygonHelper::getSpineAtlasFilePath(), 0.25);
    skeletonAnimation->retain();
    skeletonAnimation->setAnimation(0, AlignSpinePolygonHelper::getAnimationName(), true);
    skeletonAnimation->setPosition(visibleSize/2);
    this->addChild(skeletonAnimation, 10);
    
    //read polygon vertices from json
    rapidjson::Document doc = readVerticesFromJSON(AlignSpinePolygonHelper::getPolygonJsonFilePath());
    const char * polygonName = AlignSpinePolygonHelper::getPolygonName();
    std::vector<Point> vertices;
    for (rapidjson::SizeType i = 0; i < doc[polygonName].Size(); i++) {
        vertices.push_back(cocos2d::Point(doc[polygonName][i]["x"].GetDouble(), doc[polygonName][i]["y"].GetDouble())/Director::getInstance()->getContentScaleFactor()/2);
    }
    
    //draw polygon
    DrawNode* polygonDrawNode = DrawNode::create();
    cocos2d::Point* points = &vertices[0];
    polygonDrawNode->drawPolygon(points, vertices.size(), Color4F(1,0,0,0.5), 1, Color4F(0,0,1,1));
    polygonDrawNode->setPosition(0,0);
    polygonDrawNode->setScale(0.25);
    //polygonDrawNode->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    skeletonAnimation->addChild(polygonDrawNode);
    
    return true;
}

rapidjson::Document AlignSpinePolygonLayer::readVerticesFromJSON(const char* fileName) {
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    ssize_t size;
    const char* buf = (const char*) FileUtils::getInstance()->getFileData(fullPath.c_str(), "r", &size);
    
    std::string content(buf);
    std::string clearContent = content.substr(0, content.rfind('}') + 1);
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseStopWhenDoneFlag>(clearContent.c_str());
    if(doc.HasParseError()) {
        log("Parsing for JSON file failed : %s", fileName);
    }
    
    return doc;
}

void AlignSpinePolygonLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
