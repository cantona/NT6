inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這是古村的練武場，一個露天的場地裡擺滿了練武用的沙袋和
木人，幾個年輕小伙正在一位老者的知道下呼呼生風地揮動著拳腳。
LONG);
        set("exits", ([
                "north" : __DIR__"bingqishi",
                "south" : __DIR__"xiuxishi",
                "west" : __DIR__"road2",
                "east" : __DIR__"houcun-road",
        ]));

        set("objects", ([
                __DIR__"npc/wubo" : 1,
        ]));
        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("no_fight", 1);
        set("no_fight", 1);
        setup();

        replace_program(ROOM);
}
