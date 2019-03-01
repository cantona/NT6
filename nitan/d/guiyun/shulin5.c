// Room: /d/guiyun/shulin5.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

int do_zhai(string arg);
int do_sling(string arg);
int do_shake(string arg);
int do_climb(string arg);

void create()
{
        set("short", "樹林深處");
        set("long",@LONG
這是一片小樹林的深處。地面上綠草如蔭，茂密地生長著。四周安
靜得令人毛骨悚然，看來還是趕緊離開這裡的為妙。樹叢中有一棵老樹
(tree)，相對于其它樹顯得十分的粗壯，樹上的樹葉(leaf)非常茂密，
有幾只不知名的小鳥在其中竄來竄去。
LONG
);
        set("exits",([
                "southeast" : __DIR__"shulin4",
                "north"     : __DIR__"shulin7",
        ]) );
        set("item_desc", ([
                "tree" : "一棵大樹，枝葉茂密，看不清上面的情況。枝頭掛滿了野果，已經熟地要掉下來了。\n",
                "leaf" : "樹葉鬆鬆地掛在樹上，看上去很想把它摘下來。\n",
        ]) );
        set("no_clean_up",0);
        set("outdoors", "guiyun");
        set("stick_count", 3);
        set("coor/x", 290);
        set("coor/y", -800);
        set("coor/z", 0);
        setup();
}

void init()
{
        object room;

        add_action("do_sling", "sling");
        add_action("do_sling", "tan");
        add_action("do_sling", "shoot");
        add_action("do_sling", "she");
        add_action("do_shake", "shake");
        add_action("do_shake", "wave");
        add_action("do_shake", "yao");
        add_action("do_shake", "huang");
        add_action("do_strike", "strike");
        add_action("do_strike", "press");
        add_action("do_strike", "hit");
        add_action("do_strike", "pai");
        add_action("do_strike", "ji");
        add_action("do_climb", "climb");
        add_action("do_climb", "pa");
        add_action("do_zhai", "zhai");
        if (room = find_object(__DIR__"shushang"))
                tell_room(room, "透過樹葉的縫隙，你看見" + this_player()->name() + "來到了樹下。\n");
}

int do_zhai(string arg)
{
        object me = this_player();

        if (arg != "leaf" && arg != "shuye" && arg != "ye")
                return notify_fail("你要摘什麼？\n");

        message_vision("$N伸手去夠樹上的葉子，發現手臂需要再長幾十尺才行！\n", me);
        return 1;
}

int do_sling(string arg)
{
        object weapon, room, *ob;
        object me = this_player();
        int i, qi, level, qicost, temp, exp;
        string weapon_name;

        if (arg != "leaf" && arg != "shuye" && arg != "ye")
                return notify_fail("你要射什麼？\n");
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙著哪！\n");
        weapon=query_temp("weapon", me);
        if (!weapon) {
                message_vision("$N對著樹上的葉子運氣，又蹦又跳試圖把它摘下來，卻始終沒法夠到。\n", me);
                return 1;
        }
        weapon_name=query("name", weapon);
        if( query("skill_type", weapon) != "throwing"){
                message_vision("$N用手中的" + weapon_name + "去夠樹上的葉子，卻不夠長。\n", me);
                return 1;
        }

        if (room = find_object(__DIR__"shushang"))
        {
//                room = load_object(__DIR__"shushang");
                temp=10-query("str", me)/5;
                if (temp < 1) temp = 1;
                if (!random(temp))
                {
                        ob = all_inventory(room);
                        for (i = 0; i < sizeof(ob); i++)
                        {
                                if (userp(ob[i]))
                                {
                                        tell_object(ob[i], me->name() + "掏出一顆" + weapon_name + "，對著樹上彈來，卻正好擊中你，你腳下一個不穩，掉了下去。\n");
                                        tell_room(room, me->name() + "掏出一顆" + weapon_name + "，對著樹上彈來，卻正好擊中" + ob[i]->name() + "，" + ob[i]->name() + "腳下一個不穩，掉了下去。\n", ({ob[i]}));
                                        write("你掏出一顆" + weapon_name + "，對準樹葉彈去，只聽“啊”地一聲慘叫，一個人從樹上掉了下來，仔細一看，卻是" + ob[i]->name() + "。\n");
                                        tell_room(this_object(), me->name() + "掏出一顆" + weapon_name + "，對準樹葉彈去，只聽“啊”地一聲慘叫，一個人從樹上掉了下來，仔細一看，卻是" + ob[i]->name() + "。\n", ({me}));
                                        ob[i]->move(this_object());
                                        qi=query("qi", ob[i]);
                                        if (qi > 200) ob[i]->receive_damage("qi", qi / 2);
                                        else if (qi >= 100) ob[i]->receive_damage("qi", 100);
                                        else if (qi > 0) ob[i]->receive_damage("qi", qi);
                                        return 1;
                                }
                        }
                }
        }
        level = me->query_skill("throwing", 1);
        exp=query("combat_exp", me);
        qicost = level / 3 + random(level / 3);
        if( query("qi", me) <= qicost )
        {
                write("你太累了，先歇歇吧！\n");
                return 1;
        }
        if (level < 30)
        {
                write("你掏出一顆" + weapon_name + "，對準樹葉彈去，卻因為指勁太弱而沒有彈到。\n");
                WEAPON_D->throw_weapon(me, me, weapon, 0);
                return 1;
        }
        me->receive_damage("qi", qicost);
        if (level <= 100)
        {
                write("你掏出一顆" + weapon_name + "，對準樹葉彈去，只聽“嗤”地聲響過後，一片樹葉應聲而落。\n");
                WEAPON_D->throw_weapon(me, me, weapon, 0);
                if ( level * level * level /10 < exp)
                        me->improve_skill("throwing",query("int", me));
        }
        else {
                if (query("stick_count"))
                {
                        message_vision("$N掏出一顆" +weapon_name+"，對準樹葉彈去，結果用勁過大，連樹枝都敲了下來，暗器功夫上卻沒有新進展。\n", me);
                        addn("stick_count", -1);
                        new(__DIR__"obj/stick")->move(this_object());
                }
                else
                        write("你掏出一顆" + weapon_name + "，對準樹葉彈去，發現這樣練習太輕鬆了，暗器功夫上已經無法取得新進展。\n");
                WEAPON_D->throw_weapon(me, me, weapon, 0);
        }
        return 1;
}

int do_shake(string arg)
{
        object room, *ob;
        object me = this_player();
        int i, qi, level, qicost, temp ,exp;

        if (arg != "tree" && arg != "shu" && arg != "dashu")
                return notify_fail("你要搖什麼？\n");
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙著哪！\n");
        if (room = find_object(__DIR__"shushang"))
        {
//                room = load_object(__DIR__"shushang");
                temp=7-query("str", me)/5;
                if (temp < 1) temp = 1;
                if (!random(temp)) {
                        ob = all_inventory(room);
                        for (i = 0; i < sizeof(ob); i++)
                        {
                                if (userp(ob[i]))
                                {
                                        tell_object(ob[i],me->name()+"使勁地搖晃著大樹，你腳下一個不穩，掉了下去。\n");
                                        tell_room(room, me->name()+"使勁地搖晃著大樹，" + ob[i]->name() + "腳下一個不穩，掉了下去。\n", ({ob[i]}));
                                        write( "你使勁地搖晃著大樹，忽聽“嘩啦”一聲，一個人從樹上掉了下來，仔細一看，卻是" + ob[i]->name() + "。\n");
                                        tell_room(this_object(),me->name()+"使勁地搖晃著大樹，忽聽“嘩啦”一聲，一個人從樹上掉了下來，仔細一看，卻是"+ob[i]->name() + "。\n", ({me}));
                                        ob[i]->move(this_object());
                                        if (!random(3))
                                        {
                                                qi=query("qi", ob[i]);
                                                if (qi > 200) ob[i]->receive_damage("qi", qi / 2);
                                                else if (qi >= 100) ob[i]->receive_damage("qi", 100);
                                                else if (qi > 0) ob[i]->receive_damage("qi", qi);
                                        }
                                        return 1;
                                }
                        }
                }
        }
        level = me->query_skill("parry", 1);
        exp=query("combat_exp", me);
        qicost = level / 3 + random(level / 3);
        if( query("qi", me) <= qicost )
        {
                write("你太累了，先歇歇吧！\n");
                return 1;
        }
        if (level < 30)
        {
                write( "你使勁地搖晃著大樹，大樹卻紋絲不動，你不禁想到那句“蚍蜉撼樹”的成語來。\n");
                return 1;
        }
        if (level > 100)
        {
                write("你使勁地搖晃著大樹，把樹上的果子都搖得落到幾丈開外去了。\n");
                return 1;
        }
        me->receive_damage("qi", qicost);
        if (!random(5))
                message_vision("$N使勁地搖著大樹，從樹上掉下幾個果子來，砸向$N的頭臉，$N趕忙伸臂架開。\n", me);
        else
                write( "你使勁地搖著大樹，從樹上掉下幾個果子來，砸向你的頭臉，你趕忙伸臂架開。\n");
        if ( level * level * level /10 < exp)
                me->improve_skill("parry",query("int", me));
        return 1;
}

int do_strike(string arg)
{
        object room, *ob;
        object me = this_player();
        int i, qi, level, qicost, temp, exp;

        if (arg != "tree" && arg != "shu" && arg != "dashu")
                return notify_fail("你要拍什麼？\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙著哪！\n");

        if (room = find_object(__DIR__"shushang"))
        {
//                room = load_object(__DIR__"shushang");
                temp=9-query("str", me)/5;
                if (temp < 1) temp = 1;
                if (!random(temp))
                {
                        ob = all_inventory(room);
                        for (i = 0; i < sizeof(ob); i++)
                        {
                                if (userp(ob[i]))
                                {
                                        tell_object(ob[i],me->name()+"一掌拍向大樹，你腳下一個不穩，掉了下去。\n");
                                        tell_room(room, me->name()+"一掌拍向大樹，"+ob[i]->name()+"腳下一個不穩，掉了下去。\n", ({ob[i]}));
                                        write( "你一掌拍向大樹，忽聽“嘩啦”一聲，一個人從樹上掉了下來，仔細一看，卻是" + ob[i]->name() + "。\n");
                                        tell_room(this_object(),me->name()+"一掌拍向大樹，忽聽“嘩啦”一聲，一個人從樹上掉了下來，仔細一看，卻是" + ob[i]->name() + "。\n", ({me}));
                                        ob[i]->move(this_object());
                                        if (!random(3))
                                        {
                                                qi=query("qi", ob[i]);
                                                if (qi > 200) ob[i]->receive_damage("qi", qi / 2);
                                                else if (qi >= 100) ob[i]->receive_damage("qi", 100);
                                                else if (qi > 0) ob[i]->receive_damage("qi", qi);
                                        }
                                        return 1;
                                }
                        }
                }
        }
        level = me->query_skill("strike", 1);
        exp=query("combat_exp", me);
        qicost = level / 3 + random(level / 3);
        if( query("qi", me) <= qicost )
        {
                write("你太累了，先歇歇吧！\n");
                return 1;
        }
        if (level < 30)
        {
                write("你一掌拍向大樹，大樹卻紋絲不動，你感到十分沮喪。\n");
                return 1;
        }
        if (level > 100)
        {
                write("你一掌拍向大樹，把樹上的果子都震得落到幾丈開外去了。\n");
                return 1;
        }
        me->receive_damage("qi", qicost);
        if (!random(5))
                message_vision("$N一掌拍向大樹，大樹晃了幾晃，$N對于自己的掌法更有自信了。\n", me);
        else
                write( "你一掌拍向大樹，大樹晃了幾晃，你對于自己的掌法更有自信了。\n");
        if ( level * level * level /10 < exp)
                me->improve_skill("strike",query("int", me));
        return 1;
}

int do_climb(string arg)
{
        object me = this_player();

        if (arg != "tree" && arg != "shu" && arg != "dashu" && arg != "up")
                return notify_fail("你要爬什麼？\n");
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙著哪！\n");
        message_vision("$N往手心裡啐了兩口唾沫，運了運氣，順著樹幹爬了上去。\n", me);
        me->move(__DIR__"shushang", 1);
        message("vision", me->name() + "從樹下爬了上來。\n", __DIR__"shushang", ({me}));
        return 1;
}

int valid_leave(object me, string dir)
{
        object room;
        int valid;

        valid = ::valid_leave(me, dir);
        if (valid && room = find_object(__DIR__"shushang"))
                tell_room(room,"透過樹葉的縫隙，你看見"+me->name()+"離開了樹下。\n");
        return valid;
}