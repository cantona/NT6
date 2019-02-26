// npc: /d/city/npc/shenwanfu.c
// Last Modified by Sir 9/15/2001
//增加燙布任務

#include <ansi.h>
#include <command.h>

#define MAX_EXP 5000
#define MIN_EXP 1000
inherit NPC;
inherit F_DEALER;
int do_gongzuo();
void create()
{
        set_name( YEL "沈萬福" NOR, ({ "shen wanfu","shen","wanfu" }) );
        set("gender", "男性" );
        set("title", "沈家白衣鋪老闆");
        set("age", 45);
        set("long", "沈萬福是一個白胖子，臉上總是笑呵呵的，象一尊彌勒佛。看他的樣子
不象是個買賣人，然而如果你仔細看看他那雙眯縫的笑眼，就會發現裏
面同樣閃動着一絲狡黠的光芒。他就是這家白衣鋪的老闆。\n");
        set("chat_chance", 50);
        set("chat_msg", ({
                "沈萬福道：這裏就是揚州城啦，您家沒有來過麼？\n",
                "沈萬福道：啊，這位客官，聽您的口音是……北方……南方……西邊……到底是哪兒的人啊？\n",
                "沈萬福道：客官，咱這白衣，哎，沒的説，您找不到比這更好的啦，來一件吧，啊？\n",
                "沈萬福道：客官，您瞧瞧，這件白衣您穿上多精神哪！人靠衣服馬靠鞍嘛，您説是不是這個理兒？\n",
        }));
        set("inquiry", ([
                "白衣" : "要買白衣，您到我這兒就找對地方了，絕對沒錯！\n",
                "here" : "嚇，這兒可不就是揚州城嘛。\n",
                "工作" : (: do_gongzuo :),
                "job"  : (: do_gongzuo :),
                "work" : (: do_gongzuo :),
        ]) );
        set("attitude", "friendly");
        set("vendor_goods", ({
                CLOTH_DIR+"cloth/baiduanshan",
                CLOTH_DIR+"cloth/baizhusipao",
                CLOTH_DIR+"cloth/commcloth",
                CLOTH_DIR+"cloth/hulannaao",
                CLOTH_DIR+"cloth/mabukuanshan",
                CLOTH_DIR+"cloth/shabuzhizhui",
                CLOTH_DIR+"cloth/zhifengkuanshan",
                CLOTH_DIR+"cloth/nenlvchoushan", 
                CLOTH_DIR+"cloth/danhuangshayi",
                CLOTH_DIR+"cloth/yinhongshanzi",
                CLOTH_DIR+"cloth/sahuaao",
        }) );

        set("attitude", "friendly");
        set("rank_info/respect", "老哥");
        set("rank_info/rude","老王八蛋");
        set("combat_exp",100);
        set_skill("unarmed", 5);
        setup();
        carry_object( "/clone/cloth/male-cloth")->wear();
}

int do_gongzuo()
{
        object me;        
        me = this_player(); 
        
        if( query("combat_exp", me)<MIN_EXP )
        {
                command("say 這裏都是精細活，你現在還幹不了。\n");
                return 1;
        }
        
        if( query("combat_exp", me) >= MAX_EXP )
        {
                command("say 這種小事不敢勞您大駕。\n");
                return 1;
        }
        if( query_temp("gongzuo/yunbu", me)>0 )
        {
                tell_object(me,"快去把布匹熨好後交給我吧。\n");
                return 1;
        }
        message_vision(CYN"沈萬福對$N説道：現在熨好的布匹不夠用了，你就到後面的庫房裏去熨些布來。\n"NOR,me); 
        set_temp("gongzuo/yunbu", 1, me);
        return 1;
}
int accept_object(object me, object ob)
{
        object ob1;
        int add_exp,add_pot,add_score;
        if( strsrch(query("name", ob),"熨好的布")<0 )
        {
                command("say 你別來蒙我啦，這是熨好的布嗎？\n");
        }
        else if( query_temp("gongzuo/yunbu", me)<1 )
        {
                command("say 我沒有叫你幫我熨布呀！\n");
        }
        else if( query_temp("gongzuo/yunbuok", me)<1 )
        {
                command("say 這不是你熨的布呀！\n");
        }
        else
        {
                message_vision(CYN"沈萬福對$N説道：辛苦了，這是你的工錢。\n"NOR,me);
                message_vision(CYN"沈萬福遞給$N一些銀子。\n"NOR,me);

                delete_temp("gongzuo/yunbu", me);
                delete_temp("gongzuo/yunbuok", me);

                add_exp=30+random(20);
                add_pot=15+random(10);
                add_score=10+random(5);
                addn("combat_exp", add_exp, me);
                addn("potential", add_pot, me);
                addn("score", add_score, me);
                ob1 = new("/clone/money/silver");
                ob1->set_amount(add_score);
                ob1->move(me);        
                tell_object(me,HIW"你得到了:"
                        + chinese_number(add_exp) + "點實戰經驗，"
                        + chinese_number(add_pot) + "點潛能，"
                        + chinese_number(add_score) + "點江湖閲歷。\n"NOR);                                
                call_out("destroying", 1, this_object(), ob);
                return 1;
        }
        return 0;
}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

void init()
{
        object ob = this_player();
        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        message_vision("沈老闆笑呵呵的説道：“客官，您瞧瞧咱家的白衣怎麼樣？”\n",ob);
        return;
}