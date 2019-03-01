// /d/shenlong/obj/songci.c
// Last Modified by winder on Jul. 12 2002

inherit ITEM;

void create()
{
        set_name("頌詞", ({ "songci" }));
        set("weight", 1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","這是一篇假造的頌詞。\n瞎扯大唐貞觀年間衛國公李靖料定千年後神龍教教主洪某，得蒙天恩。\n");
                set("unit", "幅");
                set("value", 20);
        }
        setup();
}