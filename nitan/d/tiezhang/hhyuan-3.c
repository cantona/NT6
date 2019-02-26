#include <ansi.h>

inherit ROOM;
string look_pubu();

void create()
{
    set("short", YEL"假山"NOR);
        set("long", @LONG
你面前矗立着一座巨大的假山，一道瀑布從假山邊瀉將下來，飛注入
前面的一座大池塘中，池塘底下想是另有瀉水通道，是以塘水卻不見滿溢。
鐵掌幫為建這個花園，也不知花費了多少人力和物力。
LONG    );
        set("exits", ([
                "east" : __DIR__"hhyuan-1",
        ]));

        set("item_desc", ([
//                "pubu" : (: look_pubu :),
        ]));

        set("no_clean_up", 0);
        set("outdoors", "tiezhang");

        setup();
}

string look_pubu()
{
        return @DESC
這是一股奔騰不息的瀑布，瀑布的後面似乎隱約有個小門，你似乎可以穿(cross)過去。
DESC ;
}

void init()
{
//        add_action("do_cross", "cross");
}

int do_cross(string arg)
{
        object me;
        me = this_player();

        if (arg != "瀑布" || arg != "pubu") 
                return notify_fail("你要往哪兒穿？\n");
        {
                write(HIY "你縱身一閃，向瀑布裏穿去。\n" NOR);
                message("vision", HIY + me->name() + HIY "身行一閃突然不見了。\n" NOR, environment(me), ({me}) );
                me->move(__DIR__"mishi");
                message("vision", HIW + me->name() + HIW "全身濕淋淋地從瀑布裏穿了進來。\n" NOR, environment(me), ({me}) );
        }
        return 1;
}