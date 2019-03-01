// qingyangzi.c  青□子
// Written by Vin  2002/4/28

#include <ansi.h>
inherit NPC;

int ask_me();
int tattoo(object me);

mapping body_type = ([ "臉部" : ({ "face" }),
                       "胸口" : ({ "chest" }),
                       "後背" : ({ "back" }),
                       "臀部" : ({ "buttock" }),
                       "左臂" : ({ "leftarm" }),
                       "右臂" : ({ "rightarm" }), ]);

void create()
{
        set_name("青□子", ({ "qingyang zi", "qingyang", "zi" }));
        set("long", "他便是天下第一刺青師青□子。\n" );

        set("nickname", HIB "刺青師" NOR);
        set("gender", "男性");
        set("attitude", "friendly");
        set("age", 325);
        set("shen_type", 0);
        set("str", 500);

        /*
        set("inquiry", ([
                "刺青" : (: ask_me :),
                "紋身" : (: ask_me :),
        ]));
        */

        setup();

        if (! clonep(this_object()))
        {
                move("/d/luoyang/suanming");
                message_vision(CYN "\n$N" CYN "走了過來，環顧四周，幽"
                               "幽一聲長嘆。\n" NOR, this_object());
                set("startroom", "/d/luoyang/suanming");
        }

        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/tattoo/npc_item2")->wield();
        set_temp("handing", carry_object("/clone/tattoo/npc_item1"));
}

void init()
{
        /*
        add_action("do_show", "show");
        add_action("do_answer", "answer");
        // 刺青過程中禁止查看自身狀態，為什麼要這樣呢？因為
        // 實際數據已經在進行玩家所看到的刺青過程前便設置了。
        add_action("do_check", "hp");
        add_action("do_check", "score");
        add_action("do_check", "special");
        */
}

int do_check()
{
        object me = this_player();

        if( query_temp("item/status", me) == "waiting" )
        {
                message_vision(CYN "$N" CYN "對$n" CYN "喝道：別亂"
                               "動！還沒刺完，你猴急什麼？\n" NOR,
                               this_object(), me);
                return 1;
        }
}

int do_show(string arg)
{
        string status, msg, mat;
        object me, ob;
        int value, n;

        me = this_player();
        if (! arg)
                return notify_fail("你想要亮出什麼東西？\n");

        mat = arg;

        if (! objectp(ob = present(mat, me)))
                return notify_fail("你身上似乎沒有這種東西。\n");

        status = query_temp("item/status");

        if (status == "look_working")
        {
                message_vision(CYN "$N" CYN "頭也不抬，對$n" CYN "說道："
                               "我這正忙，你的事等會再說。\n" NOR,
                               this_object(), me);
                return 1;
        }

        if( !query("can_tattoo", ob) )
        {
                message_vision(CYN "$N" CYN "眉頭一皺，對$n" CYN "說道："
                               "我只對圖騰感興趣，沒事別來煩我。\n" NOR,
                               this_object(), me);
                return 1;
        }

        if( query("value", ob) >= 12000 )
                msg = sprintf(CYN "$N" CYN "接過$n" CYN "拿出的圖樣，凝視良久"
                              "之後，幽幽一聲長嘆。\n" NOR);
        else
        if( query("value", ob) >= 5000 )
                msg = sprintf(CYN "$N" CYN "接過$n" CYN "拿出的圖樣，看了一會"
                              "，臉上露出讚許的神色。\n" NOR);
        else
        if( query("value", ob) >= 2000 )
                msg = sprintf(CYN "$N" CYN "接過$n" CYN "拿出的圖樣，皺了皺眉"
                              "，似乎想說些什麼。\n" NOR);
        else
                msg = sprintf(CYN "$N" CYN "望著$n" CYN "遞來的圖樣，冷笑一聲"
                              "，臉上露出不屑的神色。\n" NOR);

        value=query("value", ob)/50+20;
        msg += sprintf(CYN "$N" CYN "點了點頭道：這樣的刺青需要黃金%s兩，你自"
                       "己斟酌吧。\n" NOR, chinese_number(value));
        message_vision(msg, this_object(), me);

        return 1;
}

// 發出提示信息
int ask_me()
{
        message_sort(CYN "$N" CYN "抬頭看了看$n" CYN "，點頭道：先把你打算紋"
                     "刺的圖騰拿給我看(" HIY "show" NOR + CYN ")看，讓我估算"
                     "一下價錢，如果覺得合適就交錢。\n" NOR, this_object(),
                     this_player());
        return 1;
}

// 接受定金
int accept_object(object me, object ob)
{
        string status;
        int val;

        status = query_temp("item/status");
        if (status == "look_working")
        {
                message_vision(CYN "$N" CYN "頭也不抬，對$n" CYN "說道："
                               "我這正忙，你的事等會再說。\n" NOR,
                               this_object(), me);
                return 0;
        }

        if (status == "waiting")
        {
                if( query_temp("item/player_id") == query("id", me) )
                {
                        command("say 你給我躺好，別亂動。");
                        return 0;
                }

                message_vision(CYN "$N" CYN "頭也不抬，對$n" CYN "說道："
                               "我這正忙，你的事等會再說。\n" NOR,
                               this_object(), me);
                return 0;
        }

        if (status == "accept")
        {
                if( query_temp("item/player_id") != query("id", me) )
                {
                        command("say 沒見我正忙麼，還來添什麼亂！");
                        return 0;
                }

                if( !query("money_id", ob) )
                {
                        command("say 我讓你交錢，你給我這個幹嘛？");
                        return 0;
                }
        }

        if( query("can_tattoo", ob) && query("tattoo_type", ob) )
        {
                mixed p;
                string *types;

                types = keys(body_type);

                p=query("tattoo/tattoo", me);
                if (arrayp(p))
                        types -= p;
                else
                if (stringp(p))
                        types -= ({ p });

                if (! sizeof(types))
                {
                               message_vision(CYN "$N" CYN "對$n" CYN "冷笑道：你全"
                                              "身已經紋得跟鬼一樣了，還嫌不夠麼？\n"
                                              NOR, this_object(), me);
                        return 0;
                }

                if( (p=query("can_tattoo", ob)) == "all" )
                {
                        types = keys(body_type);
                } else
                if (arrayp(p))
                        types = p;
                else
                if (stringp(p))
                        types = ({ p });

                // 確認該ID是否有地方已經被刺青
                p=query("tattoo/tattoo", me);
                if (arrayp(p))
                        types -= p;
                else
                if (stringp(p))
                        types -= ({ p });

                if (! sizeof(types))
                {
                        message_vision(CYN "$N" CYN "搖了搖頭道：這個圖"
                                       "騰並不適合紋到你剩下的部位上。\n"
                                       NOR, this_object(), me);
                        return 0;
                }

                // 計算刺青所花費的價值
                val=query("value", ob)/50+20;
                message_vision(CYN "$N" CYN "點了點頭道：這樣的刺青需要黃金" +
                               chinese_number(val) + "兩，你現在就付錢吧。\n"
                               NOR, this_object(), me);
                val *= 10000;
                set("item/value", val, ob);
                set_temp("item/status", "item_gived", me);
                set_temp("item/value", val, me);
                set_temp("item/status", "accept");
                set_temp("item/player_id",query("id", me));
                set_temp("item/accept", ob);

                remove_call_out("time_out");
                call_out("time_out", 30, me, ob);
                return 1;
        }

        if( query("money_id", ob) )
        {
                object origin;
                mixed p;
                string *types;

                if( query_temp("item/status", me) == "answer_type" )
                {
                        message_vision(CYN "$N" CYN "搖搖頭，對$n" CYN "道：別急"
                                       "著給錢，先說說你要幹什麼？\n" NOR,
                                       this_object(), me);
                        return 0;
                }

                if( query_temp("item/status", me) != "item_gived" )
                {
                        message_vision(CYN "$N" CYN "把$n" CYN "遞過去的" + ob->name() +
                                       CYN "推了回來，搖頭道：無功不受祿。\n" NOR,
                                       this_object(), me);
                        return 0;
                }

                if( ob->value()<query_temp("item/value", me) )
                {
                        message_vision(CYN "$N" CYN "冷笑道：江湖上誰不知道我青"
                                       "□子說一不二，難道能為你破例？\n" NOR,
                                       this_object(), me);
                        return 0;
                }

                origin = query_temp("item/accept");
                if( (p=query("can_tattoo", origin)) == "all" )
                {
                        types = keys(body_type);
                } else
                if (arrayp(p))
                        types = p;
                else
                if (stringp(p))
                        types = ({ p });

                // 確認該ID是否有地方已經被刺青
                p=query("tattoo/tattoo", me);
                if (arrayp(p))
                        types -= p;
                else
                if (stringp(p))
                        types -= ({ p });

                if (! sizeof(types))
                {
                        message_vision(CYN "$N" CYN "搖了搖頭道：這個刺"
                                       "青不適合紋到你剩下的部位。\n" NOR,
                                       this_object(), me);
                        return 0;
                }

                set_temp("item/types", types);
                set_temp("item/money", ob);

                ob->move(this_object());

                message_vision(CYN "$N" CYN "對$n" CYN "說道：你打算在什"
                               "麼地方刺青？請告訴(" HIY "answer" NOR +
                               CYN ")我具體部位。\n" NOR, this_object(), me);
                tell_object(me, HIC "你還可以在" HIY + implode(types, "、" )
                                + HIC "上刺青。\n" NOR);

                set_temp("item/status", "answer_type", me);
                return -1;
        }

        message_vision(CYN "青□子對$N" CYN "皺眉道：好象有點問題，你讓巫"
                       "師來幫你看看。\n" NOR, me);
        return 0;
}

int do_answer(string arg)
{
        string *tattooed, *types;
        string tlong, special;
        object ob, me;
        object money;

        me = this_player();
        if( query_temp("item/status", me) != "answer_type" )
                return 0;

        if (! arg)
                return notify_fail("你要回答什麼？\n");

        message_vision(CYN "$n" CYN "歪著頭想了一會，對$N" CYN "道：那"
                       "就勞駕你把刺青紋在我的" + arg + "上吧！\n" NOR,
                       this_object(), me);

        if (member_array(arg, query_temp("item/types")) == -1 ||
            undefinedp(body_type[arg]))
        {
                message_vision(CYN "$N" CYN "看了看$n" CYN "，鄙夷的冷"
                               "笑了一聲。\n" NOR, this_object(), me);
                return 1;
        }

        if (objectp(money = query_temp("item/money")))
                destruct(money);

        set_temp("item/status", "look_working");
        set_temp("item/status", "waiting", me);

        ob = query_temp("item/accept");

        message_sort(HIC "\n$N" CYN "點了點頭，對$n" CYN "說道：我們"
                     "這就開始吧，你躺到那邊的床上去，別亂動。$N"
                     HIC "說完便轉過身去，隨手將" + ob->name() + HIC
                     "浸入身後的水盆，待" + ob->name() + HIC "完全濕"
                     "透後，再小心翼翼地從水中取出，輕輕蒙在$n" HIC
                     "的" + arg + "之上。\n\n" NOR, this_object(), me);

        // 為已經刺了青的部位記號
        tattooed=query("tattoo/tattoo", me);

        if (! arrayp(tattooed))
                tattooed = ({ });

        tattooed -= ({ arg });
        tattooed += ({ arg });
        set("tattoo/tattoo", tattooed, me);

        // 增加不同部位的刺青描述
        tlong=query("tattoo_long", ob);

        switch (arg)
        {
        case "臉部":
                set("tattoo/face_long", tlong, me);
                break;
        case "胸口":
                set("tattoo/chest_long", tlong, me);
                break;
        case "後背":
                set("tattoo/back_long", tlong, me);
                break;
        case "左臂":
                set("tattoo/leftarm_long", tlong, me);
                break;
        case "右臂":
                set("tattoo/rightarm_long", tlong, me);
                break;
        default:
                set("tattoo/buttock_long", tlong, me);
                break;
        }

        // 增加圖騰提供的後天屬性記號
        if( query("tattoo_str", ob) )
                addn("tattoo/tattoo_str",query("tattoo_str",  ob), me);

        if( query("tattoo_int", ob) )
                addn("tattoo/tattoo_int",query("tattoo_int",  ob), me);

        if( query("tattoo_con", ob) )
                addn("tattoo/tattoo_con",query("tattoo_con",  ob), me);

        if( query("tattoo_dex", ob) )
                addn("tattoo/tattoo_dex",query("tattoo_dex",  ob), me);

        if( query("tattoo_per", ob) )
                addn("tattoo/tattoo_per",query("tattoo_per",  ob), me);

        // 增加圖騰提供的特殊技能
        special=query("tattoo_special", ob);
        if (special)
        {
                set("special_skill/"+special, 1, me);
                set("tattoo/special/"+special, 1, me);
        }

        // 執行刺青的過程描述
        me->start_busy(bind((: call_other, __FILE__, "tattoo" :), me));

        remove_call_out("time_out");
        destruct(ob);
        return 1;
}

int tattoo(object me)
{
        object ob;
        string msg;
        int finish;

        if( !query_temp("tattoo/step", me) )
                set_temp("tattoo/step", 1, me);

        finish = 0;
        switch(query_temp("tattoo/step", me) )
        {
        case 1:
                msg = "青□子走進內堂，端出一個檀木沉香盒，輕輕拈出一根銀針。";
                break;
        case 2:
                msg = "接著青□子將$N的身體擺放端正，再沿著圖騰中的紋樣施針。";
                break;
        case 3:
                msg = "只見青□子掌出如風，每一針皆是一沾即過，來去極為迅捷。";
                break;
        case 4:
                msg = "不多時，紋樣的輪廓已被青□子勾勒出來，和圖騰分毫不差。";
                break;
        case 5:
                msg = "又一會，$N刺青上的紋樣漸漸清晰了起來，與肌膚融為一體。";
                break;
        case 6:
                msg = "你不禁感嘆青□子的針法精奇，刺下千多針竟不見有血湧出。";
                break;
        case 7:
                msg = "青□子接著從盒子裡取出十八色瓷瓶，分取粉末放入色盤中。";
                break;
        case 8:
                msg = "青□子用指甲尖輕輕挑出各色粉末，再分別彈入$N刺青之上。";
                break;
        case 9:
                msg = "過得良久，彈在刺青上的各色粉末已經漸漸滲入了$N的肌膚。";
                break;
        case 10:
                msg = "刺青上的顏色慢慢顯露了出來，色彩明艷，與圖騰更無二致。";
                break;
        case 11:
                msg = "只見刺青上的紋樣精雕細琢，栩栩如生，似要沖關欲出一般。";
                break;
        case 12:
                msg = "青□子凝視許久，點了點頭，輕輕拂去了刺青上剩余的粉末。";
                break;
        default:
                msg = "青□子對$N說道：圖騰上的紋樣已經都幫你刺好了，起身吧。";
                finish = 1;
                break;
        }
        msg += "\n";

        msg = replace_string(msg, "$N", "你");
        msg = replace_string(msg, "$n", name());
        message("vision", HIG + msg + NOR, me);

        if (finish)
        {
                if (objectp(ob = present("qingyang zi", environment(me))))
                {
                        delete_temp("item", ob);
                        message_vision(HIC "\n$N" HIC "對$n" HIC "說道："
                                       "錢我收了，刺青則幫你紋了，從此你"
                                       "我兩無相欠。\n" NOR, ob, me);
                }

                delete_temp("item", me);
                delete_temp("tattoo/step", me);
                tell_object(me, HIY "\n刺青結束後，你感到身體似乎有了某"
                                "種奇特的變化。\n" NOR);
                return 0;
        }
        addn_temp("tattoo/step", 1, me);
        return 1;
}

void time_out(object me, object ob)
{
        object money;
        int at_present;

        money = query_temp("item/money");

        if (! objectp(me))
                me = find_player(query_temp("item/player_id"));

        if (! objectp(me) || environment(me) != environment())
        {
                command("say 奇怪，剛才那位客人呢？怎麼這就走了？\n");
                at_present = 0;
        } else
        {
                command("say 你慢慢猶豫吧，我可不能跟你耗著！想好再來吧！");
                at_present = 1;
        }

        delete_temp("item");
        if (objectp(me))
                delete_temp("item", me);

        if (money)
        {
                if (at_present)
                        command("give"+query("id", money)+
                                "to"+query("id", me));

                if (environment(money) == this_object())
                        command("drop"+query("id", money));
        }

        if (ob)
        {
                if (at_present)
                        command("give"+query("id", ob)+
                                "to"+query("id", me));

                if (environment(ob) == this_object())
                        command("drop"+query("id", ob));
        }
}