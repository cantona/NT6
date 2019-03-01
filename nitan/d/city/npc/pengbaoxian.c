// npc: /d/city/npc/libailv.c
// Last Modified by Winder on Jul. 15 2000

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name( YEL "彭寶現" NOR, ({ "peng baoxian","peng","baoxian" }) );
        set("gender", "男性" );
        set("title", "彭記鮮果店老板");
        set("age", 49);
        set("attitude", "friendly");
        set("rank_info/respect", "老哥");
        set("rank_info/rude","老王八蛋");
        set("long", @LONG
彭老板的這家彭記鮮果店在揚州城也是頗有名氣，來採買果品的顧客很
多，以致于人手總是很緊張，這不，連老板都親自上陣了。老彭一邊給
一個顧客算帳，一邊回答另外一個顧客的問訊，還不時回頭對伙計吩咐
些什麼。
LONG);
        set("chat_chance", 30);
        set("chat_msg", ({
                "彭老板道：怎麼樣？客官，不來二斤桃子嘗嘗麼？\n",
                "彭老板道：來啊客官，這西瓜不甜不要錢！\n",
                "彭老板道：您等等，我這兒忙完了就過來。\n",
                "彭老板：瞧一瞧罷，客官，連知府老爺家的果品都是小店供應的。\n",
        }));
        set("inquiry", ([
                "鮮果" : "啊，是啊是啊，小店各種鮮果應有盡有，看看吧！",
                "here" : "咦！您家看了，「彭記鮮果舖」這大招牌不是明擺著的麼？",
        ]) );
        set("vendor_goods", ({
                FRUIT_DIR+"banana",
                FRUIT_DIR+"banli",
                FRUIT_DIR+"boluo",
                FRUIT_DIR+"caomei",
                FRUIT_DIR+"foshou",
                FRUIT_DIR+"ganzhe",
                FRUIT_DIR+"guiyuan",
                FRUIT_DIR+"hamigua",
                FRUIT_DIR+"hetao",
                FRUIT_DIR+"hongzao",
                FRUIT_DIR+"juzi",
                FRUIT_DIR+"lemon",
                FRUIT_DIR+"laiyangli",
                FRUIT_DIR+"lizhi",
                FRUIT_DIR+"lizi",
                FRUIT_DIR+"mangguo",
                FRUIT_DIR+"pipa",
                FRUIT_DIR+"putao",
                FRUIT_DIR+"shiliu",
                FRUIT_DIR+"shizi",
                FRUIT_DIR+"taozi",
                FRUIT_DIR+"xianggua",
                FRUIT_DIR+"xigua",
                FRUIT_DIR+"xingzi",
                FRUIT_DIR+"yali",
                FRUIT_DIR+"yangmei",
                FRUIT_DIR+"yingtao",
        }) );
        set("combat_exp", 10000);
        set_skill("unarmed", 22);
        setup();
        carry_object("/clone/cloth/male-cloth")->wear();
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
        message_vision("彭老板大聲吆喝道：“時新鮮果，樣樣都有，價錢公道，童叟無欺！”\n",ob);
        return;
}