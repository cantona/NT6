//Cracked by Kafei
// 
inherit ITEM;

void create()
{
        set_name("黃藥師手諭", ({"shou yu", "yu", "letter"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long","\n
=================================
|                                |
|                字                |
|                諭                |
|                靈                |
|                風                |
|                吾                |
|                徒                |
|                                |
|                        桃        |
|                        花        |
|                        黃        |
|                                |
|                        緘        |
|                                |
=================================\n");
                set("material", "paper");
        }
}