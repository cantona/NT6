inherit ROOM;

void create()
{
        set("short", "雪坑");
        set("long", @LONG
這是大雪山腳下的一個雪坑，坑內四周光線陰暗，什麼都看不清
楚。躲進這裡，你感到暖和了一些。
LONG );
        set("exits", ([
                "northup"   : __DIR__"sroad3",
        ]));
        set("objects", ([
                "/clone/worm/xixuezhu" : 2,
                "/d/xuedao/npc/zhizhu" : 1,
        ]));
        setup();
}
