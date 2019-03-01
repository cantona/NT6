inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
這是個長廊，通向東練武場，人來人往的，很是熱鬧。
LONG);
        set("no_fight", 1);
        set("exits", ([
               "east" : __DIR__"guofu_wuchang2",
               "west" : __DIR__"guofu_dayuan",
        ]));
        setup();
        replace_program(ROOM);
}