inherit ROOM; 
void create() 
{ 
        set("short", "森林入口"); 
        set("long", @LONG 
原始森林樹葉蒼黑如蓋，遮天蔽日，林中彌漫著枯葉腐爛
和樹脂混合的味道，地上的苔鮮落葉踩上去軟綿綿的，上面還
布滿野獸的痕跡，四周濃密的山霧，讓人難以分辨方向。
LONG
); 
                        
        set("outdoors", "forest"); 
        set("virtual_room", 1); 
        set("no_magic",1);
        set("exits", ([ /* sizeof() == 3 */ 
                "west" : __DIR__"maze/entry", 
        ])); 

        set("objects",([
                "/maze/forest/npc/forest_master": 1,  
        ])); 

        setup();
        replace_program(ROOM); 
} 
