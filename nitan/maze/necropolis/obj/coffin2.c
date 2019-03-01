#include <ansi.h>
inherit ITEM; 

int generate_monk;
void set_generate_monk(int i) {
        generate_monk = i;
}
int query_generate_monk() {
        return generate_monk;
}

void create()
{
        set_name("棺材", ({"coffin"}) );
        set_weight(300);
        set("no_get", 1);
        set("unit", "輪");
        set("long", "一具腐朽的棺木,好像可以推開蓋子(push)。\n");
        set("value", 2000);
        setup();
} 

void init () {
        add_action("do_push","push");
}

int do_push(string arg) {
        object monk;
        
        if(!arg || (arg!="coffin" &&  arg!="棺材")) 
                return notify_fail("你要推什麼？\n");
                
        if(query_generate_monk()) {
                message_vision("$N推開了棺材，但是裡面什麼都沒有。\n",this_player());
                return 1;
        } else {
                message_vision("$N推開了棺材，裡面居然有個和尚。\n",this_player());
                monk = new("/maze/necropolis/npc/monk");
                monk->move(environment(this_player()));
                message_vision("$N嘆了口氣道：還是被找著了。\n",monk);
                set_generate_monk(1);
                return 1;
        }
}
