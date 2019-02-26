// abandon.c

#include <ansi.h>

inherit F_CLEAN_UP;

int help();
int main(object me, string arg)
{
        mapping smap, pmap;
        int skill_lvl, lvl, i;
        int jingcost;
        string skill;
        string name;
        int level;
        int lost;

        if (! arg || arg == "")
                return help();

        if (sscanf(arg, "%s to %d", skill, lvl) != 2)
                return help();

        if (me->is_fighting())
                return notify_fail("你正忙着打架呢，哪有時間做這種事？\n");

        if (me->is_busy())
                return notify_fail("你正忙，沒法靜下心來。\n");

        jingcost=query("int", me)+random(query("int", me));
        if( jingcost>query("jing", me) )
                return notify_fail("你無法集中精力。\n");

        if (skill == "exp")
        {
                lost=query("combat_exp", me);
                if (lost < 100)
                        return notify_fail("你發現自己現在對武學簡直就是一無所知。\n");

                if (lvl > lost || lvl < 0)
                        return notify_fail("你發現自己現在對武學理解還沒有那麼高。\n");

                if (lvl == lost)
                        return notify_fail("你是不是頭腦進水了，現在還用放棄嗎？\n");

                level = sqrt3(lvl/100) * 10 + 1;
                while ((level + 1)*(level + 1)*(level + 1) <= lvl*10 )
                        level++;

                tell_object(me, HIR "你將放棄EXP到 " + lvl + " 點，僅可支持 " +
                                chinese_number(level) + " 級武學技能。\n\n" NOR);

                tell_object(me, "請務必考慮清楚，確定的話請輸入您的管理密碼或普通密碼：");
                input_to("check_password", 1, me, skill, lvl);
                return 1;

                message("vision", me->name() + "坐下在凝神思索什麼。\n",
                        environment(me), me);
                tell_object(me, "你不再想拳腳兵器輕功內功，只是一門心思忘記武功。\n");
                me->start_busy(3 + random(5));
                if( random(query("int", me))>15 )
                {
                        tell_object(me, "可是你發現自己似乎記性太好，沒有半點效果。\n");
                        return 1;
                }

                // lost = random(lost / 100) + 1;
                // addn("combat_exp", -lost, me);
                set("combat_exp", lvl, me);
                switch (random(6))
                {
                case 0:
                        tell_object(me, HIR "你又想起了很多温馨"
                                    "的往事，不由得沉浸其中。\n" NOR);
                        break;
                case 1:
                        tell_object(me, HIR "你似乎又看到了遙遠"
                                    "的童年，一時忘卻了塵世間的煩惱。\n" NOR);
                        break;
                case 2:
                        tell_object(me, HIR "你黯然一聲長歎，只覺"
                                    "得自己為了武學荒廢一生，實在無謂。\n" NOR);
                        break;
                case 3:
                        tell_object(me, HIR "你心如止水，所有的"
                                    "武功都彷彿離自己遠去了。\n" NOR);
                        break;
                case 4:
                        tell_object(me, HIR "你抬頭仰望天空，發"
                                    "現它明亮透析，説不出的嬌媚，令你身心俱化。\n" NOR);
                        break;
                default:
                        tell_object(me, HIR "你腦海中晃過當年無"
                                    "數刻苦修煉的日子，不由得暗自苦笑。\n" NOR);
                        break;
                }

                // UPDATE_D->check_user(me);
                return 1;
        }

        smap = me->query_skill_map();
        pmap = me->query_skill_prepare();

        name = to_chinese(skill);
        if (name[0] < 160) name = "這項技能";
        skill_lvl = (int)me->query_skill(skill, 1);

        if (! skill_lvl)
        {
                me->delete_skill(skill);
                write("好了。\n");
                return 1;
        }

        if (lvl > skill_lvl || lvl < 0)
                return notify_fail("你發現自己現在對該項武功理解還沒有那麼高。\n");

        if (lvl == skill_lvl)
                return notify_fail("你是不是頭腦進水了，現在還用放棄嗎？\n");

        tell_object(me, HIR "你將放棄技能 " + name + " 至 " + chinese_number(lvl) + " 級。\n\n" NOR);

        tell_object(me, "請務必考慮清楚，確定的話請輸入您的管理密碼或普通密碼：");
        input_to("check_password", 1, me, skill, lvl, name, smap, pmap);
        return 1;

        me->start_busy(1+random(query("int", me)/7));
        if( random(query("int", me))>24 )
                return notify_fail("你集中精力不再想" + name + "，結果發現毫無結果。\n");

        // skill_lvl = random(skill_lvl);
        if (lvl < 1)
        {
                for (i = sizeof(smap)-1; i >= 0; i --)
                        if ((string)smap[keys(smap)[i]] == skill)
                                me->map_skill(keys(smap)[i]);

                for (i = sizeof(pmap)-1; i >= 0; i -- )
                        if ((string) values(pmap)[i] == skill)
                                me->prepare_skill(keys(pmap)[i]);

                SKILLS_D->remove_id_from_abandon(me, skill);
                me->delete_skill(skill);
                me->reset_action();
                write("你集中精力不再想" + name + "，結果終於將它徹底忘記了。\n");
        } else
        {
                me->set_skill(skill, lvl);
                write("你集中精力不再想" + name + "，結果有所效果。\n");
        }
        return 1;
}

varargs void check_password(string passwd, object me, string skill, int lvl, string name, mapping smap, mapping pmap)
{
        int i;
        object link_ob;
        string old_pass;

        link_ob=query_temp("link_ob", me);
        old_pass=query("ad_password", link_ob);
        if (! stringp(old_pass) || crypt(passwd, old_pass) != old_pass)
        {
                old_pass=query("password", link_ob);
                if (! stringp(old_pass) || crypt(passwd, old_pass) != old_pass)
                {
                        write(HIR "密碼錯誤！請注意，放棄武學必須輸入管理密碼或普通密碼。\n");
                        return;
                }
        }

        if (skill == "exp")
        {
                message("vision", me->name() + "坐下在凝神思索什麼。\n",
                        environment(me), me);
                tell_object(me, "你不再想拳腳兵器輕功內功，只是一門心思忘記武功。\n");
                me->start_busy(3 + random(5));
                /*
                if( random(query("int", me))>15 )
                {
                        tell_object(me, "可是你發現自己似乎記性太好，沒有半點效果。\n");
                        return;
                }
                */

                set("combat_exp", lvl, me);
                switch (random(6))
                {
                case 0:
                        tell_object(me, HIR "你又想起了很多温馨"
                                    "的往事，不由得沉浸其中。\n" NOR);
                        break;
                case 1:
                        tell_object(me, HIR "你似乎又看到了遙遠"
                                    "的童年，一時忘卻了塵世間的煩惱。\n" NOR);
                        break;
                case 2:
                        tell_object(me, HIR "你黯然一聲長歎，只覺"
                                    "得自己為了武學荒廢一生，實在無謂。\n" NOR);
                        break;
                case 3:
                        tell_object(me, HIR "你心如止水，所有的"
                                    "武功都彷彿離自己遠去了。\n" NOR);
                        break;
                case 4:
                        tell_object(me, HIR "你抬頭仰望天空，發"
                                    "現它明亮透析，説不出的嬌媚，令你身心俱化。\n" NOR);
                        break;
                default:
                        tell_object(me, HIR "你腦海中晃過當年無"
                                    "數刻苦修煉的日子，不由得暗自苦笑。\n" NOR);
                        break;
                }

                UPDATE_D->check_user(me);
                return;
        }

        me->start_busy(1+random(query("int", me)/7));
        /*
        if( random(query("int", me))>24 )
        {
                tell_object(me, "你集中精力不再想" + name + "，結果發現毫無結果。\n");
                return;
        }
        */

        if (lvl < 1)
        {
                for (i = sizeof(smap)-1; i >= 0; i --)
                        if ((string)smap[keys(smap)[i]] == skill)
                                me->map_skill(keys(smap)[i]);

                for (i = sizeof(pmap)-1; i >= 0; i -- )
                        if ((string) values(pmap)[i] == skill)
                                me->prepare_skill(keys(pmap)[i]);

                SKILLS_D->remove_id_from_abandon(me, skill);
                me->delete_skill(skill);
                me->reset_action();
                write("你集中精力不再想" + name + "，結果終於將它徹底忘記了。\n");
        } else
        {
                int add;

                add=query_temp("apply/add_skill", me);
                lvl -= add;
                if (lvl < 1)
                {
                        tell_object(me, "你如果真的想全部放棄" + name + "請重新指定數字為零。\n");
                        return;
                }
                me->set_skill(skill, lvl);
                write("你集中精力不再想" + name + "，結果有所效果。\n");
        }
        return;
}

int help()
{
        write(@TEXT
指令格式：abandon|fangqi <技能名稱> | exp to <數值>

放棄你的實戰經驗或是某一項你所學過的技能到指定的數值，成功率
和你的天賦有關，只有能夠休息的地方才能夠靜下心來忘記武功。

有時候因為武功相剋或者你不再打算在某項技能上再下功夫，就可以
使用這條指令放棄它。
TEXT );
        return 1;
}
