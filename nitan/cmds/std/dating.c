// skills.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob, man, *all;
        mapping skl, lrn, map;
        string *sname, *mapped;
        int sp, dp;
        int i, cost;
        int sklvl;
        int precise;

        seteuid(getuid());

        all = all_inventory(environment(me));
        for (i = 0; i < sizeof(all); i++)
        {
                if (living(all[i]) && ! userp(all[i]) &&
                    query("can_speak", all[i]) && 
                    !query("not_living", all[i]) )
                {
                        man = all[i];
                        break;
                }
        }

        if( query("family/family_name", me) != "丐幫" )
                return notify_fail("只有乞丐才能打探別人的技能！\n");

        if (! objectp(man))
                return notify_fail("周圍沒人能幫你去了解別人的技能！\n");

        if ((sklvl = me->query_skill("checking", 1)) < 10)
                return notify_fail("你的打探本領尚未純熟，無法"
                                   "了解別人的技能！\n");

        if (! arg)
                return notify_fail("你要打聽誰的技能？\n");

        if (present(arg, environment(me)))
                return notify_fail("你要打聽的人就在邊上，在這裡"
                                   "問不大妥當吧？\n");

        ob = find_player(arg);
        if (! ob) ob = find_living(arg);
        if (! ob) return notify_fail("你要打聽誰的技能？\n");

        if (ob == me)
                return notify_fail("你沒這麼笨吧，要別人"
                                   "告訴你自己的技能？\n");

        cost=query("max_jing", me)/(sklvl/10)-10;
        if (cost < 40) cost = 30 + random(10);

        if( query("jing", me) <= cost )
                return notify_fail("現在你太累了，無法去打聽別人的技能。\n");
        me->receive_damage("jing", cost);

        tell_object(me, "你走上前去，小心翼翼地向" + man->name() +
                        "打聽關于" + ob->name() + "的情況 ...\n");
        message("vision", "只見" + me->name() + "陪著笑臉跟" +
                          man->name() + "說著話，好象在打聽些什麼。\n", 
                environment(me), ({ me, man }) );

        sp = me->query_skill("checking") * 10 + 
             query("jing", me)+query("jing", man);
        dp=query("jing", ob)*2;
        
        if (random(sp) < random(dp))
                return notify_fail(man->name() + "搖了搖頭，說道：這事"
                                   "我可不清楚，" + RANK_D->query_respect(me) +
                                   "還是去向別人打聽一下吧！\n");

        skl = ob->query_skills();
        if (! sizeof(skl))
        {
                write(man->name() + "告訴你： " + ob->name() +
                      "目前並沒有學會任何技能。\n");
                return 1;
        }
        write(man->name() + "告訴你： " + ob->name() +
              "目前所學過的技能：\n\n");
        sname  = sort_array(keys(skl), (: strcmp :));
        
        map = ob->query_skill_map();
        if (mapp(map)) mapped = values(map);
        if (! mapped) mapped = ({});

        lrn = ob->query_learned();
        if (! mapp(lrn)) lrn = ([]);
        
        i = random(sizeof(skl));

        // 這個是打聽到的技能的精確度
        precise = 6000 / sklvl;

        write(sprintf("%s%s%-40s" NOR " - %3d\n", 
                (lrn[sname[i]] >= (skl[sname[i]] + 1) * (skl[sname[i]] + 1)) ? HIM : "",
                (member_array(sname[i], mapped) == -1? "  " : "□"),
                to_chinese(sname[i]) + " (" + sname[i] + ")",
                (skl[sname[i]] + precise / 2) / precise * precise));

        if (me->can_improve_skill("checking"))
                me->improve_skill("checking",random(query("int", me)));
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : check|dating [<某人>]

這個指令可以讓你打聽別人所學過的技能。

你也可以指定一個和你有師徒關系的對象，用 skills|cha 可以查知對方的技能狀況。

此命令為丐幫弟子專用，並需學習相應的技能。如果技能不高，那麼
打聽出來的可能會有一些出入。

HELP );
    return 1;
}
