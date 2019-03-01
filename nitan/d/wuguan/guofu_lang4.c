inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
這是個長廊，北面是武館內的物品房，要在武館做雜事
的人都得去物品房領工具，南邊是東練武場。
LONG);
        set("no_fight", 1);
        set("exits", ([
               "north" : __DIR__"guofu_wupinfang",
               "south" : __DIR__"guofu_wuchang4",
        ]));
        set("objects", ([
                __DIR__"npc/wusantong" : 1,
        ]));
        setup();
        replace_program(ROOM);
}