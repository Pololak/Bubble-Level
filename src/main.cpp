#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/ui/Popup.hpp>

class BubbleLevelPopup : public FLAlertLayer, CCAccelerometerDelegate {
protected:
    CCSprite* m_bubble = nullptr;

    bool init() override {
        if (!initWithColor({0,0,0,75})) return false;

        auto director = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();
        geode::cocos::handleTouchPriority(this);
        registerWithTouchDispatcher();
        setID("bubble-level-popup"_spr);

        auto layer = CCLayer::create();
        auto menu = CCMenu::create();
        m_mainLayer = layer;
        m_buttonMenu = menu;

        layer->addChild(menu);
        addChild(layer);

        auto bg = extension::CCScale9Sprite::create("GJ_square01.png");
        bg->setContentSize({300.f, 200.f});
        bg->setPosition(winSize / 2.f);
        layer->addChild(bg, -2);

        m_bubble = CCSprite::createWithSpriteFrameName("gj_navDotBtn_on_001.png");
        m_bubble->setPosition(winSize / 2.f);
        layer->addChild(m_bubble);

        setTouchEnabled(true);
        setKeypadEnabled(true);
        setAccelerometerEnabled(true);
        setAccelerometerInterval(1.);

        return true;
    }

    virtual void didAccelerate(CCAcceleration* pAccelerationValue) {
        m_bubble->setPositionX((CCDirector::sharedDirector()->getWinSize().width / 2.f) + pAccelerationValue->x * 100);
    }

public:
    static BubbleLevelPopup* create() {
        auto ret = new BubbleLevelPopup();
        if (ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};

class $modify(PolzMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto levelButton = CCMenuItemSpriteExtra::create(CCSprite::create("GJ_button_01.png"), this, menu_selector(PolzMenuLayer::openBubbleLevel));
        auto menu = this->getChildByID("bottom-menu");
        menu->addChild(levelButton);
        levelButton->setID("level-button"_spr);
        menu->updateLayout();

        return true;
    }

    void openBubbleLevel(CCObject*) {
        BubbleLevelPopup::create()->show();
    }
};

