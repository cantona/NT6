// flower.c

inherit ITEM;

void create()
{
        set_name("絕情花", ({ "flower" }) );
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一朵散發著刺鼻味的野花。\n");
                set("unit", "一朵");
                set("value", 0);
        }
}
