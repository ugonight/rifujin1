#pragma  execution_character_set("utf-8")
#include "epilogue.h"
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
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

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
	novel->setEndTask();
	this->addChild(novel, 0, "novel");


	return true;
}