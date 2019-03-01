//Cracked by Kafei
// paper.c
inherit ITEM;

void create()
{
        set_name("信箋", ({"letter paper", "paper"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long",
"天長地久，人生幾時？先後無覺，從爾有期。\n");
                set("material", "paper");
        }
}
