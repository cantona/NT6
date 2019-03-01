#include <ansi.h>
inherit ITEM; 

void create()
{
        set_name("血月", ({"blood moon"}) );
        set_weight(300);
        set("no_get", 1);
        set("maze_item",1);
        set("unit", "輪");
        set("long", "一輪血紅色的月亮，會對所有非鬼怪的生物造成傷害，並且治療鬼怪生物。\n");
        set("value", 2000);
        setup();
} 

void hurt() {
        object *objs,obj;
        
        if(!environment())
                return;
        if(!query("owner")) {
                destruct(this_object());
                return;
        }
        objs = all_inventory(environment());
        foreach(obj in objs) {
                if(obj==query("owner") || obj->is_undead()) {
                        message_vision(HIC"血月的光華照在$N身上，$N變得精神百倍！\n"NOR,obj);
                        obj->receive_heal("qi",4000);
                        obj->receive_curing("qi",4000);
                        obj->receive_heal("jing",2000);
                        obj->receive_curing("jing",2000);
                        continue;
                }
                if(userp(obj)) {
                        message_vision(HIR"血月的光華照在$N身上，$N的生命力在快速的流失！\n"NOR,obj);
                        obj->receive_damage("qi",2000+random(1000),query("owner"));
                        obj->receive_damage("jing",1000+random(1000),query("owner"));
                        COMBAT_D->report_status(obj);
                }
        }
        call_out("hurt",5);
}
