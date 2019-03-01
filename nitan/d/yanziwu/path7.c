// Room: /d/yanziwu/path7.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "碎石小徑");
        set("long", @LONG
一條小路通往花圃深處。走在小路上，可以聽到近處清溪水響。地
上碎石舖得很是齊整，看來是花了不少功夫了。北邊就是紅霞樓了。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"path6",
                "north"  : __DIR__"hongxia1",
        ]));
        set("coor/x", 1250);
        set("coor/y", -1260);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}