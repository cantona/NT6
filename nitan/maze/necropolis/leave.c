inherit ROOM; 

void create() 
{ 
        set("short", "墓園出口"); 
        set("long", @LONG 
墓園裏沒有一點生氣，地上到處是枯枝敗葉，偶爾看到一些
乾枯的動物屍骸，讓人不寒而慄，到處散發着一股屍首腐爛的
味道，看不到一絲活物存在。
LONG
); 
                        
        set("outdoors", "necropolis"); 
        set("virtual_room", 1);
        set("no_magic", 1);
        set("exits", ([ /* sizeof() == 3 */ 
                "north":__DIR__"maze/exit",
                "out"  : "/d/shaolin/shijie11",
        ])); 
                        
        setup();

} 
int valid_leave(object me, string dir)
{
        object *inv, obj;
        int ret;
        if (dir == "out")
        {
                me->check_team();
                    tell_object(me, "check!\n");
                inv = deep_inventory(me);
                    if (inv && sizeof(inv)>0)
                            foreach(obj in inv) {
                                    if( obj && query("maze_item", obj) )
                                            destruct(obj);
                            }
/*
                if( ret=query_temp("fuben_event", me) )
                {
                        SCHEDULE_D->delete_event(ret);
                        FUBEN_D->clear_fuben("necropolis",query("id", me));
                }
*/

        }
        return 1;
}