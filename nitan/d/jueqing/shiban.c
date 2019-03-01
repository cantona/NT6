inherit ROOM;

void create()
{
        set("short", "青石板路");
        set("long", @LONG
四周樹木叢生，花香宜人，偶聞飛鳥齊鳴，石板蜿蜒曲折，
遙見不遠處山陰遮蓋下有座極大石屋。
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "north"   : __DIR__"shanzhuang",
               "south"   : __DIR__"zhulin1",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}