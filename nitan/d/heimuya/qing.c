//ROM dating
inherit ROOM;
void create()
{
        set("short", "青龍堂大廳");
        set("long", @LONG
這是『日月神教』下第三大堂：青龍堂的大廳。一位長者居中，
神情恍惚。
LONG );
        set("exits", ([
            "north" : __DIR__"chlang2",
            "east" : __DIR__"tang",
        ]));
        set("objects",([
            CLASS_D("riyue") + "/jiabu": 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}