inherit ROOM; 

void create() 
{ 
        set("short", "大漠出口"); 
        set("long", @LONG 
一望無際的大漠，烈日、風沙、苦寒、酷熱，無時不在折磨着每
一個人，在這裏，如果你沒有飲水，很有可能就會被曬死，沙子滾燙，
足以把腳燙爛，一到晚上，卻又冰冷得透骨。

LONG
); 
                        
        set("outdoors", "desert"); 
        set("no_magic",1);
        set("exits", ([ /* sizeof() == 3 */ 
                "north":__DIR__"maze/exit",
                "out": "/d/luoyang/wenmiao",
        ])); 
                        
        setup();
        // replace_program(ROOM); 
} 

/*
int valid_leave(object me, string dir)
{
        object *inv, obj;
        int ret;

        if (dir == "out")
        {
                //FUBEN_D->query_maze_mainobj(me)->refresh_maze();
                if( ret=query_temp("fuben_event", me) )
                {
                        SCHEDULE_D->delete_event(ret);
                        FUBEN_D->clear_fuben("desert",query("id", me));
                }
        }
        return 1;
}
*/
