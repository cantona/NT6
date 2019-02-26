#include <ansi.h>
#include <medical.h>

inherit NPC;
inherit F_DEALER;

string ask_job();
int do_peiyao(string arg);
int working(object me);
int halt_working(object me);
int ask_me();
int ask_riyue();
int do_join(string arg);
int do_unjoin(string arg);
int do_identify();
int do_decide();

void create()
{
        set_name("平一指", ({ "ping yizhi", "ping", "yizhi" }));
        //set("title", "藥鋪老闆");
        set("title", HIW"煉藥師協會"HIR"會長"NOR);
        set("nickname", HIB "殺人神醫" NOR);
        set("gender", "男性");
        set("long", "他就是醫術高超的「殺人神醫」平一指。可是他性格古\n"
                    "怪，不是什麼人都醫的。\n");
        set("age", 65);

        set("int", 38);

        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 1000);
        set("max_jing", 1000);
        set("shen_type", 1);

        set("combat_exp", 500000);
        set("attitude", "heroism");

        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("parry", 60);
        set_skill("liandan-shu", 2200);
        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/damage", 50);
        set("inquiry", ([
                "配藥"   : (: ask_job :),
                "工作"   : (: ask_job :),
                "job"    : (: ask_job :),
                "療傷"   : (: ask_me  :),
                "日月神教" : (: ask_riyue :),
                "入會"     : "在我這裏，可以加入(" HIY "join" NOR +
                             CYN ")煉藥師協會。\n" NOR,
                "加入"     : "在我這裏，可以加入(" HIY "join" NOR +
                             CYN ")煉藥師協會。\n" NOR,
                "鑑定"     : "在我這裏，可以鑑定(" HIY "jianding" NOR +
                             CYN ")煉藥師品級。\n" NOR,
                "煉藥師協會" : "在我這裏，可以加入(" HIY "join" NOR +
                             CYN ")煉藥師協會。\n" NOR,
        ]));

        set("vendor_goods", ({
                HERB("chaihu"),         // 柴胡
                HERB("chenpi"),         // 陳皮
                HERB("chongcao"),       // 蟲草
                HERB("chuanwu"),        // 川烏
                HERB("dahuang"),        // 大黃
                HERB("dangui"),         // 當歸
                HERB("duhuo"),          // 獨活
                HERB("fangfeng"),       // 防風
                HERB("fuzi"),           // 附子
                HERB("gsliu"),          // 幹石榴
                HERB("guiwei"),         // 歸尾
                HERB("hafen"),          // 蛤粉
                HERB("heshouwu"),       // 何首烏
                HERB("honghua"),        // 紅花
                HERB("huangqi"),        // 黃芪
                HERB("lurong"),         // 鹿茸
                HERB("xiongdan"),       // 熊膽
                HERB("juhua"),          // 菊花
                HERB("lanhua"),         // 蘭花
                HERB("lingxian"),       // 靈仙
                HERB("lingzhi"),        // 靈芝
                HERB("mahuang"),        // 麻黃
                HERB("moyao"),          // 沒藥
                HERB("niuhuang"),       // 牛黃
                HERB("niuxi"),          // 牛膝
                HERB("qianjinzi"),      // 千金子
                HERB("renshen"),        // 人蔘
                HERB("ruxiang"),        // 乳香
                HERB("shadan"),         // 鯊膽
                HERB("shancha"),        // 山茶花
                HERB("shanjia"),        // 山甲
                HERB("shengdi"),        // 生地
                HERB("shenglg"),        // 生龍骨
                HERB("sumu"),           // 蘇木
                HERB("taoxian"),        // 桃仙
                HERB("tenghuang"),      // 藤黃
                HERB("tianqi"),         // 田七
                HERB("tugou"),          // 土狗
                HERB("wulingzhi"),      // 五靈脂
                HERB("xiefen"),         // 蠍粉
                HERB("xijiao"),         // 犀角
                HERB("xionghuang"),     // 雄黃
                HERB("xuejie"),         // 血竭
                HERB("xuelian"),        // 雪蓮
                HERB("yanwo"),          // 燕窩
                HERB("yjhua"),          // 洋金花
                HERB("yuanzhi"),        // 遠志
                HERB("zihua"),          // 紫花
                HERB("zzfen"),          // 珍珠粉
                HERB("hugu"),           // 虎骨
                "/clone/misc/yanbo",    // 研缽
                "/clone/drug/tianqi-san",
                "/d/city/obj/shanshen",
                "/clone/medicine/jinmisan",
                "/clone/book/medical_book",
        }));

        setup();
        add_money("silver", 50);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_peiyao", "peiyao");
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_join", "join");
        add_action("do_decide", "decide");
        add_action("do_identify", "jianding");
        add_action("do_unjoin", "unjoin");
}

string ask_job()
{
        object me;
        object *obs;

        me = this_player();
        if( query_temp("job/peiyao", me) )
                return "讓你乾的活你幹完了麼？";

        if( query("combat_exp", me)>30000 )
                return "讓你幹這活，也太屈就你了吧。";

        if( query("combat_exp", me)<3000 )
                return "就這點經驗，連一百五都沒有，我看你來藥臼都端不起來！";

        if( query("qi", me)<5 )
                return "你還是先歇歇吧，萬一累出人命來我可負擔不起。";

        if (! interactive(me))
                return "...";

        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              query_temp("job/peiyao", $1) &&
                              query_ip_number($1) == query_ip_number($(me)) :));
        if (sizeof(obs) > 0)
                return "我這已經有" + obs[0]->name() + "在幹活了，你等等吧。";

        set_temp("job/peiyao", 1, me);
        return "好，你就幫我配藥(peiyao)吧！喏，就這幾味。";
}

int do_peiyao(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("你正忙着呢，彆着急。\n");

        if( !query_temp("job/peiyao", me) )
        {
                message_vision("$N剛想抓幾味藥配製，就聽見$n怒喝道："
                               "給我放下，別亂動。\n",
                               me, this_object());
                return 1;
        }

        set_temp("job/step", 1, me);
        me->start_busy(bind((: call_other, __FILE__, "working" :), me),
                       bind((: call_other, __FILE__, "halt_working" :), me));
        tell_object(me, "你開始工作。\n");
        return 1;
}

int working(object me)
{
        object ob;
        string msg;
        int finish;
        int b;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if (! living(me))
        {
                delete_temp("job/peiyao", me);
                delete_temp("job/step", me);
                return 0;
        }

        finish = 0;
        me->receive_damage("qi", 1);
        switch(query_temp("job/step", me) )
        {
        case 1:
                msg = "$N東挑西揀，選好了一些藥材。";
                break;
        case 2:
                msg = "$N把藥材放進藥臼，使勁搗了起來。";
                break;
        case 3:
                msg = "藥材漸漸化作粉屑，混在一起。";
                break;
        case 4:
                msg = "粉屑在$N的搗弄下越來越細，逐漸變成了粉末。";
                break;
        default:
                msg = "$N把藥材包好，遞給$n。";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                msg += "$n看了$N配的藥，點頭道：不錯，不錯！"
                       "這是給你的報酬！\n";
                delete_temp("job/peiyao", me);
                delete_temp("job/step", me);

                b = 500 + random(80);
                GIFT_D->delay_work_bonus(me, ([ "exp" : b, "pot" : b / 3 ]));

                ob = new("/clone/money/coin");
                ob->set_amount(10);
                ob->move(me, 1);
        }

        msg = replace_string(msg, "$N", "你");
        msg = replace_string(msg, "$n", name());
        tell_object(me, msg);

        if (finish)
        {
                if (! query("zhufu_mod/wrists", me) && random(10) == 1)
                {
                        msg = "$n對$N嘿嘿一笑，道：幹得不賴，有點"
                              "意思，這個神之祝福護腕就算是我送給你的禮物吧。\n";
                        message_vision(msg, me, this_object());
                        ob = new("/clone/goods/zhufu_wrists");
                        ob->move(me, 1);
                        tell_object(me, HIM "\n你獲得了一個" + ob->name() +
                                        HIM "！\n" NOR);
                        set("zhufu_mod/wrists", 1, me);
                }
                else
                if (random(1000) == 1)
                {
                        msg = "$n對$N嘿嘿一笑，道：幹得不賴，有點"
                              "意思，這個丹玉磨就算是我送給你的禮物吧。\n";
                        message_vision(msg, me, this_object());
                        ob = new("/clone/misc/dymo");
                        ob->move(me, 1);
                        tell_object(me, HIM "\n你獲得了一個" + ob->name() +
                                        HIM "！\n" NOR);
                }

                return 0;
        }

        addn_temp("job/step", 1, me);
        return 1;
}

int halt_working(object me)
{
        message_vision("$N把手中的活一甩，嚷嚷道：不幹了，不幹了！\n",
                       me);
        delete_temp("job/peiyao", me);
        delete_temp("job/step", me);
        return 1;
}

int accept_object(object who, object ob)
{
        object obj ;
        if( !query_temp("何首烏", who) )
        {
        message_vision("平一指對$N説：醫一人，殺一人，老夫不收錢！\n", who);
                return 0 ;
        }
        if( query("money_id", ob) && ob->value() >= 50000 )
        {
                destruct(ob);
                message_vision("平一指收下了$N的錢，給了$N一株何首烏！\n" , who);
                delete_temp("何首烏", this_player());
                obj=new(__DIR__"obj/shouwu");
                obj->move(this_player());
        }
        return 1;
}

int ask_me()
{
        object ob = this_player();

        if( query("family/family_name", ob) != "日月神教" )
        {
                command("say 老夫醫一人殺一人，不怕死就來吧。\n");
                return 1;
        }
        if( query("eff_qi", ob) == query("max_qi", ob) )
        {
                command("say 你又沒有受傷，來逍遣老夫嗎？\n");
                return 1;
        }
        else
        {
                message_vision("平一指手指微屈，單指一彈，一粒藥丸疾射入$N的咽喉，$N"
                                "不由“咕嚕”一聲吞入腹中，頓感神清氣爽，精神飽滿。\n", ob);
                set("eff_qi",query("max_qi",  ob), ob);
                set("eff_jing",query("max_jing",  ob), ob);
                command("say 哼，我日月神教武功獨霸武林，你好好去學學，別再丟人現眼了，快滾吧。\n");
                return 1;
        }
}

int ask_riyue()
{
        object ob = this_player();

        if( query("family/family_name", ob) != "日月神教" )
                return notify_fail("我日月神教他日必一統江湖。\n");

        message("vision", "平一指飛起一腳，已將" + ob->name() + "踢得無影無蹤。\n", environment(ob), ob);
        ob->move("/d/heimuya/midao7");
        tell_object(ob, "平一指飛起一腳，將你踢進了祕道。\n");
        return 1;
}

int do_join(string arg)
{
        object me = this_player();

        if (! arg || arg != "煉藥師協會")
                return notify_fail(CYN "平一指一楞，説道：你要加入什麼？我"
                                   "這裏是煉藥師協會。\n" NOR);

        if( me->query_skillo("liandan-shu", 1) < 300 )
                return notify_fail(CYN "平一指皺了皺眉，説道：想加入煉藥師"
                                   "協會，必須具備一品煉藥師資格，你可以先"
                                   "從我這裏學點煉丹技藝(liandan-shu)。\n" NOR);

        if( query("is_alchemy", me) )
                return notify_fail(CYN "平一指皺了皺眉，説道：你不是已經加"
                                   "入煉藥師協會了麼？\n" NOR);

        if( query("bad_alchemy", me) )
                return notify_fail(CYN "平一指冷笑一聲，説道：既然你已經脱"
                                   "離了煉藥師協會，又回來作甚？\n" NOR);

        tell_object(me, CYN "\n平一指點了點頭，説道：你真的打算(" HIY "dec"
                        "ide" NOR + CYN ")加入煉藥師協會麼？可考慮清楚了？"
                        "\n" NOR);
        set_temp("want_join", 1, me);
        return 1;
}

int do_unjoin(string arg)
{
        object me = this_player();

        if (! arg || arg != "煉藥師協會")
                return notify_fail(CYN "平一指皺了皺眉，説道：你打算脱離什"
                                   "麼？説話不清不楚的。\n" NOR);

        if( !query("is_alchemy", me) )
                return notify_fail(CYN "平一指冷笑一聲，沒理你。\n" NOR);

        tell_object(me, CYN "\n平一指歎了口氣，説道：如果脱離煉藥師協會，以後"
                        "可不能反悔。你真打算(" HIY "decide" NOR + CYN ")"
                        "這麼做麼？\n" NOR);
        set_temp("want_tuoli", 1, me);
        return 1;
}

int do_decide()
{
        object ob, me;
        int level;
        string *pro;
        me = this_player();

        if( query_temp("want_join", me) )
        {
                message_vision(HIC "$N" HIC "對着$n" HIC "微笑道：煉藥師"
                               "可是最榮耀的職業，以後好好幹吧。\n" NOR,
                               this_object(), me);

                level = me->query_skillo("liandan-shu", 1);
                set("is_alchemy", level/300, me);
                delete_temp("want_join", me);

                ob = new("/clone/misc/yaoshi-zheng");
                set("level", level/300, ob);
                ob->enable();
                ob->move(this_object());
                command("give yaoshi zheng to "+query("id", me));

                set("bindable", 3, ob);
                set("bind_owner",query("id", me), ob);
                set("owner",query("id", me), ob);
                set("no_store", 1, ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);

                pro = query("profession", me);
                if( !pro ) pro = ({});
                pro += ({ "alchemy" });
                set("profession", pro, me);
                return 1;
        } else
        if( query_temp("want_tuoli", me) )
        {
                message_vision(HIC "$N" CYN "對着$n" HIC "點點頭，人各有"
                               "志，從此以後你我再無瓜葛。\n" NOR,
                               this_object(), me);

                delete("is_alchemy", me);
                set("bad_alchemy", 1, me);
                delete_temp("want_tuoli", me);

                pro = query("profession", me);
                pro -= ({ "alchemy" });
                set("profession", pro, me);

                if (objectp(ob = present("yaoshi zheng", me)));
                {
                        message_vision(HIR "$N" HIR "將$n" HIR "的" NOR +
                                       ob->name(1) + HIR "註銷了。\n" NOR,
                                       this_object(), me);
                        destruct(ob);
                }
                return 1;
         }

         return notify_fail(CYN "平一指瞄了你一眼，皺了皺眉，沒理你。\n" NOR);
}

int do_identify()
{
        int level;
        object ob, me = this_player();

        if( query("bad_alchemy", me) )
                return notify_fail(CYN "平一指不耐煩道：走開，走開。你又回"
                                   "來作甚？\n" NOR);

        if( !query("is_alchemy", me) )
                return notify_fail(CYN "平一指瞄了你一眼，沒理你。\n" NOR);

        if( objectp(ob = present("yaoshi zheng", me)) )
                destruct(ob);

        level = me->query_skillo("liandan-shu", 1);
        set("is_alchemy", level/300, me);

        ob = new("/clone/misc/yaoshi-zheng");
        set("level", level/300, ob);
        ob->enable();
        ob->move(this_object());
        command("give yaoshi zheng to "+query("id", me));

        set("bindable", 3, ob);
        set("bind_owner",query("id", me), ob);
        set("owner",query("id", me), ob);
        set("no_store", 1, ob);
        set("auto_load", 1, ob);
        set("set_data", 1, ob);

        return 1;
}

int recognize_apprentice(object ob, string skill)
{
        if (skill != "liandan-shu")
                return 0;

        if (ob->query_skillo("liandan-shu", 1) >= 300)
        {
                write(CYN "平一指點了點頭，説道：煉丹技藝的提"
                      "高需要不斷從實踐中來提升的，煉丹技藝的\n"
                      "基本功我就教到這裏，剩下看你的天賦和修行了。\n" NOR);
                return -1;
        }
        return 1;
}
