inherit ROOM; 

void create() 
{ 
        set("short", "森林出口"); 
        set("long", @LONG 
原始森林樹葉蒼黑如蓋，遮天蔽日，林中彌漫著枯葉腐爛
和樹脂混合的味道，地上的苔鮮落葉踩上去軟綿綿的，上面還
布滿野獸的痕跡，四周濃密的山霧，讓人難以分辨方向。
LONG
); 
                        
        set("outdoors", "forest"); 
        set("no_magic",1);
        set("exits", ([ /* sizeof() == 3 */ 
                "east":__DIR__"maze/exit",
                "out": "/d/kunming/zhaoze",
        ])); 

        set("objects",([
                "/maze/forest/npc/forest_master": 1,  
        ])); 
                        
        setup();
        // replace_program(ROOM); 
} 

int valid_leave(object me, string dir)
{
        object *inv, obj;
        if (dir == "out")
        {
                tell_object(me, "check!\n");
                inv = deep_inventory(me);
                if (inv && sizeof(inv)>0)
                        foreach(obj in inv) {
                                if( obj && query("maze_item", obj) )
                                        destruct(obj);
                        }
                FUBEN_D->query_maze_mainobj(me)->refresh_maze();
        }
        MYGIFT_D->check_mygift(me, "newbie_mygift/fuben");
        return 1;
}
