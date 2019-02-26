// chuchang shi

inherit ROOM;

void create()
{
        set("short", "儲藏室");
        set("long", @LONG
這裏是丐幫的儲藏室，你可以看見一個個鎖着的箱子。周圍還懸
掛着一些武器和裝備。這時有一位丐幫五袋弟子正閉目養神，看守着
這裏。
LONG );
        set("exits", ([
                "west" : __DIR__"mishi",
                "east" : __DIR__"undertre",
        ]));
        set("objects", ([
                "/d/gaibang/npc/5dai" : 1,
                "/d/gaibang/npc/obj/staff" : 3,
                "/clone/weapon/gangdao" : 2,
        ]));
        set("no_clean_up", 0);
        set("coor/x", 10);
        set("coor/y", -10);
        set("coor/z", -30);
        setup();
        replace_program(ROOM);
}