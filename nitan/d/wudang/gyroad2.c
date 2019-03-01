inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "果園");
        set("long", @LONG
你輕鬆地走進果園。園中落英繽紛，兩邊是桃樹林，盛開著粉紅
的桃花，紅雲一片，望不到邊。中間卻是一株冠蓋數畝的大樹(tree)，
遮住地面好大一片綠蔭。
LONG );
        set("outdoors", "wudang");
        set("item_desc", ([
                "tree" : GRN "\n這是一株人參果樹，據說摘下人參果吃了對"
                         "武功進益很有好處。\n\n" NOR
        ]));
        set("exits", ([
                "west" : __DIR__"gyroad1",
        ]));
        set("guocount",1);
        set("coor/x", -240);
        set("coor/y", -310);
        set("coor/z", 30);
        setup();
}

void init()
{
        add_action("do_zhai", "zhai");
}

int do_zhai(string arg)
{
        object guo, me = this_player();

        if (! arg || arg == "")
                return notify_fail("你想摘什麼？\n");

        if (arg == "guo" || arg == "renshen guo")
        {
                if (uptime() < 1800)
                {
                        message_vision(HIY "$N" HIY "看了看人參果樹，發現"
                                       "樹上的果子都未成熟，不禁失望地嘆了"
                                       "口氣。\n", me);
                        return 1;
                } else
                if (query("guocount") > 0 && random(10) == 1)
                {
                        message_vision(HIC "\n$N" HIC "從人參果樹上摘下一"
                                       "個熟透的" HIM "人參果" HIC "，不禁"
                                       "大喜過望。\n\n" NOR, me);
                        guo = new(__DIR__"obj/renshenguo");
                        guo->move(me, 1);
                        addn("guocount", -1);
                        return 1;
                } else
                {
                        set("guocount", 0);
                        message_vision(HIY "$N" HIY "看了看人參果樹，發現"
                                       "果樹的枝葉上有剛被採摘過的痕跡。\n", me);
                        return 1;            
                }
        }
        return 0;
}