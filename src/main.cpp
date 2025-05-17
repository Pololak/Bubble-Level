#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/ui/Popup.hpp>

class BubbleLevelPopup : public Popup<>, public CCAccelerometerDelegate {
protected:
    CCSprite* m_bubble = nullptr;

    bool setup() override {
        setID("bubble-level-popup"_spr);
        setTitle("Bubble Level");

        m_bubble = CCSprite::createWithSpriteFrameName("gj_navDotBtn_on_001.png");
        addChild(m_bubble);

        setAccelerometerEnabled(true);
        setAccelerometerInterval(1.);
    }

    virtual void didAccelerate(CCAcceleration* pAccelerationValue) {
        m_bubble->setPositionX((CCDirector::sharedDirector()->getWinSize().width / 2.f) + pAccelerationValue->x * 100);
    }

public:
    static BubbleLevelPopup* create() {
        auto ret = new BubbleLevelPopup();
        if (ret->initAnchored(240.f, 160.f)) {
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

