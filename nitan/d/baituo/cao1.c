inherit ROOM;

void create()
{
        set("short", "草叢");
        set("long", @LONG
這裏是亂草叢。東邊是扇拱月形小敞門。其餘三面都是齊腰高的
蒿草，常有蛇出沒。
LONG );
        set("exits", ([
                "west" : __FILE__,
                "north" : __DIR__"cao2",
                "east" : __DIR__"ximen",
                "south" : __FILE__,
        ]));
        set("objects", ([
                "/clone/beast/jinshe" : random(2),
        ]));
        set("quarrys", ([
                "caihuashe"  : 100000,
                "dushe"      : 50000,
                "jinshe"     : 40000,
                "qingshe"    : 40000,
                "yanjingshe" : 5000,
                "mangshe"    : 3000,
        ]));
        set("outdoors", "baituo");
        set("coor/x", -50000);
        set("coor/y", 20020);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}
