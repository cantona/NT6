#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", NOR + WHT "【奈河橋】" NOR);
        set("long", NOR + WHT @LONG

                    奈         河         橋

    這裏就是著名的陰間通道「奈河橋」，你走在這長長的石制拱橋上
面，許多亡魂正哭哭啼啼地從你身旁擦身而過，橋的另一端站着一個牛
頭人身的守衞，仔細的查看着過往的亡魂。


LONG NOR );
        set("exits", ([
                // "north" : __DIR__"hell1",
                "north" : __DIR__"youmingjie",
                "south" : __DIR__"qiao1",
        ]));
        set("objects", ([
                __DIR__"npc/niutou":1,
                __DIR__"npc/ghost":1,
        ]));
        set("item_desc", ([
                "north": HIW "\n奈河橋的另一端被煙霧所籠罩，彷彿沒有"
                         "盡頭，你什麼都看不清。\n" NOR
        ]));

        set("no_sleep_room", 1);

        set("no_magic", 1);
        setup();
}
int valid_leave(object me, string dir)
{
        int i;
        object ob;
        me = this_player();
        if (dir == "north")
        {
                if (objectp(present("niu tou", environment(me))) &&
                    !query("hell_quest/鎖陽丹", me) )
                        return notify_fail(CYN "牛頭看了你一眼，喝道：你還不滾"
                                           "回去還陽，來這裏湊什麼熱鬧！\n" NOR);
        }
        return ::valid_leave(me, dir);
}