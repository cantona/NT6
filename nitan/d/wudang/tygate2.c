#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "桃園木門");
        set("long", @LONG
你走在一條通往桃樹林深處的小道上，四周非常安靜，景色怡人。
前面有個桃木門(gate)。
LONG );
        set("outdoors", "wudang");
        set("item_desc",([
                "gate" : WHT "\n\n"
                          "\t※※※※※※※※※※※※※※※\n"
                          "\t※※※※※※※※※※※※※※※\n"
                          "\t※※※　　　　　　　　　※※※\n"
                          "\t※※※　" HIM "去年今日此門中" NOR + WHT "　※※※\n"
                          "\t※※※　　　　　　　　　※※※\n"
                          "\t※※※　" HIM "人面桃花相映紅" NOR + WHT "　※※※\n"
                          "\t※※※　　　　　　　　　※※※\n"
                          "\t※※※　" HIM "人面不知何處去" NOR + WHT "　※※※\n"
                          "\t※※※　　　　　　　　　※※※\n"
                          "\t※※※　" HIM "桃花依舊笑春風" NOR + WHT "　※※※\n"
                          "\t※※※　　　　　　　　　※※※\n"
                          "\t※※※※※※※※※※※※※※※\n"
                          "\t※※※※※※※※※※※※※※※\n\n\n" NOR,
        ]));
        set("exits", ([
                "north" : __DIR__"tyroad10",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -290);
        set("coor/y", -320);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}