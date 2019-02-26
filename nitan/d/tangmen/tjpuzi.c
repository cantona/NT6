// tangjiapuzi.c 

#include <ansi.h>;
#include "/d/tangmen/npc/job1.h";

void create()
{
        set("short", "唐家鋪子");
        set("long",
"這是唐門世家的雜貨鋪，大箱小箱堆滿了一地，都是一些日常用品。\n"
"唐掌櫃正精神抖擻地注意着過往行人。據説這兒是唐門的一個情報點，有\n"
"許多重要的情報是從這兒出去的。門口掛着一個幌子（sign）。\n"
);
        set("item_desc", ([
                "sign": HIY"    唐       譽\n"
                           "    家       滿\n"
                           "    鋪       蜀\n"
                           "    子       中\n\n"NOR,
        ]));
        set("exits", ([
                "south" : __DIR__"edajie",
        ]));
        set("objects", ([
                __DIR__"npc/tangzg": 1,
        ]));
        set("no_clean_up", 1);
        setup();
}
