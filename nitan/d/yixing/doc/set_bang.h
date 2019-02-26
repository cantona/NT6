// /d/yixing/doc/set_bang.c
// Last Modified by winder on Jul. 12 2002

#ifndef BANGZHONG
#define BANGZHONG  "/d/yixing/npc/bangzhong"
#endif

void set_bang(object owner)
{
        object ob, *obj = ({}), room = environment(owner);

        if( !room ) return;

        ob = new(BANGZHONG);
        set_follower(ob, owner);
        ob->move(room);
        obj += ({ob});

        ob = new(BANGZHONG);
        set_follower(ob, owner);
        ob->move(room);
        obj += ({ob});

        owner->set("follower", obj);
        message("vision", ob->name() + "走了過來。\n", room, ({ob}));
        message_vision("$N對着$n作了個揖，道：幫主老人家辛苦了。\n", ob, owner);
        message_vision("$N點了點頭，道：弟兄們辛苦了。\n", owner);
}


void set_follower(object ob, object owner)
{
        string fam, name;
        string *bc_skills, *weapons;
        int i, exp, level;

        ob->set("owner", owner);
        ob->set_leader(owner);

        fam = owner->query("party/partyname")+owner->query("party/rank");
        ob->set("title", fam);

        exp = (int)owner->query("combat_exp") / 2;
        ob->set("combat_exp", exp);
        level = ceil( pow( to_float(exp) * 10.0, 0.333333) ) * 4 / 5;

        ob->set("max_qi",    level * 8 + 100);
        ob->set("eff_qi",    level * 8 + 100);
        ob->set("qi",        level * 8 + 100);
        ob->set("max_jing",  level * 5 + 100);
        ob->set("eff_jing",  level * 5 + 100);
        ob->set("jing",      level * 5 + 100);
        ob->set("max_neili", level * 6 + 200);
        ob->set("neili",     level * 6 + 200);
        ob->set("max_qi",    level * 5 + 150);
        ob->set("qi",        level * 5 + 150);
        ob->set("jiali",     level / 4);

        ob->set_skill("dodge", level);
        ob->set_skill("force", level);
        ob->set_skill("parry", level);

        bc_skills = keys(unarmed_skills);
        ob->set_skill(bc_skills[random(sizeof(bc_skills))], level);

        i = random(sizeof(info_weapon));
        ob->set_skill(info_weapon[i]["type"], level);

        if( !random(2) ) {
                weapons = info_weapon[i]["weapons"];
                ob->carry_object(weapons[random(sizeof(weapons))])->wield();
        }

        level /= 3;
        ob->set_temp("apply/defense", level);
        ob->set_temp("apply/armor",   level);
        ob->set_temp("apply/damage",  level);
        ob->set_temp("apply/attack",  level);

        ob->set("inquiry/" + fam, fam + "威震江湖，指日可待！！！");
        name = (string)owner->query("name");
        ob->set("inquiry/" + "幫主", "我對我們" + name[0..01] + "幫主的景仰之情腥縑鹹轄嗖瘓");
        ob->set("inquiry/" + name, "這幾個字是你説的嗎？");
        ob->set("inquiry/" + name[0..01] + "幫主", "我對我們" + name[0..01] + "鎦韉木把鮒椋腥縑鹹轄嗖瘓");
}

