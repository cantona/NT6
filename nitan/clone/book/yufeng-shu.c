
inherit ITEM;

void create()
{
        set_name("御蜂術", ({ "yufeng book", "book" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
"封面上寫著「古墓御蜂術」\n");
                set("value", 200);
                set("material", "paper");
        }
}
