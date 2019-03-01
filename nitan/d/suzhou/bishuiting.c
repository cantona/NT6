// Room: /d/suzhou/bishuiting.c
// Last Modified by winder on Mar. 8 2001

#include <room.h>
#include <ansi.h>
inherit ROOM;
int do_press();
int valid_leave();

void create()
{
        set("short","碧水亭");
        set("short", HIC"碧水亭"NOR);
        set("long", @LONG
這是湖中的一個小亭子，從這望去，可以看到整個湖面的景色，令
人心曠神怡。亭子壁上刻畫著江南水鄉的宜人風景，令人無限遐想。亭
上有一根樑(liang)。
LONG );
        set("exits",([
                "south" : __DIR__"huzhongdao",
        ]));
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("item_desc", ([
                "liang" : "房樑是上好的楠木做的，上面還有十分古怪的字畫。\n",
        ]));
        set("coor/x", 800);
        set("coor/y", -1200);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me;
        me = this_player();
        if (arg !="liang") return notify_fail("你要到那去？\n");
        if (me->query_dex()<20) 
                write("你試圖跳上房樑，無奈身法不夠敏捷，只好做罷。\n");
        else
        {
                write("你縱身躍上了房樑。\n");
                message("vision", me->name() + "一縱身躍上了房樑。\n", environment(me), ({me}) );
                me->move(__DIR__"liang");
                message("vision", me->name() + "從下面躍了上來。\n", environment(me), ({me}) );
                return 1;
        }
}
