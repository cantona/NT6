//dufang.c                四川唐門─毒房

#include <ansi.h>
#include <room.h>

inherit ROOM;

int do_putin(object me, object obj);

void create()
{
        set("short", "煉毒房");
        set("long",
"這裡是唐門的煉毒房。屋中沒有什麼擺設，只是靠牆擺著三個木架，\n"
"架子上擺滿了藥瓶藥罐，屋子正中用上好的青石壘成了一個灶台一個怕有\n"
"千斤重的紫銅藥爐重重的壓在上面，讓人奇怪的是兩丈見方的屋子裡竟沒\n"
"有一個窗戶。\n"
);
        set("exits", ([
                "southeast" : __DIR__"houroad4",
        ]));
        set("objects", ([
                __DIR__"npc/tangdu" : 1,
        ]));
        set("area", "tangmen");
        setup();
//        replace_program(ROOM);
}

void init()
{
        add_action("do_put","put");
}

int do_put(string arg)
{
        object obj, obj2, me, *inv;
        string item;
        int amount, i;

        me = this_player();

        if (!arg) return 0;

        if( sscanf(arg, "%s in yaolu", item) == 1 );
        else 
                return notify_fail("你要放什麼東西？\n");

        if(sscanf(item, "%d %s", amount, item)==2)
        {
                if( !objectp(obj = present(item, me)) )        
                        return notify_fail("你身上沒有這樣東西。\n");
                if( !obj->query_amount() )        
                        return notify_fail( obj->name() + "不能被分開給人。\n");
                if( amount < 1 )
                        return notify_fail("東西的數量至少是一個。\n");
                if( amount > obj->query_amount() ) 
                        return notify_fail("你沒有那麼多的" + obj->name() + "。\n");
                else 
                        if( amount == (int)obj->query_amount() )
                                return do_putin(me, obj2);
                        else
                        {
                                obj->set_amount( (int)obj->query_amount() - amount );
                                obj2 = new(base_name(obj));
                                obj2->set_amount(amount);
                                if (do_putin(me, obj2))
                                        return 1;
                                else
                                {
                                        obj->set_amount((int)obj->query_amount() + amount);
                                        return 0;
                                }
                        }
        }

        if(arg=="all")
        {
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        do_putin(me, inv[i]);
                }
                write("Ok.\n");
                return 1;
        }

        if(!objectp(obj = present(item, me)))
                return notify_fail("你身上沒有這樣東西。\n");
        return do_putin(me, obj);
}

int do_putin(object me, object obj)
{
        string tar, targ;
        int tarm;
        string *duwu = ({
                "","蜈蚣","毒蠍子","竹葉青","金環蛇","蝮蛇","千年毒王",
        });

        tar=query("name", obj);
        tarm=query_temp("duyao", me);
        targ = (string)duwu[tarm];

        printf("1%s1 == 1%s1 == %d/%d\n",tar,targ,tarm,sizeof(duwu));

        if( !query_temp("duyao", me) )
        {
                message_vision("唐毒一伸手打落了$N手上的" + obj->name() + "，叫到：“什麼東西就往藥爐裡放。”\n", me);
                obj->move(this_object());
                return 1;
        }        

        if ( (tar == targ) && objectp(obj) )
        {
                message_vision("$N拿出" + obj->name() + "放進藥爐。\n", me);
                destruct(obj);
                message_vision("唐毒對著$N點了點頭，說到：“好，你幹的很好，快去休息吧。”\n", me);
                delete_temp("tangmen", me);
                delete_temp("duyao", me);
                addn("combat_exp", 150+random(150), me);

//                if( (int)me->query("potential") > (int)me->query("learned_points"))
//                        me->addn("potential", ((int)me->query("learned_points") - (int)me->query("potential"))/2 );

                addn("potential", 80+random(30), me);
                return 1;
        }
        else
        {
                message_vision("唐毒一伸手打落了$N手上的" + obj->name() + "，叫到：“什麼東西就往藥爐裡放。”\n快去找" + targ+ "回來！\n", me);
                obj->move(this_object());
//                destruct(obj);
                return 1;
        }
}