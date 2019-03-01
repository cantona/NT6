// chufang.c 廚房
// Winder Oct.10 1998

inherit ROOM;
int do_kan(string arg);

void create()
{
        set("short", "廚房");
        set("long", @LONG
這裏是全真教的廚房，屋角上堆着一大堆手臂粗細的木柴，看
來還沒有劈好。一位火工道人正愁眉苦臉地坐在那裏，看着那堆柴。
牆上掛着一塊牌子(paizi)，牆邊扔着一把柴刀。
LONG
        );
        set("exits",([
                "west" : __DIR__"shantang",
        ]));
        set("item_desc", ([
            "paizi": "招收砍柴工人，待遇從優。\n"
        ]) );
        set_temp("times" , 20);
        set("objects" , ([
                __DIR__"npc/huogong" : 1,
        ]));

        set("coor/x", -2730);
        set("coor/y", 80);
        set("coor/z", 170);
        setup();
}

void init()
{
        add_action("do_kan","kan");
}

int do_kan(string arg)
{
        object me=this_player();
        object ob;
        if (query_temp("times")==0)
                return notify_fail("今天的活幹完了，明天再來吧！\n");

        if (!arg || arg != "柴")
                return notify_fail("別亂砍，小心傷着自個兒。\n");

        if(present("huogong", environment(me)) && living(present("huogong", environment(me))))
        {
        if( query("jing", me)<50 )
                return notify_fail("你的精力不夠了，休息一會兒再砍吧。\n");

        message_vision("$N揀起柴刀，豎起一根柴火，奮力砍下去。\n",me);
        addn_temp("times",-1);

        if (random(3)<2) {
                me->receive_damage("jing",20+random(20));
                message_vision("結果$N用力過猛，柴刀一下子嵌在了柴裏。$N用盡吃奶
的力氣把柴刀拔出來，又摔了個大跟斗。\n",me);
        }
        else {
                me->receive_damage("jing",20+random(40));
                ob = new("/clone/money/silver");
                ob->set_amount(10);
                ob->move(me);
                message_vision("結果木柴應聲被劈成兩半。火工道人笑着對$N説，你工
作的不錯呀，這是你的酬勞。\n",me);
                message_vision("火工道人給$N一些銀子。\n",me);
        }
        return 1;
        }
        else
                return notify_fail("老闆都不見了，你為誰白乾啊？\n");
}