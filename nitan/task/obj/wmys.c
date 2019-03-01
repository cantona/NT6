#include <ansi.h>
inherit TASK;
void create()
{
    set_name(WHT"武穆遺書" NOR, ({ "yue-script" }));
        set_weight(20);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "本");
                set("long",
            "這是一本傳自岳武穆的兵法手冊，內文均是行軍打仗、布陣用兵的精義要訣。\n");
                set("material", "paper");
                set("skill", ([
                        "name":         "strategy",             
                        "exp_required": 50000,                          
                        "sen_cost":     30,                     
                        "difficulty":   30,                     
                        "max_skill":    80              
                        ]) );
                }
        set("owner", "趙敏");
        setup();
}
