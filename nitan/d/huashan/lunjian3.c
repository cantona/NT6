#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", RED "浴血殘陽" NOR);
        set("long", HIR "                夕     陽\n" + NOR + RED +
                "已將整個絕頂染成血紅色，你仿佛已嗅到一股血腥之氣。" + NOR + "\n ");
        set("exits", ([ /* sizeof() == 1 */
        ]));
        set("no_magic", 1);
        set("fight_room", "/adm/npc/biwu3");
        setup();
}

void init()  
{ 
        object me = this_player();  
        add_action("discmds", ({  
                   "steal", "cast", "conjure", "array", "fight", "hit",   
                   "quit", "exit", "recall", "kill", "ansuan", "touxi", "summon",
        }));  
} 

int discmds() 
{ 
        tell_object(this_player(), "比武是光明正大，不許作弊！\n");  
        return 1;  
} 

void relay_message(string msg)
{
        object look_fight_room, look_room;
        string *msgs;
        int i;
        
        if (! look_fight_room = find_object("/adm/npc/biwu3"))
                look_fight_room = load_object("/adm/npc/biwu3");
                
        if (! look_room = find_object("/adm/npc/kantai"))
                look_room = load_object("/adm/npc/kantai");
                                
        msgs = explode(msg, "\n");
        for (i = 0; i < sizeof(msgs); i++)
        if (strlen(msgs[i]) > 5)
        {
                message("vision", NOR + BOLD + ">>" + NOR + msgs[i] + "\n", look_fight_room);
                message("vision", NOR + BOLD + ">>" + NOR + msgs[i] + "\n", look_room);
        }
}

