// 玫瑰宴會廳.c

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
        set("long", @LONG
進門繞過一道淡黃綢屏風，迎面牆上掛著一副『玫瑰含露』圖，
鮮嫩欲滴，花瓣輕分，似有香氣盈室。廳內陳列奢華，正中央一張雕
花楠木青漆嵌玉大圓桌，四周十二張鑲銀象牙扶手紅木椅，杯碗勺箸，
入眼生輝。    這裡便是醉仙樓的玫瑰廳，桌上平舖著一份菜單(men
u)。
LONG );
        else
              set("long", GRN+"一盤熱氣騰騰,香噴噴的"+nmstr+"。\n"+NOR, obj);
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
              set("long", YEL+"一杯可口的"+nmstr+"。\n"+NOR, obj);
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
              set("long", RED+"一杯醇正的"+nmstr+"。\n"+NOR, obj);
        set("liquid/name", nmstr, obj);
        obj->move(this_object());
}

void create()
{
        set("short", HIG"玫瑰宴廳"NOR);
        set("long", @LONG
進門繞過一道淡黃綢屏風，迎面牆上掛著一副『玫瑰含露』圖，鮮嫩欲滴，
花瓣輕分，似有香氣盈室。廳內陳列奢華，正中央一張雕花楠木青漆嵌玉大圓桌，
四周十二張鑲銀象牙扶手紅木椅，杯碗勺箸，入眼生輝。
    這裡便是醉仙樓的玫瑰廳，桌上平舖著一份菜單(menu)。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "west" : "/d/city/zxlpath",
        ]));
        set("no_sleep_room",1);
        set("item_desc", ([
                "menu": @TEXT
承辦各式酒席, 歡迎惠顧：

        order birthday: 祝壽宴        (2兩黃金)

        order marry:    訂婚宴        (3兩黃金)

        order player:   群豪宴        (5兩黃金)

        order end:      結  束

TEXT
        ]) );
//        create_door("out", "紅木鏤花門", "enter", DOOR_CLOSED);
        set("no_clean_up", 0);
	set("coor/x", 30);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
        set("no_user", 1);
}

void init()
{
        object me;

        add_action("do_order", "order");
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
        if (type == "marry") {
                mesg = me->name() + "現在在醉仙樓玫瑰廳舉行訂婚酒宴了  !!!\n";
        } else if (type == "birthday") {
                mesg = me->name() + "現在在醉仙樓玫瑰廳舉行生辰壽宴了  !!!\n";
        } else if (type == "player") {
                mesg = me->name() + "現在在醉仙樓玫瑰廳宴請各路英雄豪傑  !!!\n";
       }
        message("channel:chat", RED+"【江湖通告】"+mesg+NOR, users() );
        message("channel:chat", GRN+"【江湖通告】"+mesg+NOR, users() );
        message("channel:chat", CYN+"【江湖通告】"+mesg+NOR, users() );
        return 1;
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
                mesg = "玫瑰廳的宴會結束了  !!!\n";
                message("channel:chat", RED+"【江湖通告】"+mesg+NOR, users() );
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
                return notify_fail("這裡已經被人包租了.\n");
         notify_fail("你沒有足夠的錢或零錢不夠.\n");
        if (arg == "marry") {
                mesg = me->name() + "現在在醉仙樓玫瑰廳舉行訂婚酒宴了  !!!\n";
                if (me->can_afford(30000) == 0)
                        return 0;
                me->pay_money(30000);
                create_water(HIG"龍井茶"NOR, ({ "tea" }), MAG"紫砂茶盅"NOR );
                create_water(RED"普洱茶"NOR, ({ "tea" }), WHT"水晶盞"NOR );
                create_wine(WHT"米酒"NOR, ({ "wine" }), HIW"搪瓷杯"NOR );
                create_wine(GRN"竹葉青"NOR, ({ "wine" }), GRN"翡翠杯"NOR );
                create_wine(YEL"紹興黃酒"NOR, ({ "wine" }), HIY"象牙杯"NOR );
                create_wine(HIR"女兒紅"NOR, ({ "wine" }), MAG"紫檀杯"NOR );
                create_wine(WHT"茅台酒"NOR, ({ "wine" }), YEL"鎏金杯"NOR );
                create_wine(RED"桂花酒"NOR, ({ "wine" }), WHT"琉璃杯"NOR );
                create_food(YEL"香酥花生"NOR,({"peanut"}) );
                create_food(HIR"酒糟紅棗"NOR,({"jujube"}) );
                create_food(RED"喜糖"NOR,({"sugar"}) );
                create_food(HIW"奶油瓜子"NOR,({"melon seeds","seeds"}) );
                create_food(HIG"碧螺春卷"NOR, ({ "spring roll","roll" }) );
                create_food(HIC"香片蒸魚"NOR, ({"fish"}) );
                create_food(HIW"麻辣手撕雞"NOR, ({"chicken"}) );
                create_food(HIR"幹煸尤魚"NOR, ({"fish"}) );
                create_food(HIY"東北水餃"NOR, ({ "dumpling" }) );
                create_food(RED"麻辣火鍋"NOR, ({ "chafing dish","dish" }) );
                create_food(HIR"油煎螃蟹"NOR, ({ "crab" }) );
                create_food(HIY"粉蒸肉"NOR, ({ "meat" }) );
                create_food(YEL"家常豆腐"NOR, ({ "bean curd" }) );
        } else if (arg == "birthday") {
                mesg = me->name() + "現在在醉仙樓玫瑰廳舉行生辰壽宴了  !!!\n";
                if (me->can_afford(20000) == 0)
                        return 0;
                me->pay_money(20000);
                create_water(GRN"雲霧茶"NOR, ({ "tea" }), MAG"紫砂茶盅"NOR );
                create_water(HIG"君山銀針"NOR, ({ "tea" }), RED"紅泥盞"NOR );
                create_water(HIW"鮮奶"NOR, ({ "milk" }), WHT"玻璃杯"NOR );
                create_wine(RED"陳年花雕"NOR, ({ "wine" }), HIW"宋瓷杯"NOR  );
                create_wine(WHT"五糧液"NOR, ({ "wine" }), WHT"玻璃杯"NOR );
                create_wine(WHT"米酒"NOR, ({ "wine" }), HIW"搪瓷杯"NOR );
                create_wine(HIR"杜康酒"NOR, ({ "wine" }), HIG"青銅爵"NOR  );
                create_wine(HIW"透瓶香"NOR, ({ "wine" }), WHT"琉璃杯"NOR  );
                create_food(HIY"德州扒雞"NOR, ({ "chicken" }) );
                create_food(HIG"碧螺春卷"NOR, ({ "spring roll","roll" }) );
                create_food(HIC"香片蒸魚"NOR, ({"fish"}) );
                create_food(YEL"咖喱飯"NOR, ({"rice"}) );
                create_food(RED"蠔油肉片"NOR, ({"fish meat","meat"}) );
                create_food(RED"羊肉串"NOR, ({ "mutton" }) );
                create_food(HIR"重慶火鍋"NOR, ({ "chafing dish","dish" }) );
                create_food(HIY"北京烤鴨"NOR, ({ "duck" }) );
                create_food(YEL"粉蒸肉"NOR, ({ "meat" }) );
                create_food(HIW"四喜豆腐"NOR, ({ "bean curd" }) );
        } else if (arg == "player") {
                mesg = me->name() + "現在在醉仙樓玫瑰廳宴請各路英雄豪傑  !!!\n";
                if (me->can_afford(50000) == 0)
                        return 0;
                me->pay_money(40000);
                create_food(YEL"叫花雞"NOR, ({ "chicken" }) );
                create_food(HIW"四喜豆腐"NOR, ({ "bean curd" }) );
                create_food(HIG"碧螺春卷"NOR, ({ "spring","roll" }) );
                create_food(HIC"香片蒸魚"NOR, ({"fish"}) );
                create_food(RED"羊肉串"NOR, ({ "mutton" }) );
                create_food(HIY"花枝飯卷"NOR, ({"rice"}) );
                create_food(HIR"魚香肉絲"NOR, ({"fish meat","meat"}) );
                create_food(HIY"德州扒雞"NOR, ({ "chicken" }) );
                create_food(RED"麻辣火鍋"NOR, ({ "chrafing dish","dish" }) );
                create_food(HIY"北京烤鴨"NOR, ({ "duck" }) );
                create_food(HIW"白斬雞"NOR, ({ "chicken" }) );
                create_food(YEL"粉蒸肉"NOR, ({ "meat" }) );
                create_food(HIR"重慶火鍋"NOR, ({ "chafing dish","dish" }) );
                create_food(HIR"麻婆豆腐"NOR, ({ "bean curd" }) );
                create_food(RED"蠔油肉片"NOR, ({"fish meat","meat"}) );
                create_food(YEL"咖喱飯"NOR, ({"rice"}) );
                create_food(HIW"麻辣手撕雞"NOR, ({"chicken"}) );
                create_food(HIR"幹煸尤魚"NOR, ({"fish"}) );
                create_food(HIY"東北水餃"NOR, ({ "dumpling" }) );
                create_water(HIW"羊奶"NOR, ({ "milk" }), CYN"青花碗"NOR );
                create_water(GRN"雲霧茶"NOR, ({ "tea" }), MAG"紫砂茶盅"NOR );
                create_water(GRN"碧螺春"NOR, ({ "tea" }), MAG"紫砂盞"NOR );
                create_water(HIG"君山銀針"NOR, ({ "tea" }), RED"紅泥盞"NOR );
                create_water(HIR"紅毛尖"NOR, ({ "tea" }), CYN"青泥盞"NOR );
                create_wine(HIW"汾酒"NOR, ({ "wine" }), WHT"羊脂白玉杯"NOR );
                create_wine(WHT"關外白酒"NOR, ({ "wine" }), YEL"犀角杯"NOR );
                create_wine(RED"葡萄酒"NOR, ({ "wine" }), HIW"夜光杯"NOR );
                create_wine(WHT"高粱酒"NOR, ({ "wine" }), CYN"青銅爵"NOR );
                create_wine(HIG"百草酒"NOR, ({ "wine" }), RED"古籐杯"NOR );
                create_wine(HIR"狀元紅"NOR, ({ "wine" }), WHT"古瓷杯"NOR );
                create_wine(GRN"梨花酒"NOR, ({ "wine" }), HIG"翡翠杯"NOR );
                create_wine(HIW"玉露酒"NOR, ({ "wine" }), WHT"琉璃杯"NOR );
        }
         else {
                return notify_fail("你要定什麼酒席?\n");
        }
        message("channel:chat", RED+"【江湖通告】"+mesg+NOR, users() );
        message("channel:chat", GRN+"【江湖通告】"+mesg+NOR, users() );
        message("channel:chat", CYN+"【江湖通告】"+mesg+NOR, users() );
        set("order_owner",query("id", me));
        set("order_type", arg);
        return 1;
}
int valid_leave(object me, string dir)
{
        if( query("id", me) != query("order_owner") )
                return 1;
        return notify_fail(RED + "先用 order end 結束宴會後才能離開。\n" + NOR);
}

