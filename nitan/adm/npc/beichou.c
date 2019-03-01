// This program is a part of NT MudLIB

#include <ansi.h>

inherit NPC;

string *quest_msg = ({
        HIW "北醜長長的出了一口氣，然後掏出一張英雄貼來遞到你面前……\n" NOR,
        HIW "北醜說道：聚賢莊這個名字，你應該不會陌生吧。\n" NOR,
        HIW "前些時候，遊氏兄弟和薛神醫在江湖上廣發英雄帖，召集天下英雄豪傑共赴聚賢莊，參加武林大會。\n" NOR,
        HIW "這張帖子是給你的，但是你向來四海為家，居無定所，聚賢莊發派帖子的下人就把你的英雄貼送到我這裡來了，希望我可以找到你。\n" NOR,
        HIW "至于這次武林大會究竟是為何事，老朽我也不是很清楚，只聽說和丐幫有莫大的關系，江湖上的風言耳語，傳來傳去的，可以相信的已經不多了。\n" NOR,
        HIW "你現在去洛陽找丐幫的徐長老，他會告訴你具體情況的。\n" NOR,
});

int ask_juxianzhuang();

void create()
{
        set_name("北醜", ({ "bei chou", "bei", "chou", "xizi" }));
        set("long", @LONG
這是一個身著戲子打扮的瘦小老頭，長得尖嘴
猴腮，天生一副姦相。誰人能知這便是當今武
林中號稱「南賢北醜」戲子北醜。雖其排名在
南賢之下，但卻也是南賢生平最畏懼之人。
LONG);
        set("nickname", HIW "北戲子" NOR);
        set("title", HIC "武林泰鬥" NOR);
        set("gender", "男性" );
        set("age", 68);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);
        set("level", 100);

        set_skill("dodge", 500);
        set_skill("unarmed", 500);
        set_skill("force", 500);
        set_skill("parry", 500);
        set_skill("sword", 500);
        set_skill("poison", 500);
        set_skill("medical", 500);
        set_skill("hand", 500);
        set_skill("strike", 500);
        set_skill("staff", 500);
        set_skill("finger", 500);
        set_skill("claw", 500);
        set_skill("blade", 500);
        set_skill("pixie-jian", 500);
        set_skill("literate", 500);
        set_skill("taoism", 500);
        set_skill("buddhism", 500);
        set_skill("jiuyang-shengong", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("xuanming-zhang", 500);
        set_skill("jiuyin-baiguzhao", 500);
        set_skill("dugu-jiujian", 500);
        set_skill("qianzhu-wandushou", 500);
        set_skill("ranmu-daofa", 500);
        set_skill("dagou-bang", 500);
        set_skill("shaolin-yishu", 500);
        set_skill("wudu-qishu", 500);
        set_skill("throwing", 500);
        set_skill("mantian-xing", 500);
        set_skill("idle-force", 500);
        set_skill("sad-strike", 500);

        map_skill("unarmed", "sad-strike");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("strike", "xuanming-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("sword", "dugu-jiujian");
        map_skill("blade", "ranmu-daofa");
        map_skill("staff", "dagou-bang");
        map_skill("throwing", "mantian-xing");
        map_skill("poison", "wudu-qishu");
        map_skill("medical", "shaolin-yishu");

        prepare_skill("unarmed", "sad-strike");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.po" :),
                (: perform_action, "blade.zhenyan" :),
                (: perform_action, "blade.huo" :),
                (: perform_action, "staff.wugou" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.ban" :),
                (: perform_action, "unarmed.xiao" :),
                (: perform_action, "parry.nuoyi" :),
                (: perform_action, "dodge.lingbo" :),
                (: perform_action, "throwing.shan" :),
                (: perform_action, "hand.zhugu" :),
                (: perform_action, "strike.wuji" :),
                (: perform_action, "finger.six" :),
                (: perform_action, "finger.zhongheng" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));

        set("inquiry", ([
                "幫派"  :"要創建幫派請先組隊，人數不能少于五個，然後 team bunch <幫派名> 就可以了。\n",
                "英雄貼": (: ask_juxianzhuang :),
                "挑戰BOSS" : "想挑戰BOSS？輸入 ask bei chou about <BOSS名稱> 即可進入挑戰空間", 
        ]) );

        set("chat_chance", 1);
        set("chat_msg",({
                CYN "北醜賊眯眯的說：天算地算不如人算，可是再怎麼算戲子我都知道。\n" NOR,
        }));

        setup();
        carry_object("/clone/cloth/cloth")->wear();

/*
        if (! clonep(this_object()))
        {
                move("/d/xiakedao/haibin");
                message_vision(CYN "\n$N" CYN "笑嘻嘻道：來了來了，戲子我來了。\n"
                               NOR, this_object());
                set("startroom", "/d/xiakedao/haibin");
        }
*/
}

void init()
{
        ::init();
        add_action("do_join", "join");
}

int ask_juxianzhuang()
{
        object me = this_player();
        call_out("quest_stage", 0, me, 0);
        return 1;
}

void quest_stage(object ob, int stage)
{

        if (! ob || ! present(ob)) return;

        tell_object(ob, quest_msg[stage]);
        if (++stage < sizeof(quest_msg))
        {
                call_out( "quest_stage", 1, ob, stage );
                return;
        }
        set_temp("juxianzhuang_step", 1, ob);
}

mixed accept_ask(object me, string arg)
{
        int valid;
           
        if( !arg || arg == "" || arg == "all" )
                return 0;
        
        if( arg == "挑戰BOSS" || arg == "挑戰boss" || arg == "BOSS" || arg == "boss" )
        {
                write(HIW"想要挑戰BOSS？輸入 ask shizhe about <BOSS名稱> 即可進入挑戰空間。\n"NOR);
                return 1;
        }
        
        valid = FUBEN_D->valid_enter(me, arg); 
        if( valid >=1 )
                FUBEN_D->enter_fuben(me, arg);
        else {
                if( valid == 0 )
                        write("您實戰經驗不足，進挑戰BOSS恐有不測，還是先歷練一下再來吧。\n");
                else if( valid == -1 )
                        write("您經驗太高了，就不要進去欺負那些可憐的小怪物了吧。\n");
                else if( valid == -2 )
                        write("遊戲中目前並沒有開放該BOSS，請您核對後再試。\n");
                else if( valid == -3 )
                        write("挑戰BOSS限制IP多重進入，您已經超過最高上限。\n");
                else if( valid == -4 )
                        write("該BOSS被巫師關閉，您暫時無法進入。\n");
                else if( valid == -5 )
                        write("你離上次挑戰該BOSS的時間太短，請休息會再來。\n");
                else if( valid == -6 )
                        write("該BOSS必須組隊才能進入。\n");
                else if( valid == -7 )
                        write("你的隊伍人數超過該BOSS規定的上限。\n");
                else if( valid == -8 )
                        write("該BOSS要求單人挑戰，您必須解散隊伍方可進入。\n");
        }        
        return 1;
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        command("say 哼！不知死活。");
        command("exert powerup");
        command("exert sword");
        ::fight_ob(ob);
}

int accept_fight(object who)
{
        command("say 沒興趣。");
        return 0;
}

int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是眼前一花，看不太清楚。\n");
}

varargs void die(object killer)
{
        full_self();
        return;
}

void unconcious()
{
        die();
}
