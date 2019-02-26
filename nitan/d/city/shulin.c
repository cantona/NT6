//By rama@lxtx

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{ 
        set("short", HIG"樹林"NOR);
        set("long", @LONG
忽然景色一轉，前面變成了一片幽深的樹林。你看看了看四周，
覺得周圍有些地方不太對頭，但是卻説上不上來。樹林裏面似乎有些
聲音傳來。到底該怎麼辦呢？你不由躊躇起來。
LONG );
        set("outdoors", "yangzhou");
        set("exits", ([
                "east" :  __FILE__,
                "west" :  __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ])); 
/*        set("objects", ([   
             "/d/city/npc/xdh-guard" : 2,   
            ]));
            */   
	set("coor/x", -10);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();            
}


int valid_leave(object me, string dir)
{
        int total_steps;

        if( query("bunch/bunch_name", me) == "小刀會" )
        {
                total_steps = 1; 
        } else
                       
                total_steps = 20;
        
        if (dir == "north")
                addn_temp("shulin/steps", 1, me);

        if (dir == "south")
                addn_temp("shulin/steps", -1, me);

        if( query_temp("shulin/steps", me) == total_steps )
        {
                me->move("/d/city/xdhzb");
                delete_temp("shulin/steps", me);
                write("你終於到了小刀會。\n");
                return -1;
        }  

        if( query_temp("shulin/steps", me) == -total_steps )
        {  
                me->move("/d/city/shulin1");
                delete_temp("shulin/steps", me);
                write("你走了半天又回到了原地。\n");
                return -1;
        }

        return ::valid_leave(me,dir);
}