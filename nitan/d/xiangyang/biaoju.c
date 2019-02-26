// Room: /d/xiangyang/biaoju.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "福威鏢局");
        set("long", @LONG
你來到一座結構宏偉的建築前，左右石壇上各插着一根兩丈多高
的旗杆，杆上青旗飄揚。右首旗子用金線繡着一頭張牙舞爪的獅子，
獅子上頭有一隻蝙蝠飛翔。左首旗子上寫着『福威鏢局襄陽分號』八
個黑字，銀鈎鐵劃，剛勁非凡。入口排着兩條長凳，幾名鏢頭坐着把
守。
LONG );
        set("exits", ([
                "west" : __DIR__"eastroad1",
        ]));
        set("objects", ([
                __DIR__"npc/biaotou" : 2,
        ]));
        set("coor/x", -7790);
	set("coor/y", -760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}