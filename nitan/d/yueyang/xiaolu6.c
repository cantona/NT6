// Room: /d/yueyang/xiaolu6.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "引道");
        set("long", @LONG
你走在君山東麓的湘妃祠引道上。君山，由七十二峯組成，峯峯皆
靈秀，“煙波不動景沉沉，碧色全無翠色深。疑是水仙梳洗處，一螺青
黛鏡中心。”但見野徑葦葉離離、翠竹風響，滿山的茶香。不由得你心
神俱醉，真是神仙洞府。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "enter"     : __DIR__"xiangfeici1",
                "northwest" : __DIR__"xiaolu7",
                "southwest" : __DIR__"erfeimu",
        ]));
        set("coor/x", -1660);
        set("coor/y", 2310);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}