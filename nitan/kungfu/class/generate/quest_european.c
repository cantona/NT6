// european.c 西洋人
#include <ansi.h>

inherit NPC;

string *all_jiuming = ({
        "$n狠狠地給了$N一個大嘴巴，瞪紅了眼睛，一副要拼命的樣子。\n",
        "$N一把揪住$n的衣領，揮舞著兵器大聲的吼叫，$n嚇得話都說不出來。\n",
        "$n偷偷從$N腦後狠命敲了一木棍，$N吼叫著回轉身，搖搖晃晃的朝$n撲去。\n",
        "$N一腳踹開大門，沖進$n家裡，翻箱倒櫃到處亂搜。\n",
        "$n被$N一刀砍中胳膊，驚怒交加，疼痛之下更是不由的大聲慘呼！\n",
        "$n一路奔跑，企圖甩開身後追殺自己的$N，一邊扯著嗓子大喊『救命！』\n",
        "$N殺氣騰騰地提著滴血的兵器，一個跨步就沖到$n面前，劈頭蓋臉地砍將上去。\n",
        "$n和$N打作一團，體力不支漸落下風，牙齒緊咬，怒目圓睜。\n",
        "$N剛從門口消失，$n就從桌子底下爬起來，沖到窗口就大喊：『救命啊！』\n",
        "$N高舉兵器沖著$n吼叫：『把你所有的錢財通通給我交出來，否則我就一刀砍死你！』\n",
        "$N揮舞著兵器高聲叫囂：『想活命的就把錢財都交出來！別讓我等煩了！』\n",
        "$n帶著哭腔大聲喊叫：『救命啊，誰來救救我啊！』\n",
        "$N姦笑著一巴掌將$n打飛出去，搶過了包裹迫不及待的翻過來尋找財物。\n",
        "$N一腳踹開$n，滿臉貪婪的朝錢箱撲了過去。\n",
        "$N一刀將$n砍傷在地，回手一刀又將一只大狼狗給劈成兩半。\n",
        "$n一邊躲閃著$N的攻擊，一邊後退，氣喘吁吁，眼看快支撐不住了。\n",
});

string *woman_jiuming = ({
        "$N姦笑著沖$n說：『你叫啊，你叫啊，叫破喉嚨也沒人救得了你！』\n",
        "$N一把摟住$n，色迷迷的上下到處亂摸，$n哭叫得聲嘶力竭。\n",
        "$N滿臉淫笑，逼近$n，$n嚇得尖聲驚叫...\n",
        "$N眯著雙眼上下打量$n，一步一步地逼近上前...\n",
        "$n雙拳亂舞，拼命想阻住$N，腳下一滑，摔倒在地，尖聲驚叫起來。\n",
        "$n聲嘶力竭地喊叫：『救命啊，快來救救我啊！』\n",
        "$N一個巴掌將$n抽倒在地，淫笑著撲了上去。\n",
        "$N收起兵器，朝$n飛身撲去，$n嚇得大聲喊叫，四處躲閃。\n",
});

void random_move();
void destruct_me();
int is_stay_in_room() { return 1; }
void jiuming(object npc,object enemy);

void create()
{
        set_name("西洋人", ({ "european" }));
        set("long", "一個西洋人。\n");
        set("gender", "男性");
        set("age", 20);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        // the follow 5 setting has no use
        set("max_qi", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 100);
        set("shen", -1000);

        set("combat_exp", 3000000);
        set("scale", 100);

        set_skill("force", 1);
        set_skill("xiyang-neigong", 1);
        set_skill("dodge", 1);
        set_skill("xiyang-boji", 1);
        set_skill("parry", 1);
        set_skill("xiyang-jian", 1);
        set_skill("sword", 1);

        map_skill("sword", "xiyang-jian");
        map_skill("force", "xiyang-neigong");
        map_skill("dodge", "xiyang-boji");
        map_skill("parry", "xiyang-jian");

        set("rank_info/rude", "紅毛鬼");

        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("scale", 100);
        set_temp("born_time", time());
        add_money("silver",50);
        keep_heart_beat();
        setup();

        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/xiyang-sword")->wield();
}

int accept_fight(object ob)
{
        command("say 很好！那我就不客氣了。");
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        command("say 哼！什麼人？");
        kill_ob(ob);
        return 1;
}

void random_move()
{
        int all_enemy;
        object env,*inv,npc;

        if (time() - query_temp("born_time") > 600)
        {
                destruct_me();
                return;
        }

        all_enemy = GROUP_QUEST_D->query_enemy() + 1;
        if (all_enemy < 2) all_enemy = 2;

        if (!GROUP_QUEST_D->query_running_quest() &&
            objectp(env = environment(this_object())) &&
            random(all_enemy) == all_enemy/2)
        {
                inv = all_inventory(env);
                inv -= ({ this_object() });
                inv = filter_array(inv, (: living($1) :));
                if (inv)
                        inv=filter_array(inv,(:!userp($1) && query("race", $1) == "人類":));
                if (inv)
                        inv = filter_array(inv, (: strsrch(base_name($1),"/kungfu/class/generate/") == -1 :));
                if (inv)
                        inv=filter_array(inv,(:query("combat_exp", $1) <= 500000:));
                if (inv)
                        inv=filter_array(inv,(:!query("family", $1):));
                if (inv && sizeof(inv))
                {
                        npc = inv[random(sizeof(inv))];
                        jiuming(npc,this_object());
                }
                inv = 0;
        }
        GROUP_QUEST_D->random_move(this_object());
}

void destruct_me()
{
        message_vision("$N急急忙忙的走了。\n", this_object());
        destruct(this_object());
}

int filter_listener(object ob)
{
        if( !query("channels", ob))return 0;
        //if( member_array("task",query("channels", ob)) == -1)return 0;
        if( query("env/no_task", ob) )return 0;
        return 1;
}

void jiuming(object npc,object enemy)
{
        object *listeners;
        string msg;

        if (!npc || !enemy)
                return;

        if( query("gender", npc) == "女性" && random(2) )
                msg = woman_jiuming[random(sizeof(woman_jiuming))];
        else
                msg = all_jiuming[random(sizeof(all_jiuming))];

        msg = replace_string(msg,"$N",enemy->name());
        msg = replace_string(msg,"$n",npc->name());

        listeners = filter_array(users(), (: filter_listener :));

        message("group_quest",HIR "【外敵】" NOR + WHT + msg + NOR,listeners);
}
