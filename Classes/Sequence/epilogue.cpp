#pragma  execution_character_set("utf-8")
#include "epilogue.h"
#include "Title.h"
#include "System/novel.h"
#include "System/cursor.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

bool Epilogue::init() {
	if (Scene::init() == false)
		return false;

	this->scheduleUpdate();

	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto cursor = Cursor::create();
	cursor->setCursorNum(7);
	this->addChild(cursor, 1, 1);

	//BGM
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/color.ogg");

	auto novel = Novel::create();
	novel->setBg("chara/cry_sakura.png");
	novel->setFontColor(Color3B::RED);
	novel->addSentence("桜「マリアちゃぁぁぁぁあん………！！」");
	novel->addSentence("マリア「…ぅ…」 ");
	novel->addSentence("桜「マリアちゃん…？」 ");
	novel->addSentence("マリア「…？あれ…？」");
	novel->addSentence("桜「…あ……」");
	novel->addSentence("桜「よかったぁぁぁああ！！！！マリアちゃんが起きてくれたぁぁあ！！！！」");
	novel->addSentence("マリア「どうして…もう会えないかと思ってたのに……」");
	novel->addSentence("桜「セリーヌ様がね…っ…知らせに来てくれたんだよ…！」");
	novel->addSentence("桜「私…重い病気にかかっちゃって……ずっと身動きが取れなくて…病気もつらくて…会いに行けなかったんだけど……」");
	novel->addSentence("桜「さっきセリーヌ様がマリアちゃんのこと知らせに来てくれてね…！…病気も治してくれて…大きな車で空を飛んでね…！すごかったんだよ…！！」");
	novel->addSentence("マリア「それは…ほんとにすごいね…」");
	novel->setBg("bg/bedroom_maria.png");
	novel->setCharaL("chara/celine1.png");
	novel->addSentence("セリーヌ「引っ越し先での国では、魔法があまり発達してなかったようでしたので、こちらからお迎えいたしました」");
	novel->addSentence("セリーヌ「臣下の者にも手伝わせて…少々大掛かりになってしまいましたが」");
	novel->setCharaC("chara/tuguru1.png");
	novel->setFontColor(Color3B::BLUE);
	novel->addSentence("継「なるほど…考えがあるって言うのはこう言うことだったんだね」");
	novel->setCharaR("chara/maria1.png");
	novel->setFontColor(Color3B::RED);
	novel->addSentence("マリア「…あ、あなたは…夢で会った…！」");
	novel->setFontColor(Color3B::BLUE);
	novel->addSentence("継「僕は、王国継だよ。同じクラスで、一応王子なんだけど…あまり学校に来れてないし、影が薄かったから忘れてたかな？」");
	novel->setFontColor(Color3B::RED);
	novel->addSentence("マリア「う…い、いえ！！滅相もない！！！」");
	novel->setFontColor(Color3B::BLUE);
	novel->addSentence("継「あはは、そんなにかしこまらなくてもいいよ。何だって友達だからね」");
	novel->setFontColor(Color3B::RED);
	novel->addSentence("マリア「友達…？私と……？」");
	novel->setCharaL("chara/suama1.png");
	novel->addSentence("寿甘「私もいるよー！」");
	novel->setCharaC("chara/bandana1.png");
	novel->setFontColor(Color3B::BLUE);
	novel->addSentence("バンダナ「俺みたいなガキ大将もいるぜ！」");
	novel->setFontColor(Color3B::RED);
	novel->addSentence("マリア「い、いいんでしょうか……私なんかネクラだし…気持ち悪い絵ばっかり描いてるし…」");
	novel->addSentence("寿甘「全っ然素敵じゃん！」");
	novel->addSentence("寿甘「んーまあ私たちも似たようなもんだし？」");
	novel->addSentence("寿甘「つぐるんは、王子でコミュ障だからみんなから一目置かれて近付かれないし」");
	novel->addSentence("寿甘「バンダナは、魔法に頼らないって言うポリシーだけでも浮いちゃってるのにその上ケンカも強いからね…」");
	novel->setFontColor(Color3B::BLUE);
	novel->addSentence("バンダナ「まあお前には敵わないけどな！」");
	novel->setFontColor(Color3B::RED);
	novel->addSentence("寿甘「えっへん！…私もこう見えて、見えないものが見えちゃったりする体質だから、周りから気持ち悪がられちゃったりするのよ」");
	novel->addSentence("寿甘「だからぜーんぜん問題無いよー！！」");
	novel->setCharaC("chara/sakura1.png");
	novel->addSentence("桜「うふふ、いいお友達できたじゃなーい！」");
	novel->addSentence("マリア「そ、そうかな…」");
	novel->setCharaL("chara/celine1.png");
	novel->addSentence("セリーヌ「交通手段なら、こちらでいくらでも用意できますし、桜様も時々遊びに来てはいかが？」");
	novel->addSentence("桜「え、いいんですか！？それではありがたくそうさせてもらいます！」");
	novel->setFontColor(Color3B::BLUE);
	novel->setCharaL("chara/bandana1.png");
	novel->addSentence("バンダナ「つぐるんと友達になると、こう言う風に、コネも使えるんだぜ！」");
	novel->setCharaC("chara/tuguru1.png");
	novel->addSentence("継「酷い言いようだなあ」");
	novel->addSentence("継「それじゃあ、マリアちゃん。これからよろしくね」");
	novel->setFontColor(Color3B::RED);
	novel->addSentence("マリア「…」");
	novel->addSentence("マリア「うん！」");

	novel->setEndTask();
	this->addChild(novel, 0, "novel");

	mSkip = 0;
	mEnd = false;

	auto _userDef = UserDefault::getInstance();
	_userDef->setBoolForKey("clear", true);
	_userDef->flush();

	return true;
}

void Epilogue::update(float delta) {
	Novel* novel = (Novel*)(this->getChildByName("novel"));
	if (novel) {
		if (novel->getEndFlag()) {
			removeChild(novel);
			
			Size display = Director::getInstance()->getVisibleSize();
			Vec2 origin = Director::getInstance()->getVisibleOrigin();

			float showTime = 10;
			float delayTime = 2;

			auto ed = Sprite::create("bg/ed0.png");
			ed->setOpacity(0.0f);
			ed->setPosition(display / 2);
			ed->runAction(Sequence::create(
				FadeIn::create(5.0f),
				DelayTime::create((showTime + delayTime * 2 ) * 11),
				CallFunc::create([this] {
				mEnd = true;
			}),
				NULL
			));
			addChild(ed, 0, "bg");

			auto listener = EventListenerTouchOneByOne::create();
			listener->onTouchBegan = [this](Touch* touch, Event* event) {
				mSkip++;
				//log("%d,%d", 50 - mSkip, mEnd);
				if (mSkip == 50) {
					Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
				}
				else if (mEnd == true) {
					event->getCurrentTarget()->runAction(Sequence::create(
						FadeOut::create(3.0f),
						CallFunc::create([this] {
						Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
					}),
						NULL
					));
					getChildByName("last")->runAction(FadeOut::create(3.0f));
				}
				return true;
			};
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, ed);


			std::stringstream s;

			for (int i = 1; i < 12; i++) {
				s.str(""); s.clear();
				s << "bg/ed" << i << ".png";
				auto spr = Sprite::create(s.str());
				spr->setOpacity(0.0f);
				spr->setPosition(display / 2);
				spr->runAction(Sequence::create(
					DelayTime::create((showTime + delayTime * 2) * (i-1)),
					FadeIn::create(delayTime),
					DelayTime::create(showTime),
					FadeOut::create(delayTime),
					NULL
				));
				addChild(spr, 1, s.str());
			}

			auto last = Sprite::create("bg/ed12.png");
			last->setOpacity(0.0f);
			last->setPosition(display / 2);
			last->runAction(Sequence::create(
				DelayTime::create((showTime + delayTime * 2) * 11),
				FadeIn::create(delayTime),\
				NULL
			));
			addChild(last, 1, "last");
		}
	}
}