inherit ROOM;

void create()
{
        set("short", "哈薩克群落");
        set("long", @LONG
這兒有一片哈薩克帳蓬。哈薩克人的帳蓬一年四季在草原
上東西南北的遷移。其中一帳蓬前掛著一張大狼皮顯得格外醒
目。一個身材苗條的女孩捧了酒漿出來，很客氣地招呼你。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                    "south" : __DIR__"huijiang5",
        ]));
        set("objects", ([
                __DIR__"npc/aman"  : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}