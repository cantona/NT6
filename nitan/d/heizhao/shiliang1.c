// Room: /heizhao/shiliang1.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "石樑");
        set("long", @LONG
順着山路向前走去，行不多時，山路就到了盡頭，前面是條寬
約尺許的石樑，橫架在兩座山峯之間，雲霧籠罩，望不見盡處。這
石樑下臨深谷，別説行走，只望一眼也不免膽戰心驚。
LONG );
        set("outdoors", "taoyuan");
        set("exits", ([
                "southdown"  : __DIR__"shanding",
                "north"      : __DIR__"shiliang2",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1250);
        set("coor/z", 40);
        setup();
}

int valid_leave(object me, string dir)
{
        object *inv, ob;
        int i;

//        if(wizardp(me)) return 1;

        inv = all_inventory(me);
        if( !sizeof(inv) )
        {
                message_vision(HIW "$N在石樑上晃了一下，差點兒掉入萬丈深淵！\n" NOR,me);
                return notify_fail("");
        } else
        {
                switch( random(5) )
                {
                        case 0: 
                                for (i = 0; i < sizeof(inv); i++ )
                                {
                                if( query("id", inv[i]) == "huangbuxiaonan" )
                                        {
message_vision(HIM "$N在石樑上一晃，身上的"+inv[i]->name()+"掉入了萬丈深淵之中！\n" NOR,me);
                                                destruct(inv[i]);
                                        }
                                }
                                break;
                        case 1: 
message_vision(HIR "$N在石樑上晃了兩下，一骨碌滾下深淵！\n" NOR,me);
                                me->move(__DIR__"shanlu6");
message("vision",HIR"只見"+query("name", me)+"從山上骨碌碌地滾了下來，躺在地上半天爬不起來！\n"NOR,environment(me),me);
                                return notify_fail(HIR"你從石樑上滾下來，只覺得渾身傷痛。\n"NOR);
                                break;
                        default: 
message_vision(HIW "$N在石樑上晃了一下，差點兒掉入萬丈深淵！\n" NOR,me);
                                break;
                }
        }
        return 1;
}