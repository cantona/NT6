//Cracked by Kafei
// paper.c
inherit ITEM;

void create()
{
        set_name("信紙", ({"letter paper", "paper"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long",
"這是張普通的信紙，上面是岳不群寫給朋友的家常信，信已寫好，而且\n"
"蓋上了私印，大概走的匆忙忘記帶上了。\n");
                set("material", "paper");
        }
}
