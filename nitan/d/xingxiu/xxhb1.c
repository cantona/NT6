// Room: /d/xingxiu/xxhb1.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "星宿海");
        set("long", @LONG
這兒便是星宿海的盡頭了。舉目遙望, 周圍是無際的湖泊和沼澤。
雖是荒蕪, 然陰暗潮濕, 毒蟲繁殖甚富。星宿弟子常來此捕捉毒蟲,以
備練毒之用。
LONG );
        set("objects", ([
                __DIR__"npc/gushou"  : 1,
        ]) );
        set("exits", ([
             "southwest" : __DIR__"riyuedong1",
             "northwest" : __DIR__"xxhb3",
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "xingxiu");
        set("coor/x", -49990);
        set("coor/y", 20400);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}