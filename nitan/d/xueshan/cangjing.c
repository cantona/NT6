inherit ROOM;

void create()
{
        set("short", "藏經閣");
        set("long", @LONG
這裡是雪山寺的藏經之處。書架上林林總總都是梵文典籍。可是
你一個字也看不懂。
LONG );
        set("exits", ([
                "south" : __DIR__"dating",
        ]));
        setup();
        replace_program(ROOM);
}