// Room: /d/xingxiu/tugu.c
// Last Modified by winder on Apr. 25 2001
inherit ROOM;

void create()
{
        set("short", "吐谷渾伏俟城");
        set("long", @LONG
這裏是吐谷渾都城。吐谷渾原為鮮卑的一支，遊牧於北方。後來首
領吐谷渾率所部西遷於此。以吐谷渾為國名。其可汗現正居於伏俟城內。
城內混居了周圍的多個民族，走在大街上看到和聽到的無不透着新奇。
LONG);
        set("outdoors", "xiyu");
        set("exits", ([
                "east"      : __DIR__"shazhou",
                "northwest" : __DIR__"silk5",
                "south"     : __DIR__"nanjiang",
        ]));

        set("objects", ([
                __DIR__"npc/trader" : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -23500);
        set("coor/y", 900);
        set("coor/z", 0);

        setup();
//        replace_program(ROOM);
}

#include "/d/xingxiu/job2.h";
