inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "海灘");
        set("long",
"這裡是冰火島西岸海灘，海浪拍打著海邊巨石。周圍是一望無\n"
"際的大海，東邊傳來陣陣巨大的聲響，地動山搖一般，似乎島上的\n"
"火山在不斷地噴發，釋放出巨大的能量。\n"
);
        set("exits", ([ 
                "east"    : __DIR__"shadi",
        ]));
        
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裡
        set("binghuo", 1);           // 表示在冰火島    
        set("outdoors", "battle4");
        
        set("objects", ([
                __DIR__"npc/shouwei" : 1,
                __DIR__"npc/xiexiao-ci" : 1,
        ]));
        
        set("no_fight", 1);
        
        setup();
}

int valid_leave(object me, string dir)
{
        object guarder, horse, person;
        object *inv;
        int i;

        if (dir == "east")
        {
                // 非天下第一幫，且不在幫戰期間不得進入冰火島
                if( !BUNCH_D->is_battle_start() && !BUNCH_D->is_top_bunch(me) )
                {
                        if (! objectp(guarder = present("binghuo shouhushen", this_object())))
                        {
                                message_vision(HIM "一陣光芒閃過，冰火守護神的幻想竟出現在$N" HIM "眼前，令$N無法前進。\n" NOR, me);
                                return 0;
                        }
                        else
                        {
                                message_vision(HIM "$N" HIM "一把將$n" HIM "攔住，道：“目前冰火島只允許天下第一幫玩家進入！\n" NOR, guarder, me);
                                return 0;
                        }
                }
                
                // 幫戰期間，上屆天下第一幫成員不能進入
                if( (BUNCH_D->is_battle_start() || BUNCH_D->is_battle_open()) && BUNCH_D->query_bunch_topten(1) == query("bunch/bunch_name", me) )
                {
                        if (! objectp(guarder = present("binghuo shouhushen", this_object())))
                        {
                                message_vision(HIM "一陣光芒閃過，冰火守護神的幻想竟出現在$N" HIM "眼前，令$N無法前進。\n" NOR, me);
                                return 0;
                        }
                        else
                        {
                                message_vision(HIM "$N" HIM "一把將$n" HIM "攔住，道：“目前冰火島不允許上屆天下第一幫進入！\n" NOR, guarder, me);
                                return 0;
                        }
                } 
                
                // 所有騎馬的人必須下馬
                if( objectp(horse=query_temp("is_riding", me)) )
                {
                        if( objectp(person=query_temp("is_rided_follow", horse)) )
                                delete_temp("is_riding_follow", person);
        
                        delete_temp("is_rided_follow", horse);
                        delete_temp("is_rided_by", horse);
                        delete_temp("is_riding_follow", me);
                        delete_temp("is_riding", me);
        
                        message_vision(HIR "\n$N的" + horse->name() + HIR " 似乎受到了驚嚇，前蹄一揚，所有人"
                                       "被迫跳下馬。\n\n" NOR, me);
        
                        return 1;
                }

                // 把背起的用戶放下來
                inv = deep_inventory(me);
                for (i = 0; i < sizeof(inv); i++)
                {
                        if (! playerp(inv[i])) continue;
        
                        // 被人背起的用戶
                        inv[i]->move(__FILE__);
                }                       
        }

        return ::valid_leave(me, dir);
}
