#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIC "地心﹒噬魂" NOR, ({"dixin shihun", "dixin", "shihun"}));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIC "一塊青色的地心噬魂，擁有集天下萬毒及邪能\n"
                            "于一身的至寶──地心噬魂，相傳為邪靈之主\n"
                            "羅剎到九幽之底，掘出當年被女媧消滅的異獸\n"
                            "骸骨，以地心毒火精煉而成。上古神物，已經\n"
                            "通靈。\n" NOR);
                set("value", 10000000);
                set("unit", "塊");
                set("can_be_enchased", 1);
                set("magic/type", "fire");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_fire"  : 50,
                "add_skill" : 30,
        ]));
        setup();
}

int query_autoload() { return 1; }
