// cha.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("碧螺春", ({ "biluo chun","cha" }));
        set_weight(1000);
        if (clonep())
            set_default_object(__FILE__);
        else {
                set("long",
"這是一杯顏色碧綠、香味濃鬱上等好茶。本地人稱作嚇煞人香。!\n");
                set("unit", "杯");
                set("value", 20);
                set("max_liquid", 10);
        }
        set("liquid", ([
                    "name" : "碧螺春",
                    "remaining" : 8,
                "type" : "water"
        ]));
        set("liquid_type", "water");
        setup();
}