#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_QIN;

void create()
{
        set_name(MAG "九霄環佩﹒唐朝" NOR, ({ "jiuxiao qin", "jiuxiao", "qin" }));
        set_weight(600);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", MAG "這是歷史最悠久的傳世之琴，盛唐開元之器。\n"
                                "此琴形體飽滿，上髹紫漆，間雜朱砂後補之  \n"
                                "色，貴在聲形俱佳，為傳世之器的極品。\n" NOR);

                set("value", 400000);
                set("material", "wood");
             }
        setup();
}

void init()
{
        add_action("play_qin", "play");
}