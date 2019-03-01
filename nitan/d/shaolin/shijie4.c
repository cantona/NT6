// Room: /d/shaolin/shijie4.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
水聲越來越大，山間充滿了濃濃的水氣。石階上，斷裂的山隙中，
都流出一道道細細的泉水，匯成一股澄碧的小溪，向山下蜿蜒流去。
周圍綠意盪漾，鳥語鸚聲，如置身仙境。
LONG );
        set("exits", ([
                "northup" : __DIR__"shijie5",
                "eastdown" : __DIR__"shijie3",
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
