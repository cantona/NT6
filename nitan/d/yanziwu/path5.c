// Room: /d/yanziwu/path5.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "碎石小徑");
        set("long", @LONG
一條小路通往花圃深處。走在小路上，可以聽到近處清溪水響。地
上碎石舖得很是齊整，看來是花了不少功夫了。南邊就是蔓陀山莊的花
圃了，滿莊滿園的花，都是那邊栽培出來的。西面就是蔓陀山莊的中心
花園了。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"huapu1",
                "east"   : __DIR__"path6",
                "west"   : __DIR__"garden",
        ]));
        set("coor/x", 1240);
        set("coor/y", -1270);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}