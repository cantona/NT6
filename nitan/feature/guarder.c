// guarder.c

#include <ansi.h>

int is_guarder() { return 1; }

int permit_pass(object ob, string dir)
{
        object *inv;
        string fam_name;
        string my_fam;
        string born_fam;
        string msg;
        int i;

        if (! living(this_object()))
                return 1;

        notify_fail("看來" + this_object()->name() + "不打算讓你過去。\n");

        if (query("quest_dg", ob) ||
            query("quest_hs", ob) ||
            query("quest_sn", ob) ||
            query("quest_kh", ob))
                return 1;

        fam_name = query("family/family_name", ob);
        my_fam   = (string) query("family/family_name");
        born_fam = (string) query("born_family", ob);
        if (born_fam == my_fam && fam_name && fam_name != my_fam)
        {
                if (stringp(msg = query("guarder/refuse_home")))
                        message_vision(msg + "\n", this_object(), ob);
                else
                        message_vision("$N冷冷的看了看$n，道：你既然已經入了" +
                                       fam_name + "，還來我們" + my_fam +
                                       "幹什麼？\n", this_object(), ob);
                return 0;
        }

        //if (my_fam != fam_name && my_fam != born_fam)
        if (fam_name && my_fam != fam_name && my_fam != born_fam)
        {
                if (stringp(msg = query("guarder/refuse_other")))
                        message_vision(msg + "\n", this_object(), ob);
                else
                        message_vision("$N伸手攔住$n，道：對不起，不是我們" + my_fam +
                                       "人不得入內！\n", this_object(), ob);
                return 0;
        }

        inv = deep_inventory(ob);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! playerp(inv[i])) continue;
                if ((string) query("family/family_name", inv[i]) != fam_name)
                {
                        if (stringp(msg = query("guarder/refuse_carry")))
                                message_vision(msg + "\n", this_object(), ob);
                        else
                                message_vision("$N對$n喝道：你背的是誰？還不快快放下！\n",
                                               this_object(), ob);
                        return 0;
                }
        }

        return 1;
}

void kill_enemy(object ob)
{
        mixed result;

        mapping *co;
        string startroom;
        object room;
        object coagent;
        object me;
        int i;
        int flag;

        me = this_object();

        /*
        if ((stringp(query("quest_dg/object", ob)) &&
            domain_file(base_name(me)) == domain_file(query("quest_dg/object", ob))) ||
            (stringp(query("quest_hs/object", ob)) &&
            domain_file(base_name(me)) == domain_file(query("quest_hs/object", ob))) ||
            (stringp(query("quest_sn/object", ob)) &&
            domain_file(base_name(me)) == domain_file(query("quest_sn/object", ob))) ||
            (stringp(query("quest_kh/object", ob)) &&
            domain_file(base_name(me)) == domain_file(query("quest_kh/object", ob))))
                return;

        if (me->name(1) == query("quest_dg/name", ob) ||
            me->name(1) == query("quest_hs/name", ob) ||
            me->name(1) == query("quest_sn/name", ob) ||
            me->name(1) == query("quest_kh/name", ob))
                return;
        */

        if (query("quest_dg", ob) ||
            query("quest_hs", ob) ||
            query("quest_sn", ob) ||
            query("quest_kh", ob))
                return;

        if ((int)query("combat_exp", ob) < (int)query("combat_exp", me) / 2)
                return;

        if (!pointerp(co = query("coagents", me)))
                return;

        if (sizeof(co) < 1)
                return;

        if (base_name(environment(me)) != (string)query("startroom", me))
                return;

        message_vision(random(2) ? HIW "\n$N大聲喊道：大家快來幫忙啊！\n\n" NOR :
                                   HIW "\n$N喝道：不好！有人挑上門來了！\n\n" NOR, me);

        if (me->is_master() && me->is_killing(query("id", ob)))
                me->master_accept_kill(ob);

        flag = 0;
        for (i = 0; i < sizeof(co); i++)
        {
                if (! mapp(co[i])) continue;

                startroom = co[i]["startroom"];
                if (! objectp(room = find_object(startroom)))
                {
                        result = catch(room = load_object(startroom));
                        if (! objectp(room))
                        {
                                if (wizardp(this_object()))
                                        write(sprintf("Error to load object:%s\nCatch message:%s\n\n",
                                              startroom, result));
                                continue;
                        }
                }

                if (! objectp(coagent = present(co[i]["id"], room)) &&
                    ! objectp(coagent = present(co[i]["id"], environment())) ||
                    ! coagent->is_coagent() ||
                    coagent == this_object())
                        continue;

                flag += (int)coagent->start_help(environment(), me, ob);
        }

        if (! flag)
                message_vision("結果沒有一個人出來 :)\n", me);
}

int check_enemy(object ob, string type)
{
        mapping myfam;
        object me;

        me = this_object();
        myfam = query("family", ob);
        if (! mapp(myfam) || ! myfam ||
                myfam["family_name"] != query("family/family_name", ob))
        {
                if (type == "fight")
                {
                        message_vision("$N對$n搖搖頭道：我現在沒空。\n\n", me, ob);
                        return 0;
                } else
                {
                        message_vision("$N大喝道，好你個" + RANK_D->query_rude(ob) +
                                       "，活得不耐煩了！來這裏撒野？\n", me, ob);
                        me->kill_ob(ob);
                }
        } else
        switch (type)
        {
        case "hit":
        case "kill":
                message_vision("$N兩眼一瞪，喝道：" + query("name", ob) +
                               "，你是要造反嗎？\n", me, ob);
                me->kill_ob(ob);
                break;

        case "fight":
                if (ob->is_apprentice_of(me))
                        message_vision("$N一瞪$n，怒道：你給我好好練功去！\n", me, ob);
                else
                        message_vision("$N對$n搖搖頭道：找你的師傅比劃去。\n\n", me, ob);
                return 0;
        }

        return 1;
}
