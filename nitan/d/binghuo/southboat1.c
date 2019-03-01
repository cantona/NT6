// Room: /binghuo/southboat1.c
// Date: Oct.28 1999 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "木筏");
        set("long", @LONG
此木筏是島上參天古木紮就，豎立主桅副桅，這些木材因生于寒
冰之地，木質致密，硬如鐵石。帆布和帆索都用樹筋獸皮來編織、搓
結。筏上水腌肉，存貯清水的皮袋皆已具備。只欠......
LONG );
        set("no_sleep_room",1);
        set("outdoors", "binghuo");
        set("no_clean_up", 0);
        set("exits", ([
                "out" : __DIR__"haitan",
        ]));
        setup();
}

void init()
{
        object ob = this_player();
        mapping fam;
        if ((strsrch(NATURE_D->game_time(), "一月") >= 0) ||
           (strsrch(NATURE_D->game_time(), "二月") >= 0))
        {
                call_out("south1", 3, ob);
        }
        else
        {
                message_vision(HIR"\n現在北風未起，你恐怕回不去了！\n"NOR, ob);
        }
}

void south1( object ob )
{
        if( !ob ) return;
        message_vision( BLU
"\n這時海流帶動木排，緩緩飄開，$N眼見冰火島慢慢模糊，漸漸
的小了下去。隔了良久良久，終于再也瞧不見了。\n\n" NOR, ob);
        ob ->move(__DIR__"southboat2") ;
        tell_object(ob, BLU 
"\n一路刮的是北風，帶著木筏直向南行。在這茫茫大海之上，自也認不
出方向，但見每日太陽從左首升起，從右首落下，每晚北極星在筏後
閃爍，而木筏又是不停的移動，你便知離中原日近一日。\n" NOR ) ;
        call_out("south2", 10, ob);
}
void south2( object ob )
{
        if( !ob ) return;
        tell_object(ob , BLU
"\n終于到港了，滿身疲倦的你腳踏實地仍有虛浮的感覺。\n\n" NOR) ;
        ob->move ("/d/beijing/haigang");
}
