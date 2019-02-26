// loveroom.c 相約軒
#include <ansi.h>
#include <room.h>
inherit ROOM;

varargs protected void
create_food(string nmstr, string* idlist, string longstr)
{
        object obj;

        obj = new("/d/city/obj/food");
        obj->set_name(nmstr, idlist);
        if (longstr)
              set("long", longstr, obj);
        else
              set("long", "一盤熱氣騰騰,香噴噴的"+nmstr+"。\n", obj);
        obj->move(this_object());
}

varargs protected void
create_water(string nmstr, string* idlist, string cup, string longstr)
{
        object obj;

        obj = new("/d/city/obj/water");
        obj->set_name(cup, idlist);
        if (longstr)
              set("long", longstr, obj);
        else
              set("long", "一杯可口的"+nmstr+"。\n", obj);
        set("liquid/name", nmstr, obj);
        obj->move(this_object());
}

varargs protected void
create_wine(string nmstr, string* idlist, string cup, string longstr)
{
        object obj;

        obj = new("/d/city/obj/wine");
        obj->set_name(cup, idlist);
        if (longstr)
                set("long", longstr, obj);
        else
                set("long", "一杯醇正的"+nmstr+"。\n", obj);
        set("liquid/name", nmstr, obj);
        obj->move(this_object());
}

void create()
{
        set("short", MAG"相約軒"NOR);
        set("long", @LONG
樓外樓的相約軒，四面通窗。湖風拂面，淡淡生暖。遠望蘇堤一
線，映波，鎖瀾，望山，壓堤，東浦，跨虹六橋斷續連沿，煙柳籠紗，
流鶯嬌啼。近處白堤橫亙湖上，堤上楊柳覆地，芳草寒茵如一段碧綢
飄然湖面。室內一張精巧的小桌。桌上一紙精緻的菜單(menu)。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
            "down" : __DIR__"jiulou",
        ]));
        set("sleep_room",1);
        set("item_desc", ([
            "menu": @TEXT
        order party:    濃情幽會    (200兩銀子)

        order end  :    結束狂歡

        close door  :   關閉房門

        open door   :   打開房門

TEXT
        ]) );
        //create_door("down", "紅木雕花門", "up", DOOR_OPENED);
        set("no_clean_up", 0);
	set("coor/x", 840);
	set("coor/y", -2040);
	set("coor/z", 10);
	setup();
        set("no_user", 1);
}

void init()
{
        object me;

        add_action("do_order", "order");
        //add_action("do_close","close");
        add_action("do_open","open");
        add_action("do_broadcast", "broadcast");
        if (query("order_owner")) {
                me = this_player();
                set("food",query("food",  me)/2, me);
                set("water",query("water",  me)/2, me);
        }
}

int do_broadcast(string arg)
{
        string type;
        string mesg;
        object me;

        me = this_player();
        if( query("order_owner") != query("id", me) )
                return 0;
        type = query("order_type");
        if (type == "party") {
                mesg = me->name() + "在杭州樓外樓和某人幽會 !!!!!!\n";
        message("channel:chat", RED+"【通告】"+mesg+NOR, users() );
        message("channel:chat", GRN+"【通告】"+mesg+NOR, users() );
        message("channel:chat", CYN+"【通告】"+mesg+NOR, users() );
        return 1;}
}

int do_order(string arg)
{
        object me, env;
        object* oblist;
        string mesg;
        int idx;

        me = this_player();
        env = this_object();
        mesg = query("order_owner");
        if( mesg && (arg == "end") && (mesg == query("id", me))){
                mesg = "幽會終於結束了 !!!!!!\n";
                message("channel:chat", RED+"【通告】"+mesg+NOR, users() );
                delete_temp("plugin");
                delete("order_owner");
                delete("order_type");
                oblist = all_inventory(env);
                for(idx=0; idx<sizeof(oblist); idx++) {
                        if (!objectp(oblist[idx]))
                                continue;
                        if (userp(oblist[idx]))
                                continue;
                        destruct(oblist[idx]);
                }
                return 1;
        }
        if (mesg)
                return notify_fail("這裏已經被人包租了.\n");
        notify_fail("你沒有足夠的錢或零錢不夠.\n");
        if (arg == "party") {
                mesg = me->name() + "和某人在杭州樓外樓幽會 !!!!!!\n";
                if (me->can_afford(20000) == 0)
                        return 0;
                me->pay_money(20000);
                create_water(CYN"龍井茶"NOR, ({ "tea" }), MAG"紫砂茶盅"NOR );
                create_water(HIG"碧螺春"NOR, ({ "tea" }), MAG"紫砂盞"NOR );
                create_wine(HIY"紹興黃酒"NOR, ({ "wine" }), HIW"象牙杯"NOR );
                create_wine(GRN"竹葉青"NOR, ({ "wine" }), HIG"翡翠杯"NOR );
                create_wine(RED"女兒紅"NOR, ({ "wine" }), MAG"紫檀杯"NOR );
                create_food(RED"東坡肉"NOR, ({ "pork" }) );
                create_food(HIB"西湖醋魚"NOR, ({ "fish" }) );
                create_food(HIR"龍井蝦仁"NOR, ({ "shrimp" }) );
                create_food(YEL"叫化童雞"NOR, ({ "chicken" }) );
                create_food(HIR"桂花鮮慄羹"NOR, ({ "guihua geng" }) );
                create_food(HIY"百果油包"NOR, ({ "baozi" }) );
                }
         else {
                return notify_fail("這兒只承辦幽會小宴。\n");
        }
        message("channel:chat", RED+"【通告】"+mesg+NOR, users() );
        message("channel:chat", GRN+"【通告】"+mesg+NOR, users() );
        message("channel:chat", CYN+"【通告】"+mesg+NOR, users() );
        set("order_owner",query("id", me));
        set("order_type", arg);
        return 1;
}

int do_close(string arg)
{
        object me=this_player();
        object room;
        if(arg!="door") return notify_fail("你要幹什麼？\n");
        if (me->is_busy() || me->is_fighting())
                 return notify_fail("你正忙着呢。\n");
        room=this_object();
        delete("exits/down", room);
        query_temp("plugin", me);
        set_temp("plugin", 1, me);
        me->start_busy(10);
        message("channel:chat", HIR+"【通告】"+me->name()+"連門都關上啦 !!!!\n"NOR, users() );
        return 1;
}

int do_open(string arg)
{
        object me=this_player();
        object room;
        if(arg!="door") return notify_fail("你要幹什麼？\n");
        if (me->is_busy() || me->is_fighting())
                 return notify_fail("你正忙着呢。\n");
        room=this_object();
        set("exits/down", __DIR__"jiulou", room);
        query_temp("plugin", me);
        delete_temp("plugin", me);
        me->start_busy(10);
        message("channel:chat", HIR+"【通告】"+me->name()+"終於打開門啦 !!!!\n"NOR, users() );
        return 1;
}

int valid_leave(object me, string dir)
{
        if( query("id", me) != query("order_owner") )
                return 1;
        return notify_fail(RED + "先用 order end 結束後再走.\n" + NOR);
}
