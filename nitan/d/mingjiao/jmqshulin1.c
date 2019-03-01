//JMQSHULIN1.C

inherit ROOM;

void create()
{
        set("short", "巨木旗樹林");
        set("long", @LONG
你眼前驟然一暗，朦朧中，只見左右前後，到處都是舖天蓋地的
不知名的巨樹，好象鬆柏，又似冷杉，簇在一起，密實的枝葉象一蓬
蓬巨傘恆伸向天空，遮天蔽日。你似乎迷失了方向，象沒頭蒼蠅般到
處亂闖。
LONG );
        set("exits", ([
                "east" : __DIR__"jmqshulin1",
                "west" : __DIR__"jmqshulin1",
                "north" : __DIR__"jmqshulin2",
                "south" : __DIR__"jmqshulin1",
                "out" : __DIR__"jmqmen",
        ]));
        set("objects", ([
                __DIR__"obj/pine" : random(5),
        ]));
        set("outdoors", "mingjiao");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}