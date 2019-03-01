// /d/yixing/npc/bangzhu2.c
// Last Modified by winder on Jul. 12 2002

#define BANGZHONG2 "/d/yixing/npc/bangzhong2"

inherit NPC;

#include <ansi.h>
#include <localtime.h>

#include "/d/yixing/doc/info_bang.h"

void create()
{
        set_name("草上飛", ({ "bangzhu" }));
        set("gender", "男性");
        set("age", 30);
        set("long", "一個魁梧之極的大漢，臉龐極盡蒼桑，精神卻甚矍鑠。\n");
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("combat_exp", 60000);

        set("max_qi", 300);
        set("max_jing", 200);
        set("max_qi", 600);
        set("max_neili", 200);
        set("neili", 200);

        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("cuff", 80);
/*
        set_skill("ding-force", 80);
        map_skill("force", "ding-force");

        set_skill("wuxingbu", 80);
        map_skill("dodge", "wuxingbu");
*/
        set("no_get", "幫主太重了");

        setup();

        call_out("come_attacker", 10);
}

void init()
{
        ::init();

        add_action("do_ask", "ask");
}

int do_ask(string arg)
{
        object ob, me = this_object();
        string dest, topic;

        if( !arg || sscanf(arg, "%s about %s", dest, topic) != 2 ) {
                write("你要問誰什麼事？\n");
                return 1;
        }

        if( !objectp(ob = present(dest, environment(me))) ) {
                write("這裡沒有這個人。\n");
                return 1;
        }

        if( ob != me )
                return notify_fail("");

        if( !living(me) )
                return 1;

        say(name() + "大怒道：沒見老子生了病煩著呢？滾！！！\n");
        return 1;
}

void come_attacker()
{
        object me = this_object(), helper, *myenemy, room, ob, obj;
        string *bangs;
        int temp, bonus, record;

        if( !(room = environment()) ) {
                destruct(me);
                return;
        }

        if( !(helper = query("helper")) ) {
                say(name() + "自言自語道：此地不可久留，三十六計走為上！\n");
                say(name() + "急急忙忙地離開了。\n");
                destruct(me);
                return;
        }

        if( room != environment(helper) ) {
                say(name() + "自言自語道：此地不可久留，三十六計走為上！\n");
                say(name() + "急急忙忙地離開了。\n");
                destruct(me);
                return;
        }

        if( !is_fighting() &&  living(me)
        &&  explode(base_name(room), "/")[1] == (string)query("dest") ) {
                command("thumb"+query("id", helper));
                if( obj = present("bang ling", helper) ) {
                        bonus=query("job/bonus", obj);
                        bonus=bonus*100000/(100000+query("combat_exp", helper));
                        record = bonus/2 + random(bonus);
                        addn("combat_exp", record, helper);
                        log_file("BangJob",sprintf("%s于%s時因護駕有功得%s經驗點\n",query("name", helper),ctime(time()),chinese_number(record)));
                        bonus /= 4;
                        addn("score", bonus, obj);
                        delete("job", obj);
                }
                say(name() + "雙手一抱拳道：幫主養傷要化一段時間，你好自為之吧！\n");
                say(name() + "揚長而去。\n");
                destruct(me);
                return;
        }

        remove_call_out("come_attacker");
        call_out("come_attacker", 5 + random(5));

        if( query("no_fight", room))return ;

        if( temp = sizeof(myenemy = query_enemy()) ) {
                for(int i = 0; i < temp; i++)
                        if( query("victim", myenemy[i]) == me )
                                return;
        }

        ob = new(BANGZHONG2);
        bangs = keys(info_bang);
        bangs -= ({query("fam")});
        set("title", bangs[random(sizeof(bangs))], ob);
        set("victim", me, ob);

        ob->move(room);
        message("vision",
                ob->name() + "走了過來。\n",
                room, ({ob}));
        ob->set_leader(me);
        message_vision("$N對$n喝道：看你還往哪裡跑？！\n", ob, me);
        ob->kill_ob(me);
        command("!!!");
        me->kill_ob(ob);
}
        
