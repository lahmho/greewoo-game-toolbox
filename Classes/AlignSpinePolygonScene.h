#ifndef __AlignSpinePolygonLayer_SCENE_H__
#define __AlignSpinePolygonLayer_SCENE_H__

#include "cocos2d.h"
#include "json/document.h"
#include "spine/spine-cocos2dx.h"

USING_NS_CC;
using namespace std;

class AlignSpinePolygonLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    rapidjson::Document readVerticesFromJSON(const char* fileName);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(AlignSpinePolygonLayer);
    
    void onMouseDown(Event *event);
    void onMouseUp(Event *event);
    void onMouseMove(Event *event);
    void onMouseScroll(Event *event);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    
protected:
    cocos2d::Label* _infoPointLabel;
    spine::SkeletonAnimation* _skeletonAnimation;
    DrawNode* _polygonDrawNode;
    Point _infoPoint;
};

#endif // __AlignSpinePolygonLayer_SCENE_H__
