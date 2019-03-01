// mtroad.c  山路

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條山路，兩旁是茂盛的森林，有一個女孩在這眼望南邊
發呆，南邊就是摩天崖了，一股陰森恐怖的氣氛隨之而來，你不禁
告訴自己，還是快走吧。
LONG );
        set("outdoors", "motianya");
        set("exits", ([
            "south" : __DIR__"mtyadi",
            "east"  : __DIR__"mtroad1",
        ]));
        set("objects",([
            __DIR__"npc/dingdang" : 1,
        ]));
        set("coor/x", -2100);
        set("coor/y", -1600);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}