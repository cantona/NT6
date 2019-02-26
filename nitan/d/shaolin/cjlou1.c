inherit ROOM;

void create()
{
        set("short", "藏經閣二樓");
        set("long", @LONG
千餘年來少林寺執中原武林之牛耳，自達摩老祖以下，歷代人材
輩出。其中有不少高僧遺著留存，彙集至今，終成名震天下的少林七
十二絕藝。少林精華，盡集於此。二樓四面開窗，確保通風。中間排
列着五排大書架。四周則陳列矮几，以供閲讀。幾位老僧手執經卷，
正在閉目凝思。房樑(fangliang)上滿是灰塵。
LONG );
        set("exits", ([
                "down" : __DIR__"cjlou",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/hui-zhen" : 1,
                "/clone/book/wuji1" : 1,
                "/clone/book/wuji2" : 1,
                "/clone/book/wuji3" : 1,
        ]));
        set("item_desc", ([ /* sizeof() == 1 */ 
                "房樑" : "房樑離地面越有一丈多高。看看能不能跳(jump)上去。\n", 
        ])); 
        setup();

        if (random(5) == 0)
                "/clone/book/wuji4"->move(this_object());
}

void init()
{
        add_action("do_hit", "hit");
        add_action("do_jump", "jump");
}

int do_hit(string arg)
{
        object ob, me = this_player();
        
        if ( arg == "huizhen" || arg == "zunzhe" || arg == "huizhen zunzhe" ) {
                ob = present("huizhen zunzhe", environment(me));
                ob->kill_ob(me);
                me->fight_ob(ob);
                tell_object(me,"你突然天旋地轉，冥冥中似乎有股力量在操縱你的命運!\n");
                me->unconcious();
        
                return 1;
        }

        return 0;
}

int do_jump(string arg)
{
        string dir;
        object me=this_player();

        if( !arg || arg=="" ) 
        {
                write("你想跳哪裏去？\n");
                return 1;
        }

        if( arg=="fangliang" ) {
                           write("你深深地吸了一口氣,猛然躍起......\n");
                if((int)me->query_skill("dodge",1)>=50)
                          {write("你一式「孤騖落日」，全身筆直，拔地而起，在半空中一轉，已落到房樑上。\n");
                me->move(__DIR__"liang");
                return 1;}
                write("“啪”的一聲你腦袋撞到了房樑,又跌回原處，摔了個四腳朝天。\n");
                addn("jing", -100, me);
                addn("qi", -100, me);
                addn("eff_qi", -100, me);
                me->improve_skill("dodge", random(30));
                me->unconcious();
                return 1;
        }
}

int valid_leave(object me, string dir)
{
        object *ob;
        int i;

        if (dir != "down" ||
            ! present("huizhen zunzhe", environment(me)))
                return ::valid_leave(me, dir);

        ob = deep_inventory(me);
        for (i = 0; i < sizeof(ob); i++)
                if (ob[i]->id("shaolin wuji")) 
                        return notify_fail("慧真説道：武功祕籍只許在藏經閣"
                                           "內研習，不得攜帶外出！\n");
        return ::valid_leave(me, dir);
}
