#pragma  execution_character_set("utf-8")
#include "prologue.h"
#include "novel.h"
#include "cursor.h"
#include "control.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*
Scene* Prologue::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	//auto scene = Prologue::create();

	// 'layer' is an autorelease object
	//auto layer = Prologue::create();

	// add layer as a child to scene
	//scene->addChild(layer);

	//ノベル
    //auto novel = Novel::create();
	//scene->addChild(novel, 0, 0);
	
	// return the scene
	return scene;
}
*/

bool Prologue::init() {
	if (Scene::init() == false)
		return false;

	this->scheduleUpdate();

	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Novel* novel = (Novel *)this->getChildByTag(0);
	//ノベル
	//auto novel = Novel::create();
	//novel->setBg("bg/bedroom.png");
	//novel->setFontColor(Color3B::BLACK);
	//novel->addSentence("zzz・・・");
	//novel->setFontColor(Color3B::RED);
	//novel->addSentence("？？？「つぐる様…」");
	//novel->setFontColor(Color3B::BLACK);
	//novel->addSentence("zzz・・・");
	//novel->setFontColor(Color3B::RED);
	//novel->addSentence("？？？「つぐる様…？」");
	//novel->setFontColor(Color3B::BLACK);
	//novel->addSentence("zzz・・・");
	//novel->setFontColor(Color3B::RED);
	//novel->addSentence("？？？「つぐる様！！」");
	//novel->setCharaR("chara/tuguru1.png");
	//novel->setFontColor(Color3B::BLUE);
	//novel->addSentence("つぐる「うーん…」");
	//novel->addSentence("つぐる「どうしたの…まだこんな時間なのに…」");
	//novel->setFontColor(Color3B::BLACK);
	//novel->addSentence("ぼくの名前は王国 つぐる");
	//novel->addSentence("その名の通り、父親からこの国をついだ王子だ。");
	//novel->setFontColor(Color3B::RED);
	//novel->setCharaL("chara/celine1.png");
	//novel->addSentence("セリーヌ「いやもう昼過ぎですから」");
	//novel->setFontColor(Color3B::BLACK);
	//novel->addSentence("そしてこちらがメイドのセリーヌ");
	//novel->addSentence("見た目はこわそうだけど、案外優しい…はず");
	//novel->setFontColor(Color3B::RED);
	//novel->addSentence("セリーヌ「こわくないです。…それは置いておいて」");
	//novel->setEndTask();
	//this->addChild(novel, 0, 0);

	mState = &Prologue::scene1;

	auto cursor = Cursor::create();
	cursor->setCursorNum(7);
	this->addChild(cursor, 1, 1);

	//BGM
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/days.ogg");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/dream.ogg");

	//バックログを初期化
	auto path = FileUtils::getInstance()->getWritablePath();
	auto file = path + "speak.log";
	FileUtils::getInstance()->removeFile(file);

	return true;
}

void Prologue::update(float delta){
	(this->*mState)();
}

void Prologue::scene1() {
	if (!this->getChildByTag(0)) {
		auto novel = Novel::create();

		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("何の変哲もない、ある日の早朝。");
		novel->addSentence("・・・・・");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("？？？「マリアー、起きなさい」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("・・・・・");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("？？？「起きて、マリア」");
		novel->setFontColor(Color3B::BLACK);
		novel->setBg("bg/sleeping_princess.png");
		novel->addSentence("・・・・・");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("？？？「どうしたの？マリア」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("・・・・・");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("？？？「マリア…？」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("・・・・・");
		novel->addSentence("少女は、固く目を閉ざしたまま");
		novel->addSentence("じっと、動かなくなっていた");
		novel->setEndTask();
		this->addChild(novel, 0, 0);
		return;
	}

	Novel* novel = (Novel*)(this->getChildByTag(0));
	if (novel->getEndFlag()) {
		mState = &Prologue::scene1_;
		this->removeChild(novel);
	}

	//return (Layer *)novel;
}

void Prologue::scene1_() {
	if (!this->getChildByTag(0)) {
		auto layer = Layer::create();
		layer->runAction(Sequence::create(FadeOut::create(3.0f), RemoveSelf::create(true), CallFunc::create(this,callfunc_selector(Prologue::scene1__)) ,NULL));
		this->addChild(layer, 0, 0);
		return;
	}
}
void Prologue::scene1__() { mState = &Prologue::scene2; }

void Prologue::scene2() {
	if (!this->getChildByTag(0)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/days.ogg", true);
		auto novel = Novel::create();
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("zzz・・・");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("？？？「つぐる様…」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("zzz・・・");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("？？？「継様…？」");
		novel->setBg("bg/bedroom.png");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("zzz・・・");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("？？？「継様！！」");
		novel->setCharaR("chara/tuguru1.png");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「うーん…」");
		novel->addSentence("継「どうしたの…まだこんな時間なのに…」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("ぼくの名前は王国　継（おうこく　つぐる）");
		novel->addSentence("その名の通り、父親からこの国を継いだ王子だ。");
		novel->setFontColor(Color3B::RED);
		novel->setCharaL("chara/celine1.png");
		novel->addSentence("セリーヌ「いやもう昼過ぎですから」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("そしてこちらがメイドのセリーヌ");
		novel->addSentence("見た目は怖そうだけど、案外優しい…はず");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「怖くないです。…それは置いておいて」");
		novel->addSentence("セリーヌ「今日は学校へ行った方がよろしいかと、さすがに１０日連続で休まれると単位が…」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「えー…でも、昨日仕事したじゃん」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("国王でありながらも、ぼくはまだ１６歳。");
		novel->addSentence("政治のお仕事をしながら魔法の修行もしなければならないのだ");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「つらい」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「まあ、顔を出すだけでも…」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「うぅ…わかったよ…」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「ご理解いただきありがとうございます。では、身支度がお済みになったらお声がけください。」");
		novel->setEndTask();
		this->addChild(novel, 0, 0);
		return;
	}

	Novel* novel = (Novel*)(this->getChildByTag(0));
	if (novel->getEndFlag()) {
		mState = &Prologue::scene3;
		this->removeChild(novel);
	}

	//return (Layer *)novel;
}

void Prologue::scene3() {
	if (!this->getChildByTag(0)) {
		auto novel = Novel::create();

		novel->setFontColor(Color3B::BLUE);
		novel->setCharaR("chara/tuguru1.png");
		novel->addSentence("継「はぁはぁ…」");
		novel->setBg("bg/school.png");
		novel->addSentence("継「つ、着いた…」");
		novel->addSentence("継「馬車が故障中だからってほうきであんなに飛ばさなくても…」");
		novel->setCharaL("chara/celine1.png");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「失礼しました。」");
		novel->setCharaC("chara/bandana1.png");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("？？？「あれ…？」");
		novel->addSentence("？？？「もう授業終わったけど…何しに来たの…？」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("こいつはクラスメイトのバイロン・ダイエナ。通称バンダナ");
		novel->addSentence("その名の通りいつもバンダナを身に着けている");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「はー…」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「申し訳ありません…」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("バンダナ「あっ…」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaC("chara/suama1.png");
		novel->addSentence("？？？「あ、つぐるん久しぶり～」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("こちらもクラスメイトの立花　寿甘（たちばな　すあま）");
		novel->addSentence("いつも麦わら帽子をかぶっている");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("寿甘「あれ…？マリアちゃんは一緒じゃないの？」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「？…何のこと？」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("寿甘「いやね、マリアちゃんもここ数日来てなかったから。てっきりデートでもしてるのかと思ったんだけど…」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("マリア・ミルフィーユ。彼女もまたクラスメイトだ。…あんまり話したことはないけど");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「どうしてそういう思考に至ったのか理解できないけど。心配だね。」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("寿甘「だからね、これからおうちに行って様子を見に行こうかと思うの」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「それならばお送りいたしましょうか」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「あれ？馬車壊れてるんじゃなかったっけ？」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「とらバスなら今呼び出せますので」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「なんでさっきそれ使わなかったの！？」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("寿甘「そうと決まればみんなで行こっか！」");

		novel->setEndTask();
		this->addChild(novel, 0, 0);
		return;
	}

	Novel* novel = (Novel*)(this->getChildByTag(0));
	if (novel->getEndFlag()) {
		mState = &Prologue::scene4;
		this->removeChild(novel);
	}

}

void Prologue::scene4() {
	if (!this->getChildByTag(0)) {
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		auto novel = Novel::create();

		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("～マリアの家～");
		novel->setCharaC("chara/suama1.png");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("寿甘「すみませーん」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("マリアの母「あら…マリアのお友達？」");
		novel->addSentence("マリアの母「継様とセリーヌ様まで…」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("寿甘「私たち、マリアちゃんのお見舞いにきました！」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("マリアの母「それはそれは…ありがとうございます…」");
		novel->addSentence("マリアの母「よかったら上がっていってください」");
		novel->setCharaC("");
		novel->setCharaR("chara/tuguru1.png");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「これは…」");
		novel->setBg("bg/sleeping_princess.png");
		novel->addSentence("継「まだ寝てるのかな」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("マリアの母「実は…」");
		novel->addSentence("マリアの母「マリアは数日前からずっと目を覚まさないのです」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「！？」");
		novel->setCharaC("chara/bandana1.png");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("バンダナ「死んでるのか…？」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaL("chara/celine1.png");
		novel->addSentence("セリーヌ「…息はあるみたいですね」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("マリアの母「セリーヌ様。何かわかりますか…？」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("セリーヌは心理魔法のプロであり、他人の心や身体の状態を読み取るのが得意なのだ。");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「彼女は今夢の中をさまよっていて、そこから出られない状況にあるようです」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「それって…魔法でなんとかならないの…？」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「一つだけ…方法があります」");
		novel->addSentence("セリーヌ「それは、彼女の夢の中に入って、彼女を連れ戻すことです」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaC("chara/suama1.png");
		novel->addSentence("寿甘「じゃあ、行くっきゃないっしょ！」");
		novel->addSentence("寿甘「みんなもいくよね？」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「うん、もちろんだよ」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「危険が伴うかもしれません。私も一緒に行きます」");
		novel->addSentence("セリーヌ「お母様はここでマリア様を見守っていてください」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("マリアの母「皆さま本当に、ありがとうございます…」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「では、準備はよろしいでしょうか」");
		novel->addSentence("セリーヌ「それでは皆様、目を瞑ってください」");

		novel->setEndTask();
		this->addChild(novel, 0, 0);
		return;
	}

	Novel* novel = (Novel*)(this->getChildByTag(0));
	if (novel->getEndFlag()) {
		mState = &Prologue::scene5;
		this->removeChild(novel);
	}

}

void Prologue::scene5() {
	if (!this->getChildByTag(0)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/dream.ogg", true);

		auto novel = Novel::create();

		novel->setFontColor(Color3B::BLUE);
		novel->setCharaR("chara/tuguru1.png");
		novel->addSentence("継「…うーん」");
		novel->setBg("forest1_.png");
		novel->addSentence("継「ここは…？」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaC("chara/suama1.png");
		novel->addSentence("寿甘「森…みたいだね」");
		novel->addSentence("寿甘「でもなんで白黒なんだろ」");
		novel->setCharaC("chara/bandana1.png");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("バンダナ「人が見る夢なんて大体白黒なんじゃねえか？」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaL("chara/celine1.png");
		novel->addSentence("セリーヌ「いえ、この魔法では色付きで見られるはずです」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「何か原因があるのかな」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaC("chara/suama1.png");
		novel->addSentence("寿甘「…んん！？身体が思うように動かないっ…！」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「うわっ！ほんとだ！！」");
		novel->addSentence("継「どうするんだよ！セリーヌ！！」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「どうやら色の無い場所では動きが制限されてしまうようですね」");
		novel->addSentence("セリーヌ「軽く結界を張りますので、その間に何か手立てがないか辺りを調べてみましょう」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「探索…？」");
		novel->setCharaC("chara/bandana1.png");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("バンダナ「画面を隈なくタップしていくあれか？」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「それも可能ですがこのゲームにはちょっとしたテクニックがあるのです」");
		novel->setCharaR("");
		novel->setCharaC("tutorial1.png");
		novel->addSentence("セリーヌ「画面をタッチするとルーペのカーソルが出てきます」");
		novel->addSentence("セリーヌ「そのままスライドしてカーソルに反応がないか探していきます」");
		novel->setCharaC("tutorial2.png");
		novel->addSentence("セリーヌ「カーソルに反応があったらそこでタップしてみましょう」");
		novel->addSentence("セリーヌ「その場所を調べたり、アイテムをゲットしたり、場所を移動したりすることができます」");
		novel->setFontColor(Color3B::BLUE);
		novel->setCharaR("chara/tuguru1.png");
		novel->setCharaC("");
		novel->addSentence("継「よし、わかった。早速探索開始だね！」");


		novel->setEndTask();
		this->addChild(novel, 0, 0);
		return;
	}

	Novel* novel = (Novel*)(this->getChildByTag(0));
	if (novel->getEndFlag()) {
		mState = &Prologue::scene5_;
		this->removeChild(novel);
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, Control::create(), Color3B::BLACK));
	}

}

void Prologue::scene5_() {}