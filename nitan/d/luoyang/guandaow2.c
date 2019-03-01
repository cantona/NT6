inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
這是一條寬闊筆直，塵土飛揚的大官道，它連接了東都長安和西都洛
陽。官道很是寬廣，足可容得下十馬並馳。往西直達長安的東門，而東邊
則是洛陽古城。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"guandaow1",
                  "west" : __DIR__"guandaow3",
        ]));

        set("coor/x", -3580);
        set("coor/y", 1090);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}