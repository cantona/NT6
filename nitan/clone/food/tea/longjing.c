//longjing.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
//實際玩家買到應該是個茶壺。一開始是滿的。
        set_name("龍井茶",({"longjing cha", "cha hu", "hu"}));
         set_weight(120);
        if (clonep())
                 set_default_object(__FILE__);
         else {
                 set("long", "一壺新沏的龍井茶，悠悠地冒着香氣~~~~~~\n");
                set("unit", "壺");
                 set("value", 80);
        set("remaining",10);
                set("drink_supply", 20);
        }
        set("liquid", ([
                "type": "tea",
                "name": "龍井茶",
                "remaining": 15,
                "drunk_apply": 3,
        ]));
}
