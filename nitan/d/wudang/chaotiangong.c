inherit ROOM;

void create()
{
        set("short", "朝天宮");
        set("long", @LONG
這裡已近武當絕頂，只見石梯直聳，危蹬高懸，兩旁輔以索鏈、
鐵攔勾連。
LONG );
        set("objects", ([
                CLASS_D("wudang") + "/qingxu": 1,
        ]));

        set("exits", ([
                "northdown" : __DIR__"hutouyan",
                "south" : __DIR__"huixianqiao",
        ]));
        set("outdoors", "wudang");
        set("coor/x", -350);
        set("coor/y", -370);
        set("coor/z", 150);
        setup();
        replace_program(ROOM);
}