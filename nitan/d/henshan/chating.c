inherit ROOM;

void create()
{        
       set("short", "茶亭");        
        set("long", @LONG
這是一家路邊的小茶亭，趕山路的人常在此處歇歇腳。亭子裡有
幾張桌子和幾支條凳。周圍是一片樹林。
LONG );
    
       set("outdoors", "henshan");        

       set("exits", ([                
              "west"  : __DIR__"hsroad6",        
       ]));        

       set("objects", ([                
               __DIR__"npc/yuanziyi" :1,        
       ])); 
      
       set("no_clean_up", 0);        

	set("coor/x", -6920);
	set("coor/y", -5690);
	set("coor/z", 0);
	setup();        
       replace_program(ROOM);
}