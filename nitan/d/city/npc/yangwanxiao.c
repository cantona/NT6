// yangwanxiao.c

inherit NPC;
#include <ansi.h>

string ask_room1();

void create()
{
        set_name( YEL "楊萬蕭" NOR, ({"yang wanxiao", "yang", "wanxiao"}) );
        set( "age", 48 );
        set( "int", 25 );
        set( "con", 26 );
        set( "per", 22 );
        set( "attribute", "peaceful" );

        set( "long", @LONG
楊家是揚州名門望族，楊萬蕭是楊府現今的主人，五柳長鬚，
看上去很是儒雅，據説楊萬蕭詩文做的極好，和現任知州是
好友，經常是做詩相和。
LONG);
        set( "combat_exp", 10000 );
        set_skill( "literate", 100);

        set("chat_chance", 30);
        set("chat_msg", ({
                "楊萬蕭只是衝從你微微一笑，卻什麼也不説。\n",
        }) );
        set( "inquiry", ([
                "小玲瓏山館" : (: ask_room1 :),
                "楊府" : (: ask_room1 :),
                "揚州" : "天下三分明月夜，無奈二分在揚州，哈哈。。。\n",
        ]) );
        setup();
        carry_object("/clone/cloth/male-cloth")->wear();
        carry_object(__DIR__"obj/chuan")->wear();
}


string ask_room1()
{
        return "那是祖上留下的，不過卻也是有些特色了。\n";
}
