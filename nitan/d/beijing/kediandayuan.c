inherit ROOM;

void create()
{
        set("short", "客店後院");
        set("long", @LONG
這裡客店後院。一陣陣打鬥之聲從東面的廂房 (room) 中傳來，
其中夾雜著一個女子的聲音。房門的板壁(wall)不住的震動，似乎客
房四周的板壁都要被刀風掌力震坍一般。南面是客店大門。
LONG );
        set("no_sleep_room",1);
        set("exits", ([
                "east" : "/d/beijing/kefang",
                "south" : "/d/beijing/fukedian",
        ]));
        set("item_desc", ([
                "wall" : "\n這是一堵木牆，板壁不過一寸來厚，被震得搖搖晃晃。\n",
                "room" :
"\n你往房中望去，只見幾個喇嘛手持戒刀，圍著一白衣女尼拼命砍殺，\n"+
"只是給白衣女尼的袖力掌風逼住了，欺不近身。但那白衣女子頭頂已冒\n"+
"出絲絲白氣，顯然已盡了全力。她只一條臂膀，再支持下去恐怕難以抵敵。\n"+
"地上斑斑點點都是血跡。\n",
        ]));
	set("coor/x", -2810);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        int i;
        object room;

        if (dir != "east" )
                return ::valid_leave(me, dir);

        room = find_object(query("exits/east"));
        if (! room) room = load_object(query("exits/east"));
        if (room && present("la ma", room) && present("dubi shenni", room))
        {
                if ((int)me->query_skill("force") < 100) 
                        return notify_fail("\n你一步踏進客房，突覺一股力道奇"
                                           "大的勁風激撲出來，將你一撞，\n"
                                           "你登時立足不穩，騰騰騰到退三步，"
                                           "一交坐倒。\n");
                me -> receive_damage ("qi",50) ;
                me -> receive_wound  ("qi",50) ;
        }
        return ::valid_leave(me, dir);
}

void init()
{
        add_action("do_thrust","thrust");
        add_action("do_thrust","ci");
        add_action("do_thrust","stab");
}

int do_thrust(string arg)
{
        object room, me,man;
        object weapon;

        if (! arg || arg != "wall" ) return notify_fail("你要刺什麼？\n");

        weapon=query_temp("weapon", this_player());
        if (! weapon ||
            (query("skill_type", weapon) != "sword" && 
             query("skill_type", weapon) != "blade") )
                return notify_fail("不用刀劍恐怕不行吧！\n");

        if (!( room = find_object("/d/beijing/kefang")))
                room = load_object("/d/beijing/kefang");

        if (man = present("la ma", room))
        {
                message_vision("\n$N走到牆邊，抽出兵刃，對準木板狠"
                               "狠地一戳。\n",this_player());

                if( query_temp("apply/damage", this_player())<100 )
                {
                        message_vision("結果$N篤的一聲，兵刃插入寸許，再也"
                                       "刺不進半分。\n",this_player());
                        return 1;
                }

                message_vision("只聽噗的一聲，匕首輕輕穿過木板，房中立時傳"
                               "來一聲慘叫。\n",this_player());
                message("vision", "忽然一個喇嘛慘叫一聲倒了下去。\n",room );
                man->die();             
        }
        else return notify_fail("屋裡沒有喇嘛，不用再殺了。\n");

        return 1;
}