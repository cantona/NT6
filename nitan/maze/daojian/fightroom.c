inherit ROOM; 

void create() 
{ 
        set("short", "大殿"); 
        set("long", @LONG 
這裏是BOSS挑戰區。

LONG
); 
                        
        set("outdoors", "boss"); 
        set("no_magic",1);
        /*
        set("exits", ([ 
                "out": "/d/city/wumiao",
        ])); 
        */
        
        set("objects", ([
                __DIR__"npc/hu-yidao" : 1,
                __DIR__"npc/miao-renfeng" : 1,
        ]));
        
        setup(); 
} 

