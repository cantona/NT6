// Room: /d/fuzhou/xidajie.c
// may. 12 1998 Java

inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
大街北面，一座結構宏偉的建築前，左右石壇上各插着一根兩丈多
高的旗杆，杆上青旗飄揚。右首旗子用金線繡着一頭張牙舞爪的獅子，
旗風招展，奕奕如生。雄獅上頭有一對黑絲線繡的蝙蝠展翅飛翔。左首
旗子上寫着“福威鏢局”四個黑字，銀鈎鐵劃，剛勁非凡。
LONG );

        set("exits", ([
                "north"   : __DIR__"biaoju",
                "east"    : __DIR__"xidajie1",
                "west"    : __DIR__"xixiaojie",
                "southup" : __DIR__"wushan",
        ]));
        set("objects", ([
                __DIR__"npc/ji" : 1,
                __DIR__"npc/di" : 1,
        ]));
        set("outdoors", "fuzhou");
	set("coor/x", -100);
	set("coor/y", -6180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}