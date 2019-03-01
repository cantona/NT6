inherit ITEM;
inherit F_LIQUID;

void init();

void create()
{
        set_name("杯子", ({ "cup", "beizi" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個磁杯子。\n");
                set("unit", "個");
                set("max_liquid", 5);
        }
        
        set("liquid", ([
                "name": "豆漿",
                "remaining": 8,
        ]));
        setup();
}