// bowl.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("水碗", ({ "wan", "bowl" }) );
        set_weight(400);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一個水碗，裡面有什麼呢？當然是水啦。\n");
                set("unit", "個");
                set("value", 0);
                set("max_liquid", 60);
        }

        // The liquid contained in the container is independent, we set a copy
        // in each cloned copy.
        set("liquid", ([
                "type": "water",
                "name": "水",
                "remaining": 60,
        ]) );
}