inherit ROOM;
#include <ansi.h>; 
void create()
{
        set("short", "洞道"); 
        set("long", @LONG
山洞極窄，須膝行而爬，若一不小心，就不免被洞中的石壁撞的
頭破血流，洞中潮濕陰暗，腥臭難聞，一陣陣的惡臭撲面而來，你不
禁頭暈目眩，難受異常。
LONG );
        set("indoors", "wansong");
        set("type","mountain");
        set("exits",([
                "out":__DIR__"dongkou",
                "north":__DIR__"shandong1",
        ]) ); 
        set("coor/x",-610);
        set("coor/y",290);
        set("coor/z",80);
        setup();
        
} 
int valid_leave(object me, string dir)
{
        
        if( userp(me) && !query_temp("fugui_liquan", me) && dir == "north" )
        {
        message_vision( HIC "一陣陣的惡臭撲面而來，$N不禁頭暈目眩,難受異常。\n\n"NOR,me);
                // me->unconcious();
                return 0;
        } else
        {
                return 1;
        }
}  
