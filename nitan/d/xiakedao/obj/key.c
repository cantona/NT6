// key.c

inherit ITEM;

void create()
{
        set_name("鑰匙", ({"key", "yaoshi"}));
        set("long",
                "這是一把很普通的鑰匙。\n");
        set("unit", "把");
        set("weight", 10);
        set_temp("times", 3);
        set("no_drop", 1);
        set("no_get", 1);
}

