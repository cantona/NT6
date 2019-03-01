// Room: /binghuo/shulin2.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "大樹林");
        set("long", @LONG
這裡綠樹成蔭。奇花異卉，長青闊葉，漫山遍野。在這極北之處，
居然有此林木，看來是拜火山之賜了。偶爾驚起一些叫不出名目的大
鳥小獸，也不避人。
LONG );
        set("outdoors", "binghuo");
        set("exits", ([
                "south"     : __DIR__"shulin1",
                "northeast" : __DIR__"shulin3",
        ]));
        set("objects", ([
                "/d/lingjiu/npc/lu": 1,
        ]));
        setup();
        replace_program(ROOM);
}
