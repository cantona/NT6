inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @LONG
這裡是後院，北面是三清殿，南面是一個圓形的門洞，有條小路
通往後山。
LONG );
        set("exits", ([
                "south" : __DIR__"xiaolu1",
                "north" : __DIR__"sanqingdian",
        ]));
        set("objects", ([
                CLASS_D("wudang") + "/yu" : 1
        ]));
        set("coor/x", -370);
        set("coor/y", -310);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}