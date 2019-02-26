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
"乞丐何曾有二妻？鄰家焉得許多雞？當時尚有周天子，何事紛紛説魏齊。\n");
                set("material", "paper");
        }
}
