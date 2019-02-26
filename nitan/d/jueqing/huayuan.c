inherit ROOM;

void create()
{
        set("short", "後花園");
        set("long", @LONG
這是絕情谷的後花園，但見園中羣花爭奇鬥豔，偶聞花香
撲鼻，醉人心扉。四周翠木叢生，飛禽追逐嬉戲，別有一番景
致。
LONG);
        set("exits", ([
               "north"   : __DIR__"zizhuxuan",
               "west"    : __DIR__"xiaojing",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}