// Room: /d/kunlun/dashibi.c
// Last Modified by winder on Jun. 29 2001

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIW"大平台"NOR);
        set("long", @LONG
前面是一堵屏風也似的大山壁。眼前茫茫雲海，更無去路，你竟是
置身在一個三面皆空的極高平台上。那平台倒有十余丈方圓，可是半天
臨空，上既不得，下又不能，當真是死路一條。這大平台上白皚皚的都
是冰雪，既無樹林，更無野獸。唯有平台下有一株鬆樹(tree)。
    你向前滑出一步，但見左側山壁黑黝黝的似乎有個洞穴，山壁側黑
黝黝似乎有個小山洞(dong)。
LONG );
        set("exits",([
                "west" : __DIR__"xsxiepo2",
        ]));
        set("item_desc", ([
                "tree": "一株挺拔健碩的鬆樹。\n",
                "dong": "一個不知深淺的山洞。\n",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "hongmei");
        set("coor/x", -100000);
        set("coor/y", 20010);
        set("coor/z", 40);
        setup();
}
void init()
{
        add_action("do_enter","enter");
        add_action("do_climb","climb");
}
int do_enter(string arg)
{
        object me = this_player();
        int n=query("str", me);
        if( !arg || arg != "dong")
        {
                write("你想幹什麼呀?\n");
                return 1;
        }
        message_vision("$N深吸了一口氣，慢慢沿著洞壁往裡爬。\n", me);
        if(n < 20 || wizardp(me))
        {
                message_vision("$N爬進數丈，忽見前面透進光亮，心中大喜，手足兼施，加速前行。\n", me);
                me->move(__DIR__"cuigu");
        }
        else
        {
                message_vision( HIR"$N狂怒之下，勁運雙肩，向前一擠，身子果然前進了尺許，可是再想前行，卻已萬萬不\n能，堅硬的石壁壓在他胸口背心，竟然氣也喘不過來。$N窒息難受，只得後退，不料身\n子嵌在堅石之中，前進固是不能，後退卻也已不得，這一下$N嚇得魂飛魄散，竭盡生平\n之力，雙臂向石上猛推，身子才退了尺許，猛覺得胸口一陣劇痛，竟已軋斷了一根肋骨。\n"NOR, me);
                me->receive_damage("qi", 45);
                me->receive_wound("qi", 40);
        }
        return 1;
}
int do_climb(string arg)
{
        object me = this_player();
        if( !arg || arg != "tree")
        {
                write("你想幹什麼呀？\n");
                return 1;
        }
        message_vision("$N手攀鬆樹，搖了兩搖，試試是否結實。\n", me);
        message_vision("$N忽然一個失手，向懸崖下直跌下去。\n", me);
        me->move(__DIR__"xuedi");
        me->receive_damage("qi",100 - me->query_dex());
        me->receive_wound("qi",100 - me->query_dex());
        me->unconcious();
        return 1;
}
