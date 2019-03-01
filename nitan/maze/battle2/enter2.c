inherit ROOM; 
void create() 
{ 
        set("short", "戰場入口"); 
        set("long", @LONG 
四周越來越暗了，你膽顫心驚的象前摸索著，到處是一些
迷路人的屍體和骷髏。不時傳來一陣陣鬼哭浪嚎,好象有什麼
東西在暗中窺視著，你不由的加快了腳步。
LONG
); 
                        
        set("outdoors", "battle"); 
        set("virtual_room", 1); 
        set("no_magic",1);
        set("exits", ([ /* sizeof() == 3 */ 
                "east" : __DIR__"maze/exit",
        ])); 

        setup();
        replace_program(ROOM); 
} 