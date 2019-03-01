// shanlu.c 山路
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
從漢中西門出來，路勢變急了，這是一條用石塊舖成的山路。路
兩旁光禿禿的，沒有什麼樹木，全是一塊塊的大石頭。這條路好象通
往前面的終南山上。北面有一個小村莊，村中正升起冉冉的炊煙。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "eastup"    : "/d/quanzhen/shanlu1",
                "northup"   : __DIR__"xiaocun",
                "southwest" : __DIR__"ximen",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -12260);
	set("coor/y", 820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}