// /guanwai/famu.c

#include <ansi.h>

inherit ROOM;

int start_work(object me, object ob);
varargs int end_working(object me, object passive);
int working(object me);
int coagent(object me);
int halt_working(object me, object who, int silent);

void create()
{
        set("short", "伐木場");
        set("long", @LONG
這裡是鹿鳴峰西坡下的一片森林，長著許多百年的參天大
樹，筆直挺拔，都是上好的木材，許多人在這裡砍伐(famu)木料，
然後運到中原供達官貴人們建築豪宅。這裡地處深山老林，時常
有兇猛的野獸出沒。
LONG);
        set("exits", ([
                "southup" : __DIR__"luming",
        ]));
        set("outdoors", "changbai");
        setup();
}

void init()
{
        add_action("do_famu", "famu");
        if (find_call_out("call_beast") == -1)
                call_out("call_beast", random(60) + 20);
}

void call_beast()
{
        object ob;
        string beast;
        int n;

        remove_call_out("call_beast");

        if (sizeof(filter_array(all_inventory(), (: interactive :))) < 1)
                return;

        // Call out wovles when player is here
        call_out("call_beast", random(200) + 30);

        if (present("he xiong", this_object()) ||
            present("ye lang", this_object()))
                return;

        switch (random(10))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
                n = 1 + random(4);
                beast = "/clone/quarry/lang2";
                break;
        case 8:
                n = 1;
                beast = "/clone/quarry/xiong";
                break;
        case 9:
                n = 1;
                beast = "/clone/quarry/xiong2";
                break;
        }

        message("vision", "山坳裡面突然串出" + chinese_number(n) +
                query("unit",get_object(beast)) + beast->name() +
                "\n", this_object());
        while (n--)
        {
                ob = new(beast);
                ob->move(this_object());
        }
}

int do_famu(string arg)
{
        object me;
        object ob;
        object old;
        object weapon;

        me = this_player();

        if (! arg || sscanf(arg, "with %s", arg) != 1)
                return notify_fail("你要和誰一起伐木(famu with <sb>)？\n");

        ob = present(arg, this_object());
        if (! ob)
                return notify_fail("這裡沒有這個人可以和你一起伐木。\n");

        if (me == ob)
                return notify_fail("你是不是大腦進水...需要修理？\n");

        if (! living(ob))
                return notify_fail("你怎麼也得等人家醒過來再說吧？\n");

        if( query_temp("job/famu", ob) )
        {
                if (! ob->is_busy())
                        delete_temp("job/famu", ob);
                else
                        return notify_fail("人家現在正在伐木呢。\n");
        }

        if( query_temp("job/famu", me) )
        {
                if (! me->is_busy())
                        delete_temp("job/famu", me);
                else
                        return notify_fail("你現在不是正在伐木嘛？\n");
        }

        if (ob->is_fighting())
                return notify_fail("人家現在正在打架，那有功夫理你？\n");

        if (me->is_fighting())
                return notify_fail("你還是打完了架再說吧。\n");

        if (ob->is_busy())
                return notify_fail("人家現在正忙，沒功夫理你。\n");

        if (me->is_busy())
                return notify_fail("你還是等有空了再說吧。\n");

        if( query("qi", ob)<200 )
                return notify_fail("人家氣力不加，還是算了吧。\n");

        if( query("qi", me)<200 )
                return notify_fail("你現在氣息不夠，還是養足了力氣再說吧。\n");

        if (ob->query_str() < 30)
                return notify_fail("看人家那副模樣不像是能幹這種重活的人。\n");

        if (me->query_str() < 30)
                return notify_fail("你的膂力不夠，幹不了這種重活。\n");

        if( query_temp("pending/job_coagent", ob) == me )
        {
                delete_temp("pending/job_coagent", ob);
                return start_work(me, ob);
        }

        if( objectp(old=query_temp("pending/job_coagent", me)) )
        {
                if (old == ob)
                        return notify_fail("你已經向別人提出要求了，可是人家還沒有答應。\n");

                tell_object(old, me->name() + "改變了主意不想和你一同伐木了。\n");
                tell_object(me, "你改變了主意不想和" + old->name() + "一同伐木了。\n");
        }

        set_temp("pending/job_coagent", ob, me);
        message_vision("$N對$n熱情道：“來吧，" + RANK_D->query_respect(ob) +
                       "，咱們一同伐木如何？”\n", me, ob);
        tell_object(ob, YEL + me->name() + "邀請你一同伐木，你如果"
                    "願意就一起幹(famuwith"+query("id", me)+")吧。\n"NOR);
        return 1;
}

int start_work(object me, object ob)
{
        object weapon, hand;
        object swap;

        hand=query_temp("handing", me);
        if (! objectp(hand) || ! hand->is_saw())
        {
                swap = me;
                me = ob;
                ob = swap;
                hand=query_temp("handing", me);
        }

        if (! objectp(hand) || ! hand->is_saw())
                return notify_fail("你們倆誰都沒有拿鋸，怎麼伐木？\n");

        if( (!objectp(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "axe") && 
            (!objectp(weapon=query_temp("weapon", ob)) || query("skill_type", weapon) != "axe") )
                return notify_fail("你們沒有斧頭，這活幹不完啊！\n");

        set_temp("job/famu", 1, me);
        set_temp("job/step", 1, me);
        set_temp("job/coagent", ob, me);
        set_temp("job/famu", 1, ob);
        set_temp("job/step", 1, ob);
        set_temp("job/coagent", me, ob);
        me->start_busy((: working :), (: halt_working :));
        ob->start_busy((: coagent :), (: halt_working :));
        tell_object(me, "你和" + ob->name() + "開始伐木。\n");
        tell_object(ob, "你和" + me->name() + "開始伐木。\n");
        return 1;
}

private varargs int end_working(object me, object passive)
{
        object coagent;

        if( !query_temp("job/famu", me) )
                return 0;

        coagent=query_temp("job/coagent", me);
        me->interrupt_me(me, 1);
        delete_temp("job", me);
        if (objectp(passive))
        {
                message_vision("$n不幹了，$N也只好跟著停下手來。\n",
                               me, passive);
        }
        if (coagent) end_working(coagent, me);
        return 0;
}

int working(object me)
{
        object ob;
        object coagent;
        object weapon;
        object wood;
        string msg;
        string gmsg;
        int finish;
        int b;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if( !objectp(coagent=query_temp("job/coagent", me)) )
        {
                message_vision("幫忙的人走了，$N只好停手不幹了。\n", me);
                return end_working(me);
        }

        if (! living(me))
        {
                return end_working(me);
        }

        ob=query_temp("handing", me);
        if (! objectp(ob) || ! ob->is_saw())
        {
                message_vision("鋸沒了，$N停手不幹了。\n", me);
                return end_working(me);
        }

        finish = 0;
        switch(query_temp("job/step", me) )
        {
        case 1:
                me->receive_damage("qi", 20);
                msg = "$N四周看看，選中了一顆上好的鬆樹。";
                break;
        case 2:
                me->receive_damage("qi", 20);
                msg = "$N和$n走到鬆樹旁，掂量了一下，然後抄起" + ob->name() +
                      "開始攔腰拉鋸。";
                break;
        case 3:
                me->receive_damage("qi", 30);
                msg = "“吱嘎吱嘎”，木屑飛揚，地上洒了不少木屑。";
                break;
        case 4:
                me->receive_damage("qi", 30);
                msg = "“嘎吱嘎吱”，$N和$n奮力拉鋸。";
                break;
        case 5:
                me->receive_damage("qi", 30);
                msg = "“吱嘎吱嘎”，地上的木屑是越來越多，鋸也越來越深。";
                break;
        case 6:
                me->receive_damage("qi", 30);
                msg = "“嘎吱嘎吱”，$N和$n奮力拉鋸。";
                break;
        case 7:
                me->receive_damage("qi", 30);
                msg = "“吱嘎吱嘎”，忽然“喀拉”的一聲，鬆樹有些搖晃。";
                break;
        case 8:
                if( objectp(weapon=query_temp("weapon", me)) && 
                    query("skill_type", weapon) == "axe" )
                {
                        msg = "$N擺擺手，讓$n扶好鬆樹，上去就是“□□□”的砍。";
                        break;
                }
                if( objectp(weapon=query_temp("weapon", coagent)) && 
                    query("skill_type", weapon) == "axe" )
                {
                        msg = "$n擺擺手，讓$N扶好鬆樹，上去就是“□□□”的砍。";
                        break;
                }
                
                message_vision("鋸到這個份上，卻沒找到斧頭，$N和$n"
                               "瞪瞪眼睛，只好停手。\n", me, coagent);
                return end_working(me);
        default:
                msg = "大樹“吱呀吱呀”的到了下來，$N和$n連忙閃開。";
                finish = 1;
                break;
        }
        msg += "\n";

        // send message out
        gmsg = replace_string(msg, "$N", "你");
        gmsg = replace_string(gmsg, "$n", coagent->name());
        tell_object(me, gmsg);
        gmsg = replace_string(msg, "$n", "你");
        gmsg = replace_string(gmsg, "$N", me->name());
        tell_object(coagent, gmsg);

        if (finish)
        {
                delete_temp("job", me);
                delete_temp("job", coagent);
                coagent->interrupt_me(coagent, 1);

                wood = new("/d/guanwai/obj/largewood");
                wood->move(this_object());

                if (me->query_dex() / 2 + random(me->query_dex() / 3) < 12)
                {
                        message_vision("大樹轟然倒地，$N還是差了一步，結"
                                       "果“啪”的一下把$N壓了個嚴嚴實實。\n", me);
                        me->unconcious();
                } else
                if (coagent->query_dex() / 2 + random(coagent->query_dex() / 3) < 12)
                {
                        message_vision("大樹轟然倒地，$N還是差了一步，結"
                                       "果“啪”的一下把$N壓了個嚴嚴實實。\n", coagent);
                        coagent->unconcious();
                } else
                {
                        message_vision("大樹轟然倒地，$N和$n抹了抹頭"
                                       "上的汗，相視一笑。\n", me, coagent);

                        if (wood->move(me))
                        {
                                message_vision(HIC "$N" HIC "“嗨”的一聲，在$n" HIC
                                               "的幫助下把" + wood->name() + HIC
                                               "扛了起來。\n" NOR, me, coagent);
                        } else
                        if (wood->move(coagent))
                        {
                                message_vision(HIC "$n" HIC "“嗨”的一聲，在$N" HIC
                                               "的幫助下把" + wood->name() + HIC
                                               "扛了起來。\n" NOR, me, coagent);
                        } else
                        {
                                message_vision("$N和$n上去掂了掂木料，都覺得太"
                                               "重，只好先放在地上。\n",
                                               me, coagent);
                        }
                }

                if( query("combat_exp", me) >= 500000 && 
                    query("combat_exp", me)<1500000 )
                {
                        // bonus to me
                        b = 150 + random(100);
                        GIFT_D->work_bonus(me, ([ "exp" : b, "pot" : b / 3, "prompt" : "通過這次鍛煉，你對武學的理解又進一步" ]));
                        me->improve_skill("force", (b + 3) / 4);
                }

                if( query("combat_exp", coagent) >= 500000 && 
                    query("combat_exp", coagent)<1500000 )
                {
                        // bonus to coagent
                        b = 150 + random(100);
                        GIFT_D->work_bonus(coagent, ([ "exp" : b, "pot" : b / 3, "prompt" : "通過這次鍛煉，你對武學的理解又進一步" ]));
                        coagent->improve_skill("force", (b + 3) / 4);
                }

                return 0;
        } else
                addn_temp("job/step", 1, me);

        return 1;
}

int coagent(object me)
{
        return 1;
}

int halt_working(object me, object who, int silent)
{
        if( !query_temp("job/famu", me) )
                return 1;

        if (! silent)
                message_vision("$N嘆了口氣，道：“累死了，我"
                               "得先揉揉肩！”\n", me);
        end_working(me);
        return 1;
}
