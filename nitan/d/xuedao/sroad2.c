inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
一條山路蜿蜒在山間。向西望去，可以見到大雪山的銀色的雪頂
在熠熠生輝。
LONG );
        set("exits", ([
                "east" : __DIR__"sroad1",
                "west" : __DIR__"sroad3",
        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}