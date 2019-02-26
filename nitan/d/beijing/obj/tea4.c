inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("一級龍井茶", ({"longjing cha", "tea"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個藍邊粗磁大碗，裏面盛滿了龍井茶。\n");
                set("unit", "碗");
                set("value", 20);
        set("max_liquid", 4);
    }
    set("liquid", ([
        "type": "tea",
        "name": "茶水",
        "remaining": 4,
        "drunk_supply": 0,
    ]));
}