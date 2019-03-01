#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "桃園籬笆");
        set("long", @LONG
你走在一條通往桃樹林深處的小道上，四周非常安靜，景色怡人。
前面有個籬笆(fence)門。
LONG );
        set("outdoors", "wudang");
        set("item_desc",([
                "fence" : WHT "\n\n"
                          "\t※※※※※※※※※※※※※※※\n"
                          "\t※※※※※※※※※※※※※※※\n"
                          "\t※※※　　　　　　　　　※※※\n"
                          "\t※※※　" HIM "應憐屐齒印蒼苔" NOR + WHT "　※※※\n"
                          "\t※※※　　　　　　　　　※※※\n"
                          "\t※※※　" HIM "小扣柴扉久不開" NOR + WHT "　※※※\n"
                          "\t※※※　　　　　　　　　※※※\n"
                          "\t※※※　" HIM "春色滿園關不住" NOR + WHT "　※※※\n"
                          "\t※※※　　　　　　　　　※※※\n"
                          "\t※※※　" HIM "一枝紅杏出牆來" NOR + WHT "　※※※\n"
                          "\t※※※　　　　　　　　　※※※\n"
                          "\t※※※※※※※※※※※※※※※\n"
                          "\t※※※※※※※※※※※※※※※\n\n\n" NOR,
        ]));
        set("exits", ([
                "south" : __DIR__"tyroad10",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -290);
        set("coor/y", -300);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}