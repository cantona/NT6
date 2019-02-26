// Room: /binghuo/yuanye2.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "原野");
        set("long", @LONG
這裏是一片空曠的原野。你走得口乾舌燥，遍身大汗，但見身旁
已無一株樹木花草，只餘光禿禿、黃焦焦的巖石。火山口在北面還遠
着呢。
LONG );
        set("outdoors", "binghuo");
        set("exits", ([
                "south"  : __DIR__"yuanye2",
        ]));
        set("objects", ([
                "/d/emei/obj/liuhuang" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
