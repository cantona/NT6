#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "藏經樓");
        set("long", @LONG
這裏是報國寺藏經樓。閣樓上密密麻麻排了好多書架，架上擺滿
了經書。有兩個身穿白衣的小師太正在一角靜靜地讀着經書。
LONG );
        set("objects", ([
                CLASS_D("emei") + "/daoming" : 1,
                __DIR__"obj/fojing1" + random(2) : 1,
                __DIR__"obj/fojing2" + random(2) : 1,
        ]));
        set("exits", ([
                "south" : __DIR__"dxdian",
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        me = this_player();

        if (dir == "south"
           && present("shu", me)
           && objectp(present("dao ming", environment(me))))
                return notify_fail(CYN "道明小師父見你想把經書拿走，上前輕"
                                   "聲説道：本閣經書恕不外借。\n" NOR);

        return ::valid_leave(me, dir);
}