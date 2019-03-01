inherit ROOM;

void create()
{
        set("short", "絕情谷山腳");
        set("long", @LONG
這裡是絕情谷山腳下，但見四周溪流飛瀑，樹木高聳，兩
邊山峰壁立，景色極盡清幽。 
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "northup"   : __DIR__"shulin1",
               "southdown" : "/d/xiangyang/caodi1",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}