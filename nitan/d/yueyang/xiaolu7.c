// Room: /d/yueyang/xiaolu7.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "青石山道");
        set("long", @LONG
你正走在君山東麓通往秋月嶺的青石山道上。君山，由七十二峰組
成，峰峰皆靈秀，“煙波不動景沉沉，碧色全無翠色深。疑是水仙梳洗
處，一螺青黛鏡中心。”但見野徑葦葉離離、翠竹風響，滿山的茶香。
不由得你心神俱醉，真是神仙洞府。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "north"     : __DIR__"qiuyueqiao",
                "southeast" : __DIR__"xiaolu6",
        ]));
        set("coor/x", -1670);
        set("coor/y", 2320);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}