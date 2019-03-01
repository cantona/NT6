// Room: /qingcheng/gulongqiao.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "古龍橋");
        set("long", @LONG
你走在古龍橋上。望見巖壁上一個大裂槽。寬二十余丈深，深
達六、七丈，傳說是張天師降魔時以筆劃山而過的仙家痕跡。
LONG );
        set("outdoors","qingcheng");
        set("exits", ([
                "northup"   : __DIR__"zushidian",
                "southdown" : __DIR__"tianshidong",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8100);
        set("coor/y", -900);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}