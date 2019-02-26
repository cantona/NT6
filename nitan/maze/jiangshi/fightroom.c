inherit ROOM; 

void create() 
{ 
        set("short", "弒神大殿"); 
        set("long", @LONG 
這裏是30級BOSS挑戰區。

LONG
); 
                        
        set("outdoors", "boss"); 
        set("no_magic",1);
        set("exits", ([ /* sizeof() == 3 */ 
                "out": "/d/city/wumiao",
        ])); 
        
        set("objects", ([
                __DIR__"npc/daozhang" : 1,
        ]));
        
        setup(); 
} 

