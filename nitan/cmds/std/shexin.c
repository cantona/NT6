// shexin.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string dest, cmd, verb;
        object ob;
        mapping fam;

        seteuid(getuid());

        if( query("no_ansuan", environment(me)) )
                return notify_fail("這裏禁止戰鬥。\n");
        if( query("no_fight", environment(me)) )
                return notify_fail("這裏禁止戰鬥。\n");
        if( me->is_busy() )
                return notify_fail("你上一個動作還沒有完成！\n");
        if( me != this_player() ) return 0;
        me = this_player();
        if( (!(fam=query("family", me)) || fam["family_name"] != "雪山寺") )
                return notify_fail("只有雪山寺弟子才能行使懾心術！\n");
        if (me->query_skill("necromancy",1) < 40)
                return notify_fail("你的降伏法還太淺薄了，沒法行使懾心術。\n");

        if( !arg || sscanf(arg, "%s to %s", dest, cmd) != 2 )
                return notify_fail("指令格式: shexin <某人> to <指令>\n");

//        if (!ob = get_object( dest ) )
        if( !objectp(ob = present(dest, environment(me))))
                return notify_fail("找不到" + dest + "。\n");
        if( !living(ob) || query_temp("noliving", ob) )
                return notify_fail("這個物件不能被懾心。\n");
        if( query("id", ob) == "renzhi" )
                return notify_fail("你對"+ob->name() + "行使懾心術可不成。\n");
        if( userp(me) && query("owner", ob) && query("id", me) != query("owner", ob) )
                        return notify_fail("不是你要抓的人，湊什麼熱鬧！\n");                                                
        notify_fail("此人來頭不小，還是少惹為妙。\n");
        if (!userp(ob) && !ob->accept_hit(me)) return 0;                

        if( query("no_get", ob) || query("no_get_from", ob) )
                return notify_fail("你對"+ob->name() + "行使懾心術可不成。\n");
        if( wizardp(ob) ) return notify_fail("巫師不能被你懾心。\n");
        if( wiz_level(me) < wiz_level(ob) )
                return notify_fail("你沒法對" + ob->name() + "行使懾心術。\n");
message_vision("
$N的一對眼睛半眯着，只如兩道細縫，但細縫中瑩然有光，眼神甚是清朗。
$n微覺不妥，要想轉頭避開$N的眼光，可是一雙眼睛竟似被$N的目光吸住了，
不由自主的凝視着他。\n", me, ob);
        if( random(me->query_skill("necromancy",1)) < random(ob->query_skill("force",1)))
        {
                message_vision("突然$n猛地一陣清醒，於是，$n大喝一聲：你活膩了，敢來對我施懾心術？\n", me, ob);
                if( query("age", ob)>17)ob->kill_ob(me);
                return 1;
        }
        if (strsrch(cmd, "give ") >= 0)
        {
                message_vision("於是，$n迷迷糊糊也不知道是遞了些什麼給$N。\n", me, ob);
        }
        else
        {
                if (strsrch(cmd, "go ") >= 0)
                {
                        if( !userp(ob) )
                                return notify_fail("你只能對玩家行使懾心術。\n");
                        message_vision("結果，$n迷迷糊糊也不知道怎麼回事就往前摸着走開了。\n", me, ob);
                }
                else
                {
                        if (strsrch(cmd, "follow ") >= 0)
                        {
                                if( !userp(ob) )
                                        return notify_fail("你只能對玩家行使懾心術。\n");
                                message_vision("果然，$n迷迷糊糊地就跟在$N的屁股後面走了。\n", me, ob);
                        }
                        else
                                return notify_fail("你只能懾心人家做：give、go和follow。\n");
                }
        }
        me->start_busy(5);

        if( userp(ob) )
                log_file("shexin_player", sprintf("[%s] %s shexin %s to %s\n", ctime(time()), geteuid(me), geteuid(ob), cmd));
        return ob->force_me(cmd);
}

int help(object me)
{
        write(@HELP
指令格式: shexin <某人> to <指令>

    shexin sb to give sth to sb
    shexin sb to follow sb
    shexin sb to go <dir>

    利用懾心術誘惑某人做把身上的東西給你, 或往那裏離開，或者
跟着你。當然你必須是雪山派弟子，且有相當的降伏法修為。
    對方如果內功深厚，而你學藝不精，必然也會招致以牙還牙。當
心！
HELP
        );
        return 1;
}
