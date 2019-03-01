// qi.c 戚長發

#include <ansi.h>
#include <command.h>

inherit NPC;
inherit F_DEALER;

int do_answer();

void create()
{
        set_name("戚長發", ({ "qi changfa", "qi" }));
        set("title", "躺屍劍門傳人");
        set("nickname", HIR "宰人不用刀，" HIC "願" HIR "者上鉤" NOR);

        set("gender", "男性");
        set("age", 48);
        set("str", 100);
        set("long",
                "戚老板最近是爆發橫財，所謂是三年不開張，開張管三年。\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("higgling", 800);
        set_temp("apply/damage", 15);

        set("combat_exp", 800000);
        set("attitude", "friendly");

        set("inquiry", ([
                "寶物" : (: do_answer :),
                "買賣" : (: do_answer :),
                "生意" : (: do_answer :),
                "東西" : "扔掉就沒了！嘿嘿。",
                "還我錢"     : "哼！我這裡是有進無出！",
                "我的錢"     : "什麼你的錢，地上的就是我的！",
                "錢"         : "想錢啊？自己去掙！",
                "我的東西"   : "扔掉就沒了！嘿嘿。",
                "贖"         : "贖？沒得贖！",
                "天王保命丹" : "賣！賣！五百兩黃金一粒！",
                "翡翠蘭"     : "可治百毒啊！有氣就能活！",
                "朱睛冰蟾"   : "雖然不象翡翠蘭那樣可起死回生，但是能解百毒！",
                "討價還價"   : "和我學(higgling)... 我很窮啊！",
                "higgling"   : "和我學討價還價麼... 我很窮啊！",
        ]));

        set("vendor_goods", ([
                "/d/item/obj/xuantie"     : "3000000",
                "/d/item/obj/butian"      : "8000000",
                "/d/item/obj/wujins"      : "3000000",
                "/d/item/obj/tiancs"      : "8000000",
                //"/clone/medicine/baoming" : "3000000",
                //"/clone/medicine/jiuhua"  : "3000000",
                "/d/shenlong/obj/hua4"    : "30000000",
                "/clone/misc/zhujingchan" : "20000000",
                "/clone/gift/shenliwan"   : "100000000",
                "/clone/gift/xisuidan"    : "100000000",
                "/clone/gift/xiandan"     : "100000000",
                "/clone/gift/unknowdan"   : "100000000",
                "/clone/misc/dymo"        : "5000000",
                "/clone/item/magicfruit"  : "200000000",
                "/clone/gift/kardan"      : "5000000",
                "/clone/gift/perwan"      : "5000000",
                "/clone/gift/huirongwan"   : "50000000",
                "/clone/gift/htdan"   : "50000000",
                "/clone/goods/washgift"   : "10000",
                "/clone/goods/dizangshi"   : "15000000",
                "/clone/goods/zhufu_sword"   : "1000000",
                "/clone/goods/zhufu_blade"   : "1000000",
                "/clone/goods/zhufu_staff"   : "1000000",
                "/clone/goods/zhufu_whip"   : "1000000",
                "/clone/goods/zhufu_hammer"  : "1000000",
                "/clone/goods/zhufu_finger"   : "1000000",
                "/clone/goods/zhufu_hand"   : "1000000",
                "/clone/goods/zhufu_armor"   : "1000000",
                "/clone/goods/zhufu_cloth"   : "1000000",
                "/clone/goods/zhufu_head"   : "1000000",
                "/clone/goods/zhufu_boots"   : "1000000",
                "/clone/goods/zhufu_surcoat"   : "1000000",
                "/clone/goods/zhufu_waist"   : "1000000",
                "/clone/goods/zhufu_wrists"   : "1000000",
                "/adm/npc/obj/gift"   : "1000000",
        ]));

        setup();
        set_max_encumbrance(100000000);
        if (clonep()) keep_heart_beat();
}

void init()
{
        add_action("do_buy", "buy");
        add_action("do_list", "list");
        add_action("do_drop", "drop");
        add_action("do_look", ({"guankan", "kan"}));
}

void heart_beat()
{
        string start_room;
        object ob;

        if (stringp(start_room = query("startroom")) &&
            find_object(start_room) == environment())
        {
                foreach (ob in all_inventory(environment()))
                {
                        if (! ob->is_character() ||
                            interactive(ob) || playerp(ob) ||
                            query_temp("owner", ob) )
                                continue;

                        if( stringp(start_room=query("startroom", ob)) &&
                            find_object(start_room) == environment())
                                continue;

                        message_vision("$N皺了皺眉，把$n推了出去。\n",
                                       this_object(), ob);
                        ob->move("/d/city/beidajie1");
                }
        }

        ::heart_beat();
}

int do_drop(string arg)
{
        int i;
        object *obs;
        object ob;
        object me;

        if (! arg)
                return 0;

        me = this_player();
        if (objectp(ob = present(arg, me)) &&
            ob->is_character() && ! playerp(ob))
        {
                addn_temp("static/drop_npc", 1, me);
                if( query_temp("static/drop_npc", me)>1 &&
                    query("combat_exp", me) >= 50000 )
                {
                        message_vision("$N大怒道：：“好你個" +
                                       RANK_D->query_rude(ob) +
                                       "，還來添亂！”\n說罷只見$N"
                                       "飛起一腳，將$n和" + ob->name() +
                                       "一起踢出門外。\n", this_object(), me);
                        ob->move("/d/city/beidajie1");
                        me->move("/d/city/beidajie1");
                        message("vision", "只聽叮叮□光一陣向，" + me->name() +
                                          "被人一腳踢了出來。\n",
                                environment(me), me);
/*
                        me->receive_damage("qi", 1);
                        me->die();
*/
                        return 1;
                }

                message_vision("$N怒道：“滾開，少給我添亂，影響我的生意。”\n"
                               "說罷只見$N飛起一腳，將$n和" + ob->name() +
                               "一起踢出門外。\n", this_object(), me);
                ob->move("/d/city/beidajie1");
                me->move("/d/city/beidajie1");
                message("vision", "只聽叮叮□光一陣向，" + me->name() +
                                  "被人一腳踢了出來。\n",
                        environment(me), me);
/*
                me->receive_damage("qi", 1);
                me->unconcious();
*/
                return 1;
        }

/*
        if (! DROP_CMD->main(me, arg))
                return 0;

        if (! GET_CMD->main(this_object(), arg))
                return 1;
*/

        if (objectp(ob) && ! ob->is_character()) destruct(ob);
        obs = all_inventory(this_object());
        for (i = 0; i < sizeof(obs); i++)
                if (! obs[i]->is_character()) destruct(obs[i]);
        if (! random(5))
        {
                switch (random(4))
                {
                case 0:
                        command("say 日積月累，小康之路！");
                        break;
                case 1:
                        command("kok "+query("id", this_player()));
                        command("say 隨地亂扔垃圾，罰款五元！");
                        break;
                case 2:
                        command("say 敗家子，敗家子！");
                        break;
                default:
                        command("heihei");
                        break;
                }
        }
        return 1;
}

int do_answer()
{
        write(name() + "在你耳邊輕聲說道：我");
        ::do_list();
        write("這可真是貨真價實，童叟無欺啊！\n");
        return 1;
}

int accept_object(object who, object ob)
{
        if( query("money_id", ob) )
        {
                if( !query_temp("mark/戚", who) )
                        set_temp("mark/戚", 0, who);

                if( query("money_id", ob) && ob->value() >= 10000 )
                {
                        message_vision("$N同意指點$n一些討價還價得的技巧。\n",
                                       this_object(), who);
                        addn_temp("mark/戚", ob->value()/100, who);
                        destruct(ob);
                        return 1;
                }
                command("say 你這點錢... 我雖然窮可還真看不上！");
                return -1;
        }

        switch (random(6))
        {
        case 0:
                command("say 好！好！");
                break;
        case 1:
                command("say 不要就給我！");
                break;
        }

        if (! ob->is_character())
        {
                destruct(ob);
                return -1;
        }

        return 1;
}

void unconcious()
{
        message_vision("\n$N哼哼兩聲，道：“困死了...哦！”\n",
                       this_object());
        full_self();
}

void die()
{
        message_vision("\n$N大叫一聲，道：“痛死啦！”連忙掏出天王保命丹吃了兩顆。\n",
                       this_object());
        full_self();
}

int recognize_apprentice(object ob, string skill)
{
        if( query_temp("mark/戚", ob)<1 )
                return 0;

        if (skill != "higgling")
                return 0;

        addn_temp("mark/戚", -1, ob);
        return 1;
}
