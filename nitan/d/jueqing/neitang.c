inherit ROOM;

void create()
{
        set("short", "內堂");
        set("long", @LONG
絕情谷內堂較大廳要寬敞一些，四周陳設甚多，但四周仍
擺放着幾盆花木，清香四溢。可見谷主是個愛花之人。
LONG);
        set("exits", ([
               "south"  : __DIR__"dating",
               "north"  : __DIR__"changlang2",
               "west"   : __DIR__"chufang",
               "east"   : __DIR__"pianting",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
