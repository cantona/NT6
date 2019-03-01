//Cracked by Kafei
// heye 荷葉
// xbc 06/21/97

inherit ITEM;

void create()
{
        set_name("荷葉", ({"he ye", "lotus leaf"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一片大大的綠綠的荷葉。\n");
                set("unit", "片");
                set("value", 0);
        }
}