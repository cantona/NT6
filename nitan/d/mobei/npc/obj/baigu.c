// baigu.c
// Last Modified by winder on May. 25 2001

inherit ITEM;
void create()
{
        set_name("骷髏頭骨", ({ "kulou tougu" }) );
        set_weight(900);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "白骨慘慘，每個頭骨的頂上都有五個指孔。\n");
        }
}

