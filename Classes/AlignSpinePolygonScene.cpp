#include "AlignSpinePolygonScene.h"
#include "AlignSpinePolygonHelper.h"

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
    _skeletonAnimation = spine::SkeletonAnimation::createWithFile(AlignSpinePolygonHelper::getSpineJsonFilePath(), AlignSpinePolygonHelper::getSpineAtlasFilePath(), 0.25);
    _skeletonAnimation->retain();
    _skeletonAnimation->setAnimation(0, AlignSpinePolygonHelper::getAnimationName(), true);
    _skeletonAnimation->setPosition(visibleSize/2);
    this->addChild(_skeletonAnimation, 10);
    
    //read polygon vertices from json
    rapidjson::Document doc = readVerticesFromJSON(AlignSpinePolygonHelper::getPolygonJsonFilePath());
    const char * polygonName = AlignSpinePolygonHelper::getPolygonName();
    std::vector<Point> vertices;
    for (rapidjson::SizeType i = 0; i < doc[polygonName].Size(); i++) {
        vertices.push_back(cocos2d::Point(doc[polygonName][i]["x"].GetDouble(), doc[polygonName][i]["y"].GetDouble())/Director::getInstance()->getContentScaleFactor()/2);
    }
    
    //draw polygon
    _polygonDrawNode = DrawNode::create();
    cocos2d::Point* points = &vertices[0];
    _polygonDrawNode->drawPolygon(points, vertices.size(), Color4F(1,0,0,0.5), 1, Color4F(0,0,1,1));
    _polygonDrawNode->setPosition(0,0);
    _polygonDrawNode->setScale(0.5);
    //polygonDrawNode->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    _skeletonAnimation->addChild(_polygonDrawNode);
    

    //add mouse listener
    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseMove = CC_CALLBACK_1(AlignSpinePolygonLayer::onMouseMove, this);
    _mouseListener->onMouseUp = CC_CALLBACK_1(AlignSpinePolygonLayer::onMouseUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(AlignSpinePolygonLayer::onMouseDown, this);
    _mouseListener->onMouseScroll = CC_CALLBACK_1(AlignSpinePolygonLayer::onMouseScroll, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    
    //Initializing and binding
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(AlignSpinePolygonLayer::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(AlignSpinePolygonLayer::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    _infoPoint = Point(0,0);
    
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

void AlignSpinePolygonLayer::onMouseDown(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    string str = "Mouse Down detected, Key: ";
    str += to_string(e->getMouseButton());
    CCLOG(str.c_str());
}

void AlignSpinePolygonLayer::onMouseUp(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    string str = "Mouse Up detected, Key: ";
    str += to_string(e->getMouseButton());
    CCLOG(str.c_str());
}

void AlignSpinePolygonLayer::onMouseMove(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    string str = "MousePosition X:";
    str = str + to_string(e->getCursorX()) + " Y:" + to_string(e->getCursorY());
    //CCLOG(str.c_str());
}

void AlignSpinePolygonLayer::onMouseScroll(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    string str = "Mouse Scroll detected, X: ";
    str = str + to_string(e->getScrollX()) + " Y: " + to_string(e->getScrollY());
    //CCLOG(str.c_str());
}

void AlignSpinePolygonLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d pressed", keyCode);
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            _polygonDrawNode->setPositionY(_polygonDrawNode->getPositionY()+1);
            _infoPoint += Point(0,1);
            break;
            
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            _polygonDrawNode->setPositionY(_polygonDrawNode->getPositionY()-1);
            _infoPoint += Point(0,-1);
            break;
            
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            _polygonDrawNode->setPositionX(_polygonDrawNode->getPositionX()-1);
            _infoPoint += Point(-1,0);
            break;
            
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            _polygonDrawNode->setPositionX(_polygonDrawNode->getPositionX()+1);
            _infoPoint += Point(1,0);
            break;
            
        default:
            break;
    }
    
    _infoPointLabel->setString(StringUtils::format("(%.0f,%.0f)", _infoPoint.x, _infoPoint.y));
}

void AlignSpinePolygonLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d released", keyCode);
}
