#include <ansi.h>
inherit ITEM;

void create()
{
                
        set_name(RED"迷宮入口"NOR, ({ "maze door","door"}) );
        set_weight(5);
        set("no_get",1);

        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", GRN"從這個入口可以進入迷宮。(enter door)\n"NOR); 
                set("unit", "個");
                set("lore",1);
                set("value", 20);
        }
        setup();
}

void init()
{
        add_action("do_enter","enter");
}

int do_enter(string arg) {
        object maze;
        string entry;
                
        if( arg != "door" )
                return 0;
        
        entry = query("maze_entry");
        
        if( !stringp(entry) || entry == "" || 
            !(maze = get_object(entry)) )
                return notify_fail("迷宮已經摧毀，無法進入。\n");
                
        this_player()->move(maze);
        return 1;
}
