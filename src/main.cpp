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
        bg->setContentSize({200.f, 100.f});
        bg->setPosition(winSize / 2.f);
        layer->addChild(bg, -2);
        menu->setPosition(winSize / 2.f);

        auto closeSpr = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
        closeSpr->setScale(.6f);
        auto closeBtn = CCMenuItemSpriteExtra::create(closeSpr, this, menu_selector(BubbleLevelPopup::onClose));
        closeBtn->setPosition({-95.f, 45.f});
        menu->addChild(closeBtn);

        auto label = CCLabelBMFont::create("Bubble Level", "goldFont.fnt");
        label->setScale(.75f);
        label->setPosition({winSize.width / 2.f, winSize.height / 2.f + 35.f});
        layer->addChild(label);

        auto bbgOutline = extension::CCScale9Sprite::create("square02b_small.png");
        bbgOutline->setScale(.55f);
        bbgOutline->setColor({0,0,0});
        bbgOutline->setContentSize({224.f, 42.f});
        bbgOutline->setPosition(winSize / 2.f);
        layer->addChild(bbgOutline);

        auto bbg = extension::CCScale9Sprite::create("square02b_small.png");
        bbg->setScale(.5f);
        bbg->setColor({130,220,130});
        bbg->setContentSize({240.f, 40.f});
        bbg->setPosition(winSize / 2.f);
        layer->addChild(bbg);

        m_bubble = CCSprite::createWithSpriteFrameName("gj_navDotBtn_on_001.png");
        m_bubble->setPosition(winSize / 2.f);
        m_bubble->setColor({0,255,120});
        layer->addChild(m_bubble);

        auto leftLine = CCSprite::createWithSpriteFrameName("persp_outline_02_001.png");
        leftLine->setScale(.725f);
        leftLine->setRotation(90.f);
        leftLine->setColor({0,0,0});
        leftLine->setPosition({winSize.width / 2.f - 14.f, winSize.height / 2.f});
        layer->addChild(leftLine);

        auto rightLine = CCSprite::createWithSpriteFrameName("persp_outline_02_001.png");
        rightLine->setScale(.725f);
        rightLine->setRotation(-90.f);
        rightLine->setColor({0,0,0});
        rightLine->setPosition({winSize.width / 2.f + 14.f, winSize.height / 2.f});
        layer->addChild(rightLine);

        setTouchEnabled(true);
        setKeypadEnabled(true);
        setAccelerometerEnabled(true);

        return true;
    }

    virtual void didAccelerate(CCAcceleration* pAccelerationValue) override {
        m_bubble->setPositionX((CCDirector::sharedDirector()->getWinSize().width / 2.f) + pAccelerationValue->x * 50);
    }

    void keyBackClicked() override {
        setTouchEnabled(false);
        setAccelerometerEnabled(false);
        removeFromParentAndCleanup(true);
    }

    void onClose(CCObject*) {
        keyBackClicked();
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

