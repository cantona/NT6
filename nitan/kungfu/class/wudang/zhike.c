// zhike.c 靈虛

#include <ansi.h>
//#include "daozhang.h"
inherit NPC;
//inherit F_MASTER;

void create()
{
        set_name("靈虛道長", ({ "lingxu daozhang", "lingxu", "daozhang" }));
        set("long", "他是武當山的知客道長，是宋遠橋的弟子。守在山門迎接香客。\n");
        set("gender", "男性");
        set("nickname", "知客道長");
        set("age", 30);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "taoist");
        set("no_get", 1);
        set("no_steal",1);
        set("owner","mud_os");
        set("quest_no_guard",1);

        set("str", 20);
        set("int", 20);
        set("con", 25);
        set("dex", 20);

        set("max_qi", 800);
        set("max_jing", 400);
        set("neili", 500);
        set("max_neili", 500);

        set("combat_exp", 7500);
        set("score", 1000);

        set_skill("force", 80);
        set_skill("yinyun-ziqi", 40);
        set_skill("dodge", 80);
        set_skill("strike", 40);
        set_skill("wudang-zhang", 40);
        set_skill("parry", 80);
        set_skill("sword", 80);
        set_skill("wudang-jian", 80);
        set_skill("taoism", 20);

        map_skill("parry", "wudang-jian");
        map_skill("sword", "wudang-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("strike", "wudang-zhang");

        set("chat_chance",2);
        set("chat_msg", ({
                 "靈虛道長說道：我武當地靈人傑，香火鼎盛，普天下的人都來朝拜敬香。\n",
                 "靈虛道長說道：玄岳門乃武當出入門戶，我等一定要精心守衛(volunteer)，不可絲毫懈殆。\n"
                 "靈虛道長說道：香火練制不易，不能隨便與人，虔誠奉獻者方能得之。\n",
                 "靈虛道長說道：我武當地靈人傑，香火鼎盛，普天下的人都來朝拜敬香。\n",
                 "靈虛道長說道：聽說山門前的鬆林裡有異果，有砍樹的道士進去找，就再也沒有出來。\n",
        }));

        set("inquiry", ([
                "香火" : "香火練制不易，不能隨便與人，虔誠奉獻者方能得之。",
                "進香" : "進香？童言無忌！童言無忌！要說敬香才是！",
                "敬香" : "殿堂的香火能綿延不斷，都因為我武當弟子和山外香客及時敬奉。",
                "虔誠奉獻" : "虔誠奉獻就是主動多捐獻香火錢，多作義工。",
                "敬奉" : "虔誠奉獻就是主動多捐獻香火錢，多作義工。",
                "鬆林" : "武當鬆林在山門前面。",
                "柏林" : "武當柏林就在遇真宮後。",
                "name" : "我是武當的知客道長，負責守衛山門。",
                "here" : "這裡是武當的玄岳門，一直南上就可到紫霄宮。",
                "rumors" : "聽說山門前的鬆林裡有異果，不知是真是假。"
                "可是有砍樹的道士進去找，就再也沒有出來。\n",
                "守衛" : "我這裡的工作就是守衛(volunteer)山門，每次守一天。\n",
                "工作" : "我這裡的工作就是守衛(volunteer)山門，每次守一天。\n",
                "幹活" : "我這裡的工作就是守衛(volunteer)山門，每次守一天。\n",
        ]));
        create_family("武當派", 3, "弟子");

        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"dao-cloth")->wear();
        carry_object(CLOTH_DIR"dao-shoe")->wear();
}

void init()
{
        object me = this_player();
        ::init();
        if (environment() != load_object("/d/wudang/xuanyuegate") ) return;

        add_action("do_volunteer","volunteer");

        if( !is_fighting() && living(this_object()))
        {
                if(interactive(me))
                {
                        remove_call_out("greeting");
                        call_out("greeting", 1, me);
                }
        }
}

void greeting(object ob)
{
        mapping myfam;
        if (environment(this_object())!=environment(ob))
        return;
        myfam=query("family", ob);
        if ( myfam && myfam["family_name"] == "武當派" )
                command("say這位道"+((query("gender", ob) == "女性")?"姑":"兄")+"辛苦了！");
        else if( query("title", ob) == "武當道童" )
                say("靈虛道長對"+ob->name()+"說道：這位"+RANK_D->query_respect(ob)+"還要繼續努力啊！\n");
        else if( query("shen", ob)>-100 )
                say("靈虛道長作了個揖道：這位" + RANK_D->query_respect(ob) + "請了，歡迎來到武當山！\n");
        else        say("靈虛道長「唰」抽出長劍：這位" + RANK_D->query_respect(ob) + "滿臉殺氣，如果不是來武當敬香就請回吧！\n");
}

int do_volunteer()
{
        object me = this_player();
        object *ob;
        object *obs;
        int i;

        if( query_temp("in_guard", me) )
                return notify_fail("知客道長對你說：你專心守好山門，別想打兩份工。\n");

        if( query("family/family_name", me) != "武當派" )
        {
                message_vision("知客道長大喝一聲：作為別派的弟子，我怎麼放心你呢？！\n", me);
                return 1;
        }

        if( query("short", environment(this_object())) != "玄岳門" )
        {
                message_vision("哎呀，我怎麼在這裡呀，等我先回去。\n", me);
                return 1;
        }

        if( query("combat_exp", me) >= 400000 )
         {
                message_vision("知客道長一揖道：怎敢煩勞壯士做這粗活。\n", me);
                return 1;
        }

        ob = all_inventory(environment(me));
        obs = filter_array(ob,
                           (: interactive($1) &&
                           $1 != $(me) &&
                           query_temp("in_guard", $1) && 
                           environment($1) :));

        if (sizeof(obs) > 3)
                return notify_fail("知客道長對你說：已經有不少人守山門了，你一會再來吧。\n");

        tell_room(environment(me),query("name", me)+"開始在武當山門值守。\n");
        set("qi", 30000);
        set("jing", 30000);
        set_temp("in_guard", 1, me);

        // remove_call_out("end_guard");
        call_out("end_guard", 150, me);
        // remove_call_out("clone_meng");
        call_out("clone_meng", 30, me);
        return 1;
}

void clone_meng(object me)
{
        object ob;
        int maxskill;
        int maxexp;
        int maxqi;

        if (! me) return;

        if( !query_temp("in_guard", me) )
                return;

        maxskill = me->query_skill("force", 1);
        maxqi=query("eff_qi", me);
        maxexp=query("combat_exp", me);

        if( query("short", environment(me)) != "玄岳門" )
        {
                tell_object(me,"你在武當山門值守走開，失敗。\n");
                call_out("end_guard", 0, me);
                return;
        }

        tell_room(environment(me), "山下突然沖上來一伙蒙面大漢。\n");

        ob = new("/d/wudang/npc/mengmian.c");
        if (! me->is_ghost())
        {
                ob->move(environment(me));
        }
        set("combat_exp", maxexp, ob);
        if (maxskill > 5 && maxexp > 50000)
        {
                ob->set_skill("kuang-jian", maxskill*2/3);
                ob->set_skill("sword", maxskill*2/3);
                ob->set_skill("parry", maxskill*2/3);
                ob->set_skill("unarmed", maxskill*1/2);
                ob->set_skill("dodge", maxskill*2/3);
        } else
        {
                ob->set_skill("kuang-jian", 5);
                ob->set_skill("sword", 5);
                ob->set_skill("parry", 5);
                ob->set_skill("unarmed", 5);
                ob->set_skill("dodge", 5);
        }
        set("qi", maxqi, ob);
        set("volunteer_owner",query("id",  me), ob);

        set("title", HIR"蒙面大漢"NOR, ob);
        ob->kill_ob(me);
        message_vision(HIR "\n$N對著$n大叫一聲，殺啊!。\n" NOR, ob, me);
        tell_room(environment(me), "山下突然沖上來一伙蒙面大漢。\n");

        ob = new("/d/wudang/npc/mengmian.c");
        if (! me->is_ghost())
        {
                ob->move(environment(me));
        }

        set("combat_exp", maxexp, ob);
        if (maxskill > 5 && maxexp > 50000)
        {
                ob->set_skill("kuang-jian", maxskill);
                ob->set_skill("sword", maxskill);
                ob->set_skill("parry", maxskill);
                ob->set_skill("unarmed", maxskill);
                ob->set_skill("dodge", maxskill);
        } else
        {
                ob->set_skill("kuang-jian", 5);
                ob->set_skill("sword", 5);
                ob->set_skill("parry", 5);
                ob->set_skill("unarmed", 5);
                ob->set_skill("dodge", 5);
         }
        set("qi", maxqi, ob);
        set("volunteer_owner",query("id",  me), ob);

        set("title", HIR"蒙面大漢"NOR, ob);
        ob->kill_ob(me);
        me->kill_ob(ob);
        message_vision(HIR "\n$N對著$n大叫一聲，殺啊!。\n" NOR, ob, me);

        call_out("clone_meng", 100, me);
}

void end_guard(object me)
{
        object *enemys;
        int i;
        if (! me) return;

        remove_call_out("clone_meng");
        if( !query_temp("in_guard", me))return ;

        delete_temp("in_guard", me);

        if( query("short", environment(me)) == "玄岳門" )
        {
                addn("family/gongji", random(8)+4, me);
                addn("combat_exp", random(220)+120, me);
                if( query("potential", me)>me->query_potential_limit() )
                        addn("potential", 1, me);
                else
                        addn("potential", random(50)+80, me);

                tell_room(environment(me),query("name", me)+"在武當山門值守期已滿。\n");
                tell_object(me, "你在武當山門值守期已滿。\n");
        } else
        {
                tell_room(environment(me),query("name", me)+"在武當山門值守走開，失敗。\n");
                tell_object(me, "你在武當山門值守走開，失敗。\n");
        }
        enemys = children("/d/wudang/npc/mengmian");
        enemys = filter_array(enemys, (: query("volunteer_owner", $1) == $(query("id",me)) :));
        if (sizeof(enemys) > 0)
        {
                for (i = 0; i < sizeof(enemys); i++)
                {
                        if (enemys[i]->is_fighting())
                        {
                                enemys[i]->remove_all_killer();
                                tell_room(environment(enemys[i]), HIW "只見" + enemys[i]->name()
                                        + "突然面色一變，迅速攻出幾招，跳出戰圈轉身逃了。\n");
                        }
                        else {
                                tell_room(environment(enemys[i]), HIW "只見" + enemys[i]->name()
                                        + "掐值一算，突然臉色大變，急急忙忙地逃走了。\n");
                        }
                        destruct(enemys[i]);
                }
        }
}

void die()
{
        object *me, *enemys;
        int i;

        me = all_inventory(environment());

        for (i = 0; i < sizeof(me); i ++)
                delete_temp("in_guard", me[i]);

        enemys = children("/d/wudang/npc/mengmian");
        if (sizeof(enemys) > 0)
        {
                for (i = 0; i < sizeof(enemys); i++)
                {
                        if (enemys[i]->is_fighting())
                        {
                                enemys[i]->remove_all_killer();
                                tell_room(environment(enemys[i]), HIW "只見" + enemys[i]->name()
                                        + "突然面色一變，迅速攻出幾招，跳出戰圈轉身逃了。\n");
                        }
                        else {
                                tell_room(environment(enemys[i]), HIW "只見" + enemys[i]->name()
                                        + "掐值一算，突然臉色大變，急急忙忙地逃走了。\n");
                        }
                        destruct(enemys[i]);
                }
        }
        ::die();
}

int accept_object(object who, object ob)
{
        object obn, wage;
        int i, j;
        string *wanted;
        if( query("money_id", ob) && ob->value() >= 100*query("age", who) )
        {
                if( (query("family/family_name", who)) == "武當派" )
                        tell_object(who,"靈虛道長哈哈一笑：既然道"+((query("gender", who) == "女性")?"姑":"兄")+"如此誠心向道，我這有新制香火一枝，請拿去貢奉吧。\n");
                else
                        tell_object(who, "靈虛道長哈哈一笑：既然施主如此誠心向道，我這有新制香火一枝，請施主拿去貢奉吧。\n");
                obn = new("/d/wudang/obj/incense");
                obn->move(who);
                return 1;
        }
        else
                if( query("money_id", ob) )
                {
                        if( (query("family/family_name", who)) == "武當派" )
                                tell_object(who,"靈虛道長對你讚嘆道：武當山香火鼎盛，全靠象道"+((query("gender", who) == "女性")?"姑":"兄")+"你這樣捐獻香火啊！\n");
                        else
                                tell_object(who, "靈虛道長對你讚嘆道：武當山香火鼎盛，全靠象您這樣的虔誠香客啊！\n");
                        return 1;
                }
        return 0;
}
