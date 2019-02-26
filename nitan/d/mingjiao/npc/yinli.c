// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// yinli.c 殷離

inherit NPC;
#include <ansi.h>

mixed ask_qianzhu();
mixed ask_he();

string *qianzhu_message = ({
        "千蛛萬毒手雖是一門毒功, 其實它包括指法, 內功, 輕功, 招架在內, 一通百通。\n",
        "練千蛛萬毒手極為費時費力, 非窮畢生之力不可。\n",
        "千蛛萬毒手練起來極為枯燥, 要不是為了報仇, 我才不練呢。\n",
        "千蛛萬毒手入門容易, 可越到後來越難練, 我也不過練了百來只花蛛而已。\n",
        "修練千蛛萬毒手時兇險萬分, 非有一定的內力為基礎不可。\n",
        "江湖人物只知道打打殺殺, 實戰經驗雖豐富, 可又怎麼奈何得了我的千蛛萬毒手?\n",
        "咱們練千蛛萬毒手的, 只求毒功深湛, 跟實戰經驗倒沒什麼關係。\n",
        "千蛛萬毒手一旦施展, 無藥可救, 只有中毒者自己靠深厚的內力化解。\n",
        "千蛛萬毒手乃是我的家傳武功, 雖説沒什麼名氣, 可等我練成了, 連張無忌怕也擋不住我一指。\n",
        "練了千蛛萬毒手以後容貌盡毀, 那是不必説了。\n",
        "要説功夫深哪, 練個幾千只花蛛也不算多。\n",
        "等練到幾百只毒蜘蛛以後，突襲(tuxi)敵人的效果可就利害了。\n",
});

void create()
{
        set_name("殷離", ({ "yin li", "yin", "li" }));
        set("gender", "女性");
        set("age", 19);
        set("long","她是個十七八歲的少女，荊釵布裙，是個鄉村貧女，\n"+
                   "面容黝黑，臉上肌膚浮腫，凹凹凸凸，生得極是醜陋，\n"+
                   "只是一對眸子頗有神采，身材也是苗條纖秀。\n");
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 26);
        set("per", 6);
        set("unique", 1);
        set("location", 1);
        set("combat_exp", 300000);
        set("shen", -500);
        set("attitude", "peaceful");
        set("max_qi",600);
        set("max_jing",600);
        set("neili",800);
        set("max_neili",800);
        set("jiali",20);
        set_temp("no_return", 1);
        set_skill("unarmed", 60);
        set_skill("parry",60);
        set_skill("qingfu-shenfa",60);
        set_skill("dodge", 60);
        set_skill("throwing",60);
        set_skill("duoming-jinhua",60);
        set_skill("qianzhu-wandushou", 60);
        set_skill("finger", 60);
        set_skill("force",60);
        set_skill("shenghuo-shengong",60);
        map_skill("force","shenghuo-shengong");
        map_skill("finger","qianzhu-wandushou");
        map_skill("dodge","qingfu-shenfa");
        map_skill("throwing","duoming-jinhua");
        map_skill("parry","duoming-jinhua");
        prepare_skill("finger","qianzhu-wandushou");
        set("inquiry", ([
                "千蛛萬毒手" : (: ask_qianzhu :),
                "報仇" : "哼, 我要叫天下負心薄辛的男子個個不得好死。\n",
                "殷野王" : "他是我爹。\n",
                "殷天正" : "他是我爺爺。\n",
                "殷素素" : "他是我姑姑。\n",
                "金花婆婆" : "唉, 婆婆去波斯啦。\n",
                "銀葉先生" : "銀葉先生我也沒見過。\n",
                "胡青牛" : "哼, 這個臭醫生, 要不是他, 銀葉先生也不會死。\n",
                "王難姑" : "嗯, 難姑的毒技是極高的, 可我的千蛛萬毒手卻也另有一功。\n",
                "周芷若" : "小姑娘人長的漂亮, 可心眼不怎麼好。\n",
                "趙敏" : "趙姑娘心機敏捷, 令人佩服。\n",
                "張無忌" : "這沒良心的、狠心短命的死鬼, 我到處都找不到他。\n",
                "錦盒" : (: ask_he :), 

        ]));
        
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        setup();
        carry_object("/d/mingjiao/obj/green-cloth")->wear();
        carry_object("/clone/weapon/feihuangshi")->wield();
}

mixed ask_qianzhu() 
{
        object he, player = this_player(), me = this_object();
        int flags, level, idx;

        if (player->is_busy()) 
        {
                return "剛問完又來，你有沒有聽懂我説的啊？\n";
        }

        flags=query_temp("qianzhu-wandushou/flags", player);
        level = player->query_skill("qianzhu-wandushou", 1);

        if (flags >= 1023 && level < 10) 
        {
                command("say 好吧, 看你這麼誠心, 我就教你這門功夫吧。\n");
                player->set_skill("qianzhu-wandushou", 10);
                message_vision("$N指點了$n一些基本的千蛛萬毒手。\n", me, player);
                tell_object(player, "師傅領進門, 修行看各人, 今後就你自己練啦。如果沒有錦盒，可以來問我要。\n");
                return 1;
        }else 
        {
                player->start_busy(1 + random(3));
                idx = random(sizeof(qianzhu_message));
                if (idx < 10) 
                {
                        flags = flags | (1 << idx);
                   }
                set_temp("qianzhu-wandushou/flags", flags, player);
                return qianzhu_message[idx];
        }
}

mixed ask_he() 
{
        object player = this_player();
        object he;

        if (player->query_skill("qianzhu-wandushou", 1) < 10) 
        {
                return "你我素不相識, 問來也不冒昧麼？\n";
        }

        if (objectp(present("jin he", player))) {
                return "你已經有錦盒了。\n可以找個偏僻的所在, 抓一隻毒蜘蛛, 自己就可以修練啦。\n";
        }
        he = new ("/clone/misc/jinhe");
        he->move(player);
        tell_object(player, "你怎麼這麼不小心, 好吧, 我再給你一個。\n");
        message_vision("$N給$n一個錦盒。\n", this_object(), player);
        return 1;
}
