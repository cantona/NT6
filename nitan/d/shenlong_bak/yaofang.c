// /d/shenlong/yaofang 藥房
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "藥房");
        set("long", @LONG
這是神龍島的藥房，靠牆放了許多櫃子，抽屜中放滿了許多中草藥，
陸大夫常在這兒給島上的眾人抓藥、診治。不過陸大夫現在遇到點頭疼
的事，如果你想要一些雄黃以避免島上的毒蛇侵擾，只好去他的小屋了。
LONG
        );
        set("exits", ([
                "north" : __DIR__"zhulin1",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
