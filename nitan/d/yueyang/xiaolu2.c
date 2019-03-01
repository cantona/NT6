// Room: /d/yueyang/xiaolu2.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
你走在君山西麓的湖邊小路上。君山，由七十二峰組成，峰峰皆靈
秀，“煙波不動景沉沉，碧色全無翠色深。疑是水仙梳洗處，一螺青黛
鏡中心。”但見野徑葦葉離離、翠竹風響，滿山的茶香。不由得你心神
俱醉，真是神仙洞府。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "northeast" : __DIR__"longkou",
                "west"      : __DIR__"shejiaotai",
        ]));
        set("coor/x", -1730);
        set("coor/y", 2280);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}