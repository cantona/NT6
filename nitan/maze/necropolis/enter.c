inherit ROOM; 

void create() 
{ 
        set("short", "墓園入口"); 
        set("long", @LONG 
墓園裡沒有一點生氣，地上到處是枯枝敗葉，偶爾看到一些
幹枯的動物屍骸，讓人不寒而栗，到處散發著一股屍首腐爛的
味道，看不到一絲活物存在。
LONG
); 
                        
        set("outdoors", "necropolis"); 
        set("virtual_room", 1);
        set("no_death_penalty", 1);
        set("no_magic", 1);
        set("exits", ([ /* sizeof() == 3 */ 
                "south" : __DIR__"maze/entry", 
        ])); 
        set("objects",([
                "/maze/necropolis/obj/coffin1": 1,  
        ])); 
        setup();
 
} 