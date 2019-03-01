// Room: /d/xiakedao/xkroad4.c
// Modified by Java on Feb.14.1998
inherit ROOM;

void create()
{
        set("short", "南海漁村");
        set("long", @LONG
這是南海沿岸的偏僻小村，稀稀落落的幾戶人家。空地上晾著幾
頂漁網。南面就是波濤浩淼的南海了。向西走好象還有個漁港。東面
是小村的沙灘曬網場。
LONG );
        set("outdoors", "nanhai");
        set("exits", ([
                "north"   : __DIR__"xkroad3",
                "east"    : __DIR__"xkroad5",
                "west"    : __DIR__"haigang",
                "south"   : __DIR__"haibin",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("resource/quarry", ([
                "/clone/quarry/gui" :  50,
                "/clone/quarry/eyu" :  10,
                "/clone/quarry/haibei" :  10,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -1400);
        set("coor/y", -9000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}