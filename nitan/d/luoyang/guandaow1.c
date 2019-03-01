inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
這是一條寬闊筆直，塵土飛揚的大官道，它連接了東都長安和西都洛
陽。官道很是寬廣，足可容得下十馬並馳。往西直達長安的東門，而往東
邊不遠便是東都洛陽古城的西城邊了。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "eastup" : __DIR__"wbridge",
                  //"west" : __DIR__"guandaow2",
                  "west" : "/d/changan/road1",
        ]));

	set("coor/x", -7070);
	set("coor/y", 2180);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}