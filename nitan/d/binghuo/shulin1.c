// Room: /binghuo/shulin1.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "大樹林");
        set("long", @LONG
這裏綠樹成蔭。奇花異卉，長青闊葉，漫山遍野。在這極北之處，
居然有此林木，看來是拜火山之賜了。偶爾驚起一些叫不出名目的大
鳥小獸，也不避人。
LONG );
        set("outdoors", "binghuo");
        set("no_clean_up", 0);
        set("exits", ([
                "east"   : __DIR__"haitan",
                "north"  : __DIR__"shulin2",
        ]));
        setup();
        replace_program(ROOM);
}
