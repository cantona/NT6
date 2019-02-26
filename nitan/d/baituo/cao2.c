inherit ROOM;

void create()
{
        set("short", "草叢");
        set("long", @LONG
這裏是亂草叢。北邊是青竹林。其餘三面都是齊腰高的蒿草，常
有蛇出沒。
LONG );
        set("exits", ([
                "west"  : __FILE__,
                "north" : __DIR__"zhulin",
                "east"  : __DIR__"cao1",
                "south" : __DIR__"cao1",
        ]));

        set("objects", ([
                "/clone/beast/qingshe" : random(2),
                "/clone/beast/jinshe"  : random(2),
                "/clone/beast/dushe"   : 1,
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
        set("coor/y", 20030);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}