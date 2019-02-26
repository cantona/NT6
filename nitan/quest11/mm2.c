// 通寶物品答疑 mm2.c
// by fengyue 0808
#include <ansi.h>

inherit NPC;

int do_look(string);
int ask_me();
int ask_wuliao();

int ask_cantu();
int ask_daopu();
int ask_ebook();
int ask_tianlong();
int ask_jingpa();
int ask_kongxin();
int ask_pearl();
int ask_putao();
int ask_shuzhi();
int ask_suizhi();
int ask_taijitu();
int ask_wcard();
int ask_yuji();
int ask_zhanshu();
int ask_shenshu();
int ask_fail();


void create()
{
     set_name("奧黛雷赫", ({ "audrey hepburn","girl", "meimei" }) );
      set("title",HIC"假日公主"NOR);
     //set("nickname",HIR"專 用"NOR);
     set("gender", "女性" );
     set("age", 18);
     set("long","奧黛麗·凱瑟琳·赫本-魯斯頓（Audrey Kathleen Hepburn-Ruston）;\n"+
                "假日裏的小公主。\n");
     set("combat_exp", 10000);
     set("attitude", "friendly");
     set("no_get", 1);
     set("per", 30);
     set("inquiry", ([
//                   "sex" :         (: ask_me :),
//                  "make love" :   (: ask_me :),
//                   "QQ" :          (: ask_wuliao :),
//                   "電話號碼" :    (: ask_wuliao :),
//                   "qq" :          (: ask_wuliao :),
//                   "msn" :         (: ask_wuliao :),
//                   "手機號碼" :    (: ask_wuliao :),
//                   "name" :        (: ask_wuliao :),

                   "苗家劍法殘圖" : (: ask_cantu :),
                   "cantu" :        (: ask_cantu :),

                   "破舊刀譜" :     (: ask_daopu :),
                   "daopu" :        (: ask_daopu :),

                   "精英之書" :     (: ask_ebook :),
                   "ebook" :        (: ask_ebook :),

                   "天龍八部" :     (: ask_tianlong :),
                   "tianlong" :     (: ask_tianlong :),

                   "鴛鴦錦帕" :     (: ask_jingpa :),
                   "jingpa" :       (: ask_jingpa :),

                   "空心散" :       (: ask_kongxin :),
                   "kongxinsan" :   (: ask_kongxin :),

                   "幸運珍珠" :     (: ask_pearl :),
                   "pearl" :        (: ask_pearl :),

                   "神奇葡萄" :     (: ask_putao :),
                   "putao" :        (: ask_putao :),

                   "小樹枝"  :      (: ask_shuzhi :),
                   "xiaoshuzhi"  :  (: ask_shuzhi :),

                   "碎紙片" :       (: ask_suizhi :),
                   "suizhi pian" :  (: ask_suizhi :),

                   "太極圖" :       (: ask_taijitu :),
                   "taijitu" :      (: ask_taijitu :),

                   "清池貴賓卡" :   (: ask_wcard :),
                   "guibinka" :     (: ask_wcard :),


                   "玉肌丸" :       (: ask_yuji :),
                   "yujiwan" :      (: ask_yuji :),

                   "獨孤戰書" :     (: ask_zhanshu :),
                   "zhanshu" :      (: ask_zhanshu :),

                   "金庸全集" :     (: ask_shenshu :),
                   "shenshu" :      (: ask_shenshu :),

                   "失敗" :     (: ask_fail :),

                     ]) );

      setup();
         carry_object(ARMOR_D("changqun"))->wear();
         carry_object(ARMOR_D("flower_shoe"))->wear();
}


void init()
{
	object ob;

	::init();
	add_action("do_look","kiss1");
	add_action("do_look","kick");
	add_action("do_look","flirt");
	add_action("do_look","loveshoe");

	if( interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

int ask_me()
{
	object me;

	me = this_player();
	switch( random(5) ) {
		case 0:
			message("vision", "美眉向" + me->name() +"怒道：你無聊不無聊呀。流氓！你出去！\n", me );
			command("slap " + me->query("id"));
			remove_call_out("kicking");
			call_out("kicking", 1, me);
			break;
		case 1:
			message("vision", "美眉向" + me->name() +"怒道：你無聊不無聊呀。流氓！你出去！\n", me );
			command("kick " + me->query("id"));
			remove_call_out("kicking");
			call_out("kicking", 1, me);
			break;
		case 2:
			command("faint " + me->query("id"));
			break;
		case 3:
			command("rascal " + me->query("id"));
			command("kick2 " + me->query("id"));
			break;
		case 4:
			command("xixi " + me->query("id"));
			command("benger " + me->query("id"));
	}
	return 1;
}

int do_look(string target)
{
	object me;

	me = this_player();
	if (target=="shuang" || target=="shuang er")
	if ((string)me->query("gender") != "女性") {
		message("vision", "美眉向" + me->name() +"道：你無聊不無聊呀。\n", me );
		switch( random(5) ) {
			case 0:
				command("club " + me->query("id"));
				remove_call_out("kicking");
				call_out("kicking", 1, me);
				break;
			case 1:
				command("kick " + me->query("id"));
				remove_call_out("kicking");
				call_out("kicking", 1, me);
				break;
			case 2:
				command("faint " + me->query("id"));
				break;
			case 3:
				command("stare " + me->query("id"));
				break;
			case 4:
				command("rascal " + me->query("id"));
				command("kick2 " + me->query("id"));
		}
	}
	return 0;

}

void kicking(object me)
{
	if (!me || environment(me) != environment()
	|| environment(this_object())->query("short") != "當鋪")
		return;

	me->move("/d/city/guangchangnan");
	message("vision","只聽“嘭”地一聲，緊接着" +  me->query("name") +
		"從當鋪裏飛了出來，臉上一個紅手印，屁股上有一個小鞋印。\n", environment(me), me);
}

int ask_wuliao()
{
     object me;

	me = this_player();
            command("mimi "+me->query("id") );
            command("? ");
            command("hmm ");
         return 1;
}

int ask_cantu()
{
     object me;
     me = this_player();
     command("say 本週你好像已經翻閲過"+ chinese_number(me->query("spec/cantu")) +NOR"次苗家劍法殘圖了。");
     command("say 這些殘圖我已經翻(fanyue mjjf cantu)過好多遍了，可是上面的劍招太難了，沒人指點，我總是學不會。");
     command("sigh ");
     command("say 你知道誰能指點我一下嘛？要不等你學會了回來教我好不好？ ");
     command("addoil girl ");
         return 1;
}
int ask_daopu()
{
     object me;
     me = this_player();
     command("say 本週你已經弄壞了"+ HIR+chinese_number(me->query("spec/daopu")) +NOR"本破舊刀譜了。");
     command("say 據説這上面紀錄的是傳説中享譽江湖的胡家刀法呢！");
     command("say 看不清楚的話,我可以借個放大鏡給你仔細辨認一下(bianren pojiu daopu)，不過你要請我吃哈根達斯哦！");
     command("smile ");
         return 1;
}
int ask_ebook()
{
     object me;
     me = this_player();
     command("say 本週你已經用掉了"+ HIR+chinese_number(me->query("spec/ebook")) +NOR"本精英之書。");
     command("say 怎麼才漲了這麼點經驗啊？");
     command("push ");
         return 1;
}
int ask_tianlong()
{
     object me;
     me = this_player();
     command("say 本週你已經讀(read)過"+ HIR+chinese_number(me->query("spec/tianlong")) +NOR"遍天龍八部了。");
     command("say 我最崇拜裏面的蕭峯蕭大哥了！");
     command("say 最可憐的人還是阿紫啊！");
     command("sigh ");
         return 1;
}
int ask_jingpa()
{
     object me;
     me = this_player();
     command("say 本週你已經歸還給瑛姑阿姨"+ HIR+chinese_number(me->query("spec/jingpa")) +NOR"方鴛鴦錦帕。");
     command("say 她有沒有教你點鬼穀神機術啊？");
     command("say 不過這死老太婆老不肯教我，説我笨。");
     command("shout ");
         return 1;
}
int ask_kongxin()
{
     object me;
     me = this_player();
     command("say 本週你已經服用過"+ HIR+chinese_number(me->query("spec/kongxin")) +NOR"次空心散。");
     command("say 服用一點逍遙自在，就會把江湖瑣事忘的乾乾淨淨。");
     command("say 這東西不會就是傳説中的K粉吧");
     command("fear ");
         return 1;
}
int ask_pearl()
{
     object me;
     me = this_player();
     command("say 本週你已經對着它祈禱(pary)過"+ HIR+chinese_number(me->query("spec/pearl")) +NOR"次了。");
     command("say 我有這樣一串珍珠手鍊呢。");
     command("say 不過我還是覺得自己挺倒黴的，老是碰見些色狼來騷擾我。");
     command("club ");
         return 1;
}
int ask_putao()
{
     object me;
     me = this_player();
     command("say 本週你已經吃過"+ HIR+chinese_number(me->query("spec/putao")) +NOR"串神奇葡萄。");
     command("say 酸酸甜甜就是我。");
     command("sing ");
         return 1;
}

int ask_shuzhi()
{
     object me;
     me = this_player();
     command("say 本週你已經隨手亂丟過"+ HIR+chinese_number(me->query("spec/shuzhi")) +NOR"根小樹枝了。");
     command("say 亂丟垃圾是要罰款的哦！");
     command("say 左圓右方，這麼簡單的事情嘛，我也能畫(hua fangyuan)出來哦！");
     command("draw lao ban ");
         return 1;
}

int ask_suizhi()
{
     object me;
     me = this_player();
     command("say 本週你已經隨手亂丟過"+ HIR+chinese_number(me->query("spec/suizhi")) +NOR"團碎紙片了。");
     command("say 你老是翻來覆去的拿着它看什麼啊(chakan suizhi pian)？");
     command("say 不可能是張教主藏經圖的啦！");
     command("giggle ");
     command("say 張教主早回家種田去了，傳聞多少年都沒出了。");
     command("laugh ");
         return 1;
}
int ask_taijitu()
{
     object me;
     me = this_player();
     command("say 本週你已經盯着這張太極圖研究(yanjiu taiji tu)"+ HIR+chinese_number(me->query("spec/taijitu")) +NOR"次啦。");
     command("say 邋遢道士天天嘟囔着太極深意，可意會不可言傳。");
     command("say 要不你去問問他吧。");
         return 1;
}
int ask_wcard()
{
     object me;
     me = this_player();
     command("say 本週你已經用掉了"+ HIR+chinese_number(me->query("spec/wcard")) +NOR"張貴賓卡。");
     command("say 我愛洗澡，皮膚好好！");
     command("sing ");
     command("say 沒事你秀(show card)啥呢？你以為就你自己辦過了啊？");
     command("wah "+ me->query("id") +" ");

         return 1;
}


int ask_zhanshu()
{
     object me;
     me = this_player();
     command("say 本週你已經拆閲(yuedu)過"+ HIR+chinese_number(me->query("spec/zhanshu")) +NOR"封獨孤戰書。");
     command("say 獨孤九劍，難道天下真的有這麼高明的劍法麼？ ");
     command("think ");
     return 1;
}

int ask_yuji()
{
     object me;
     me = this_player();
     command("say 本週你已經服用過"+ HIR+chinese_number(me->query("spec/yuji")) +NOR"粒玉肌丸。");
     command("say 本週你已經服用過"+ HIR+chinese_number(me->query("spec/yuji1")) +NOR"粒極品玉肌丸。");
     command("say 朵爾膠囊，以內養外，補腎養顏....");
     command("blush ");
         return 1;
}

int ask_shenshu()
{
     object me;
     me = this_player();
     command("say 本週你已經閲讀過"+ HIR+chinese_number(me->query("spec/shenshu")) +NOR"次金庸全集。");
         return 1;
}

int ask_fail()
{
     object me;
     me = this_player();
     command("say " + HIW + "九陰神功上卷" + NOR + "，已經失敗了"+ HIR+chinese_number(me->query("quest/jiuyin1/fail"))+NOR"次。\n");
     command("say " + HIG + "九陰神功下卷" + NOR + "，已經失敗了"+ HIR+chinese_number(me->query("quest/jiuyin2/fail"))+NOR"次。\n");
     command("say " + HIB + "冷泉神功" + NOR + "，已經失敗了"+ HIR+chinese_number(me->query("quest/雪山飛狐/武功/lengquanfail"))+NOR"次。\n");
     command("say " + HIW + "蛤蟆功" + NOR + "，已經失敗了"+ HIR+chinese_number(me->query("quest/hama/fail"))+NOR"次。\n");
     command("say " + HIC + "凌波微步" + NOR + "，已經失敗了"+ HIR+chinese_number(me->query("天龍八部/武功/fail"))+NOR"次。\n");
     command("say " + HIR + "葵花寶典" + NOR + "，已經失敗了"+ HIR+chinese_number(me->query("quest/pixie/fail"))+NOR"次。\n");
     command("say " + HIW + "左右互搏" + NOR + "，已經失敗了"+ HIR+chinese_number(me->query("quest/hubo/fail"))+NOR"次。\n");
     command("say " + HIR + "凝血神爪" + NOR + "，已經失敗了"+ HIR+chinese_number(me->query("quest/ningxue/fail"))+NOR"次。\n");
     command("say " + HIG + "金刀黑劍" + NOR + "，已經失敗了"+ HIR+chinese_number(me->query("quest/jindaoheijian/fail"))+NOR"次。\n");
     command("say " + HIC + "太玄功" + NOR + "，已經失敗了"+ HIR+chinese_number(me->query("quest/taixuan/fail"))+NOR"次。\n");
     command("say " + HIR + "千蜘萬毒手" + NOR + "，已經失敗了"+ HIR+chinese_number(me->query("quest/qianzhu/fail"))+NOR"次。\n");
     command("say " + HIM + "楊家槍" + NOR + "，已經失敗了"+ HIR+chinese_number(me->query("quest/yangjiaqiang/fail"))+NOR"次。\n");
         return 1;
}
