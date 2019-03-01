inherit ROOM;

void create()
{
        set("short", "密林");
        set("long", @LONG
這是黑森森的一片密林，楠木參天，濃陰蔽日。這裡東下二裡是
報國寺，西邊林間隱藏著一座廟宇。
LONG );
        set("exits", ([
                "north" : __DIR__"bgs",
                "west"  : __DIR__"fhs",
        ]));
        set("outdoors", "emei");
        set("no_clean_up", 0);
        set("coor/x", -370);
        set("coor/y", -230);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}