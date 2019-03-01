// This program is a part of NT MudLIB

#include <ansi.h>
#define GIFT_NAME "天賦分配工具"
inherit ITEM;

int do_fen(string arg);

void create()
{
        set_name(HIR + GIFT_NAME + NOR, ({"gift allocate"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", @LONG
可以把mygift獲得的先天天賦分（fen）到你想要的先天屬性上
格式為 fen 悟性 1 這種格式。
LONG );
                set("value", 0);
                /*
                set("no_give", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_put", 1);
                set("no_sell", 1);
                set("no_drop", 1);
                */
        }
        setup();
}

void init()
{
        object me = this_player();

        if (me == environment())
        {
                add_action("do_fen", "fen");
        }
}

int do_fen(string arg)
{
        string htsx;
        int jnd;

        object me = this_player();

        if (! arg || sscanf(arg, "%s %d", htsx, jnd) != 2)
                return notify_fail("指令格式：fen <先天屬性> <點數>\n");

        if( query("tianfu", me)<1 )
                return notify_fail("你目前沒有剩下任何的先天天賦點數可用來分配！\n");

        if (htsx != "膂力" && htsx != "悟性" && htsx != "根骨" && htsx != "身法"
                && htsx != "str" && htsx != "int" && htsx != "con" && htsx != "dex")
                return notify_fail("你只可以將先天天賦點數分配到膂力、悟性、根骨和身法這四種天賦屬性上！\n");

        if (jnd < 1) return notify_fail("先天天賦點數的分配每次最少要求是１點。\n");

        if( jnd>query("tianfu", me) )
                return notify_fail("你沒有那麼多的先天天賦點數！\n");

        switch (htsx)
        {
        case "膂力":
        case "str":
                addn("str", jnd, me);
                tell_object(me, HIY "冥冥中，你似乎感覺有一道光芒射入你的體內！\n" NOR);
                tell_object(me, HIG "你的「" + HIR + "先天膂力" + NOR + HIG "」提升了 " + HIR + chinese_number(jnd) + NOR + HIG + " 點！\n" NOR);
                break;
        case "悟性":
        case "int":
                addn("int", jnd, me);
                tell_object(me, HIY "冥冥中，你似乎感覺有一道光芒射入你的體內！\n" NOR);
                tell_object(me, HIG "你的「" + HIR + "先天悟性" + NOR + HIG "」提升了 " + HIR + chinese_number(jnd) + NOR + HIG + " 點！\n" NOR);
                break;
        case "根骨":
        case "con":
                addn("con", jnd, me);
                tell_object(me, HIY "冥冥中，你似乎感覺有一道光芒射入你的體內！\n" NOR);
                tell_object(me, HIG "你的「" + HIR + "先天根骨" + NOR + HIG "」提升了 " + HIR + chinese_number(jnd) + NOR + HIG + " 點！\n" NOR);
                break;
        case "身法":
        case "dex":
                addn("dex", jnd, me);
                tell_object(me, HIY "冥冥中，你似乎感覺有一道光芒射入你的體內！\n" NOR);
                tell_object(me, HIG "你的「" + HIR + "先天身法" + NOR + HIG "」提升了 " + HIR + chinese_number(jnd) + NOR + HIG + " 點！\n" NOR);
                break;
        default:
                return notify_fail("指令格式：fen <先天屬性> <點數>\n");
                break;
        }
        addn("tianfu", -jnd, me);

        if( query("tianfu", me)<1 )
        {
                delete("tianfu", me);
                destruct(this_object());
        }

        if( query("tianfu", me)>0 )
                tell_object(me,HIG"你目前還有"+chinese_number(query("tianfu", me))+"點先天天賦沒有分配！\n\n"NOR);
        return 1;
}

void owner_is_killed() { destruct(this_object()); }

