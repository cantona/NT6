#include <ansi.h>

inherit DEMONROOM;

void create()
{
        set("short", "九頭蛇領地");
        set("long",@LONG
這是九頭蛇的領地，周圍盡是潮濕陰深的濕地，恐怖之極。
LONG);


        set("exits", ([
                "east"  : __DIR__"jiutou1.22",                
                "west"   : __DIR__"jiutou1.2",
                "out"    : __DIR__"haitan",
                
        ]));
                set("no_rideto", 1);         // 設置不能騎馬到其他地方
                       set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
                set("n_time", 60);
                set("n_npc",1); 
                set("n_max_npc", 2);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/jiutoushe");

        setup();
}


// 判斷玩家是否付費，未付費則不能進入
void init()
{
        object me = this_player();
        int i;
        object *inv;
        
        if (! objectp(me))
        {
                me->move(__DIR__"haitan");
        }
        
        if (! playerp(me))return;
        
        if( !me->enter_jtshe_srv() )
        {
                tell_object(me, HIR "\n對不起，你沒有進入九頭蛇領地的特權，不能進入！\n\n" NOR);
                me->move(__DIR__"haitan");
        }

        // 把背起的用户放下來
        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! playerp(inv[i])) continue;

                // 被人揹起的用户
                inv[i]->move(__DIR__"haitan");                
        }        
        
        // 允許進入
        return;
}
