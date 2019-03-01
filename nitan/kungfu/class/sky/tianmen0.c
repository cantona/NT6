#include <ansi.h>
inherit ROOM;

#define SCBORN_D       "/adm/daemons/scbornd"

void create()
{
        set("short", NOR + WHT "【通天門外】" NOR);
        set("long", HIW @LONG
你來到這裡，發現這裡茫茫一片雲海。不遠處有一道大門，門前站
著一個老者，似乎正注視著你。大門的正中央懸掛著一盞金黃色的長明
燈（changmingdeng for xueyi）。
LONG NOR );
        set("exits", ([
                "enter" : __DIR__"tianmen",
]));
        set("sky", 1);
        set("objects", ([
                __DIR__"npc/xing": 1,
                "/clone/misc/changmingdeng" : 1,
        ]));

        set("no_fight", 1);
        setup();
}

void init()
{
        // this_player()->delete("yhjob");
}

int valid_leave(object me, string dir)
{
        object ob;
        object *inv;
        int i;

        //if (! wizardp(me))return notify_fail("暫不開放！\n");

        if (time() - me->query("last_enter_tianmen0") < 86400)                        
        {
                 return notify_fail("對不起，你距離上次進入天界不足24小時，無法再次進入天界。\n");
        }

        // 進入12重天的條件
        if ( dir == "enter" && ! me->query("sky12/floor"))
        {
               ob = present("xingjun yan", environment(me));
               if (! objectp(ob))return notify_fail("物件出錯！\n");
               message_vision(HIC "星君眼仔細的看著$N" HIC " ……\n" NOR, me);

               if (! SCBORN_D->check_data(me))
               {
                            message_vision(HIW "星君眼冷冷地對$N" HIW "說道：你的條件還不"
                                           "夠闖天界十二重天。\n" NOR, me);
                                         
                            return notify_fail("\n");  
               }
        }

        if (dir == "enter")
        {
                // 背了人則進入不了
                inv = deep_inventory(me);
                for (i = 0; i < sizeof(inv); i++)
                {
                        if (! playerp(inv[i])) continue;
        
                        // 被人背起的用戶
                        return notify_fail(HIW "星君眼冷冷地對$N" HIW "說道：“我看你還是先把" + inv[i]->name() + 
                                           HIW "放下再說吧！\n" NOR);                
                }                
        }

        me->set("last_enter_tianmen0", time());

        return ::valid_leave(me, dir);
}
