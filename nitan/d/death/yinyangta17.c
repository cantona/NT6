#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB "陰陽塔" NOR);
        set("long", HIB @LONG
這是地獄中最高的一座塔，高約三百餘尺，共有十八級。相傳塔頂
住有神獸朱雀，這個傳言也不知是真是假。
LONG NOR
        );

        set("exits", ([
                "up"   : __DIR__"yinyangta18",
                "down" : __DIR__"yinyangta16",
        ]));
        
        set("objects",([
                __DIR__"npc/mamian" : 1,
        ]));
        
        set("no_magic", 1);
        setup();
}

int valid_leave(object me, string dir)
{
        int i;
        object ob;
        me = this_player();
        if (dir == "up")
        {
                if (objectp(present("ma mian", environment(me))))
                        return notify_fail(CYN "馬面看了你一眼，喝道：你還不滾"
                                           "回去還陽，來這裏湊什麼熱鬧！\n" NOR);
        }
        return ::valid_leave(me, dir);
}