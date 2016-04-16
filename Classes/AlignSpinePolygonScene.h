#ifndef __AlignSpinePolygonLayer_SCENE_H__
#define __AlignSpinePolygonLayer_SCENE_H__

#include "cocos2d.h"
#include "json/document.h"

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
    
protected:
    cocos2d::Label* _infoPointLabel;
};

#endif // __AlignSpinePolygonLayer_SCENE_H__
