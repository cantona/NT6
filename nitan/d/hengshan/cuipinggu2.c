// Room: /d/hengshan/cuipinggu2.c
// Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
        set("short", "翠屏谷");
        set("long", @LONG
這裏峽谷幽深，石壁陡直，兩崖壁立，一澗中流。就在這地勢絕險
的恆山山谷中，卻有數十殿堂懸掛在翠屏山腰。它們上載危巖，下臨深
谷，錯落有致，如玉宇瓊樓自空中冉冉降落。那就是懸空寺了。
LONG
        );
        set("exits", ([
                "up"         : __DIR__"cuiping1",
                "northwest"  : __DIR__"cuipinggu1",
        ]));

        set("outdoors", "hengshan");
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 3180);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
