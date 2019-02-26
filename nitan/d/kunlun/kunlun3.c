// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "崑崙之巔");
        set("long", @LONG
四下無聲，只有風吹松濤，幽韻天成，仰視蒼天，注視羣山，令
人不覺愴然而發思古之幽情！往前看，只見一塊很大的冰壁，下臨絕
崖，大冰壁表面極其光滑，如同鏡子一般，散發出奇異的光芒，往下
看，峭壁如刀削，雲卷霧湧，深不見底。
LONG );
        set("exits", ([
                "down" : __DIR__"kunlun2",
        ]));

        set("outdoors", "kunlun");
        setup();
}

void init()
{
        add_action("do_throw", "throw");
        add_action("do_enter", "enter");
}

int do_throw(string arg)
{
        object me, ob;

        me = this_player();
        if( !objectp( ob = present("contract", me) ) ||
            query("owner", ob) != query("id", me) )
                return 0;

        if( !query("reborn_offer", me) || query("reborn_offer", me) != "finish" )
                return 0;

        if( query("betrayer", me) )
                return notify_fail("你與判師門派中的糾葛未了，無法使用崑崙鏡！\n");

        if( !arg || arg != "contract" )
                return notify_fail("你要用什麼擲向那冰壁？\n");

        message_vision( HIW "$N" HIW "將泛紫光的閻王契(Contract)擲向那冰壁，閻王契沒入其中、竟爾消失不見。\n"
                        HIW "只見本就平滑的大冰壁愈見光潔、而後漸漸透明，漸漸化作了水銀鏡般的模樣，\n"
                        HIW "原來這正是通往地獄的通道：" HIR "「崑崙鏡」" HIW "(enter mirror)。\n" NOR, me );
        set_temp("throw_contract", 1, me);
        destruct(ob);
        return 1;
}

int do_enter(string arg)
{
        object me, *inv;
        int i;

        me = this_player();
        if( !query_temp("throw_contract", me) )
                return 0;

        if( !arg || arg != "mirror" )
                return notify_fail("你想要去那裏？\n");

        inv = deep_inventory(me);
        for( i=sizeof(inv)-1; i>=0; i-- ) {
                if( objectp(inv[i]) && inv[i]->is_character() ) {
                        tell_object(me, "你不可以將其他玩家或者NPC(包括寵物)背進崑崙鏡中。\n");
                        return 0;
                }
        }

        message_vision( HIW "$N" HIW "謹慎舉步，緩緩走入了崑崙鏡中。\n" NOR, me );
        tell_object(me, HIM "只見四周俱是五彩瑰麗景象，如臨仙境，好半晌後你才回過神、走出隧道，來到幽冥界。\n" NOR);
        delete_temp("throw_contract", me);
        me->move("/d/death/youmingjie");
        set("startroom", "/d/death/youmingjie", me);
        message("vision",HBRED"【轉世重生】地府："+query("name", me)+"("+query("id", me)+")"
                HBRED "進入幽冥界，欲挑戰幽冥地府考驗，換取轉世奇緣！\n" NOR, users());
        return 1;
}
