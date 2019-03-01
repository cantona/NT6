// Room: /yangzhou/pingtai5.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","平台");
        set("long",@LONG
熙春台前平台，臨水二層，白石為砌，圍以雕欄，再現昔日“橫可
躍馬，縱可方軌”的風貌。右通重檐亭，左達十字閣。樓台亭閣之間，
列置湖石花台，種植“金玉滿堂春富貴”的桂、玉蘭、牡丹，更顯得莊
重富麗。露台左側設詩碑一座：“青山隱隱水迢迢，秋盡江南草未凋，
二十四橋明月夜，玉人何處教吹簫”。
LONG );
        set("outdoors", "shouxihu");
        set("objects", ([
                "/d/village/npc/kid" : 1,
        ]));
        set("exits", ([
                "north"  : __DIR__"shizige",
                "south"  : __DIR__"chongyanting",
                "westup" : __DIR__"xichuntai",
                "east"   : __DIR__"ershisiqiao",
        ]));
        set("coor/x", -50);
        set("coor/y", 100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}