// Room: /d/mingjiao/gudi2.c
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "昆侖谷底");
        set("long", @LONG
翻過那堵屏風也似的大山壁。眼前依舊茫茫雲海，更無去路，山
石堅硬無比，你看到右邊有一株大鬆樹(tree)，左側山壁黑黝黝似乎
有個小山洞(dong)。
LONG );
        set("outdoors", "mingjiao");
        set("item_desc", ([
                "dong": "一個不知深淺的山洞。\n",
                "tree": "一株挺拔健碩的鬆樹。\n",
        ]));
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
        int n = query("str", me);

        if( !arg || arg != "dong")
        {
                write("你想幹什麼呀?\n");
                return 1;
        }
        message_vision("$N深吸了一口氣，慢慢沿著洞壁往裡爬。\n", me);
        if(n < 20 || wizardp(me))
        {
                message_vision("$N爬進數丈，忽見前面透進光亮，心中大喜，手足兼施，加速前行。\n", me);
                me->move(__DIR__"gudi3");
        }
        else
        {
                message_vision(HIR
                        "$N狂怒之下，勁運雙肩，向前一擠，身子果然前進了尺許，可是再想前行，卻已萬萬不\n", me);
                message_vision(
                        "能，堅硬的石壁壓在他胸口背心，竟然氣也喘不過來。$N窒息難受，只得後退，不料身\n", me);
                message_vision(
                        "子嵌在堅石之中，前進固是不能，後退卻也已不得，這一下$N嚇得魂飛魄散，竭盡生平\n", me);
                message_vision(
                        "之力，雙臂向石上猛推，身子才退了尺許，猛覺得胸口一陣劇痛，竟已軋斷了一根肋骨。\n"NOR, me);
                me->receive_damage("qi",15);
                me->receive_wound("qi",10);
        }
        return 1;
}
int do_climb(string arg)
{
        object me = this_player();
        if( !arg || arg != "tree")
        {
                write("你想幹什麼呀?\n");
                return 1;
        }
        message_vision("$N手攀鬆樹，搖了兩搖，試試是否結實。\n", me);
        message_vision("$N忽然一個失手，向懸崖下直跌下去。\n", me);
        me->move(__DIR__"shanjiao");
        me->receive_damage("qi", 1);
        me->receive_wound("qi", 1);
        me->unconcious();
        return 1;
}