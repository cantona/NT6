// guojing.c 郭靖

#define RIDE_CMD        "/cmds/std/ride"  
inherit NPC;
#include <ansi.h>

int give_quest(string arg); 
void create()
{
        set_name("郭靖", ({"guo jing", "guo", "jing"}));
        set("nickname", HIY "北俠" NOR);
        set_temp("title", HIW"大宋兵馬大元帥"NOR);
        set("gender", "男性");
        set("age", 41);
        set("long",
                "他就是人稱北俠的郭靖，既是蒙古成吉思汗的金刀駙馬，又是\n"
                "江南七怪、全真派馬鈺道長、「北丐」洪七公和「老頑童」周\n"
                "伯通等人的徒弟，身兼數門武功。他身着一件灰色長袍，體態\n"
                "魁梧，敦厚的面目中透出一股威嚴。\n");
        set("attitude", "friendly");
        set_max_encumbrance(100000000);
        set_temp("warquest/party", "song");
        set("per", 20);
        set("str", 40);
        set("int", 20);
        set("con", 30);
        set("dex", 25);
        set("chat_chance", 1);
        set("chat_msg", ({
                "郭靖歎了口氣道：“蒙古兵久攻襄陽不下，一定會再出詭計，蓉兒又不在身邊，這....\n",
                "郭靖説道：“華箏公主近來不知可好，抽空一定要回大漠去看看她。\n",
        }));

        set("inquiry", ([
                "周伯通" : "你見到我周大哥了？他現在可好？\n",
                "老頑童" : "周大哥一貫這樣，沒點正經！\n",
                "洪七公" : "師父除了吃，就是喜歡玩。到處玩，還是為了找吃的。\n",
                "黃藥師" : "那是我泰山大人。他雲遊四海，神龍見首不見尾的。\n",
                "一燈大師" : "在下對大師好生感激。\n",
                "歐陽鋒" : "這個老毒物，害死我六位師父，一待襄陽事了，決不與他干休。\n",
                "黃蓉"   : "蓉兒是我的愛妻，你問她做甚？\n",
                "蓉兒"   : "蓉兒就是蓉兒了。你問這麼多幹嘛？\n",
                "郭芙"   : "這個女兒，又笨又不聽話。\n",
                "郭襄"   : "襄兒生於亂世，這輩子又多艱厄。但願她能快樂一世。\n",
                "郭破虜" : "那是我的小兒子。\n",
                "楊過"   : "過兒確實有出息。\n",
                "馬鈺"   : "馬道長於我有半師之誼。\n",
                "丘處機" : "邱道長義薄雲天，是真豪傑。\n",
                "柯鎮惡" : "那是我大師父。\n",
                "朱聰"   : "那是我二師父。\n",
                "韓寶駒" : "那是我三師父。\n",
                "南希仁" : "那是我四師父。\n",
                "張阿生" : "那是我五師父。\n",
                "全金髮" : "那是我六師父。\n",
                "韓小瑩" : "那是我七師父。\n",
                "丐幫"   : "丐幫英雄幾百年了，守衞襄陽多虧了他們。\n",
                "拜師"   : "現在蒙古人圍攻襄陽，我哪有心情收徒啊！\n",
                "領取任務" : "格式：lingming houqin-baozhang",
                ]));

        set("qi", 10000);
        set("max_qi", 10000);
        set("jing", 8000);
        set("max_jing", 8000);
        set("neili", 34000);
        set("max_neili", 34000);
        set("jiali", 500);

        set("combat_exp", 25000000);
        set("score", 200000);

        set_skill("force", 400);                // 基本內功
        set_skill("huntian-qigong", 400);       // 混天氣功
        set_skill("strike", 400);               // 基本拳腳
        set_skill("dragon-strike", 400);        // 降龍十八掌
        set_skill("dodge", 400);                // 基本躲閃
        set_skill("xiaoyaoyou", 400);           // 逍遙遊
        set_skill("parry", 400);                // 基本招架
        set_skill("arrow", 400);
        set_skill("lianzhu-arrow", 400);

        map_skill("arrow", "lianzhu-arrow");
        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dragon-strike");
        prepare_skill("strike", "dragon-strike");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "dodge.xian" :),
                (: perform_action, "strike.hui" :),
                (: perform_action, "strike.lei" :),
                (: perform_action, "strike.leiting" :),
                (: perform_action, "strike.pai" :),
                (: perform_action, "strike.qin" :),
                (: perform_action, "strike.sanhui" :),
                (: perform_action, "strike.xianglong" :),
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shengang" :),
                (: exert_function, "shexin" :),
        }) );

        setup();

        carry_object("/clone/misc/cloth")->wear();
}


void init()
{

        add_action("give_quest", ({ "lingming" }));
}



int give_quest(string arg)
{
        object me, ob, ling;
        object horse;
        int count;
        
        ob = this_player();
        me = this_object();
        
        if (! arg)
        {
                tell_object(ob, "你想要領命去幹什麼事情？！\n");
                return 1;
        }
        
        if( query_temp("warquest/party", ob) != "song" )
        {
                tell_object(ob, "你還沒有參加宋軍，如何領命啊？！\n");
                return 1;
        }
                
        switch(arg)
        {
        case "train-infantry":
        case "xunlian-bubing":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "infantry" )
                {
                        tell_object(ob, "你已經另有他職了！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中幾無能戰之師，\n命你加緊訓練一支精鋭步兵，以備不時之需，" +
                               "不得有誤！\n" NOR, me, ob);
                set_temp("title", HIW"大宋步兵營統領"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/train", "infantry", ob);
                set_temp("warquest/quest", "訓練步兵，作戰準備", ob);
                ob->command("drill");
                break;

        case "xunlian-qibing":
        case "train-cavalry":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "cavalry" )
                {
                        tell_object(ob, "你已經另有他職了！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中幾無能戰之師，\n命你加緊訓練一支精鋭騎兵，以備不時之需，" +
                               "不得有誤！\n" NOR, me, ob);

                set_temp("title", HIR"大宋車騎營統領"NOR, ob);
                if (! present("zhan ma", ob))
                {
                        horse = new("/maze/battle3/song/horse");
                        if (horse->move(environment(ob)))
                                RIDE_CMD->do_ride(ob, horse);
                        else destruct(horse);
                }
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/train", "cavalry", ob);
                set_temp("warquest/quest", "訓練騎兵，作戰準備", ob);
                ob->command("drill");
                break;

        case "train-archer":
        case "xunlian-gongnu":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "archer" )
                {
                        tell_object(ob, "你已經另有他職了！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中幾無能戰之師，\n命你加緊訓練一支精鋭弓箭手，以備不時之需，" +
                               "不得有誤！\n" NOR, me, ob);
                set_temp("title", HIB"大宋神弩營統領"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }

                set_temp("warquest/train", "archer", ob);
                set_temp("warquest/quest", "訓練弓兵，作戰準備", ob);
                ob->command("drill");
                break;
                
        case "houqin-baozhang":
                count = 600000;
                if( WAR_D->query_moneys() < 600000 )
                {
                        message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中糧草匱乏，\n命你火速率部，在半月內將京師供應之糧草押解" +
                               "至軍中，如有延誤，軍法論處！\n" NOR, me, ob);

                        set_temp("title", HIY"大宋軍備營統領"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "forage", ob);
                        set_temp("warquest/quest", "押運糧草，補充軍備", ob);
                        ob->command("stock");
                } 
                else if( WAR_D->query_soilders(me) < 2000 )
                {        
                        message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中兵員匱乏，\n命你火速率部，趕去襄陽城內招募新兵" +
                               "至軍中，如有延誤，軍法論處！\n" NOR, me, ob);
                        set_temp("title", HIY"大宋軍備營統領"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "enlist", ob);
                        set_temp("warquest/quest", "招募新兵，補充兵源", ob);
                        WAR_D->change_moneys(-count);
                        ob->command("stock");
                }
                else if( WAR_D->query_weapons(me) < 4000 )
                {               
                        message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中兵器和盔甲匱乏，\n命你火速率部，趕去襄陽城內採購兵器和盔甲" +
                               "至軍中，如有延誤，軍法論處！\n" NOR, me, ob);
                        set_temp("title", HIY"大宋軍備營統領"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "weapon", ob);
                        set_temp("warquest/quest", "購置兵甲，補充軍備", ob);
                        WAR_D->change_moneys(-count);
                        ob->command("stock");
                }
                else if( WAR_D->query_arrows(me) < 2000 )
                {
                        message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍營箭樓羽箭匱乏，\n命你火速率部，趕去襄陽城內採購羽箭" +
                               "至軍中，如有延誤，軍法論處！\n" NOR, me, ob);
                        set_temp("title", HIY"大宋軍備營統領"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "arrow", ob);
                        set_temp("warquest/quest", "購置羽箭，補充軍備", ob);
                        WAR_D->change_moneys(-count);
                        ob->command("stock");
                }
                else if( WAR_D->query_horses(me) < 2000 )
                {
                        message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中戰馬匱乏，\n命你火速率部，趕去襄陽城內採購戰馬" +
                               "至軍中，如有延誤，軍法論處！\n" NOR, me, ob);
                        set_temp("title", HIY"大宋軍備營統領"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "horse", ob);
                        set_temp("warquest/quest", "購置戰馬，補充軍備", ob);
                        WAR_D->change_moneys(-count);
                        ob->command("stock");
                }
                else if( WAR_D->query_stones(me) < 2000 )
                {
                        message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中滾石和檑木匱乏，\n命你火速率部，趕去襄陽城內採購石頭和木材" +
                               "至軍中，如有延誤，軍法論處！\n" NOR, me, ob);
                        set_temp("title", HIY"大宋軍備營統領"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "stone", ob);
                        set_temp("warquest/quest", "購置石木，補充軍備", ob);
                        WAR_D->change_moneys(-count);
                        ob->command("stock");
                }
                else if( WAR_D->query_economy(me) < 1200000 )
                {
                        message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來蒙古騎兵常騷擾我大宋襄陽城，\n命你火速率部，趕去襄陽駐守城池" +
                               "，如有延誤，軍法論處！\n" NOR, me, ob);
                        set_temp("title", HIY"大宋後防營統領"NOR, ob);

                        set_temp("warquest/guard", 1, ob);
                        set_temp("warquest/quest", "守衞襄陽，穩固後方", ob);
                        // ob->command("guard");
                        ob->move("/d/xiangyang/guofuting");
                }
                else
                {
                        message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來軍中糧草匱乏，\n命你火速率部，在半月內將京師供應之糧草押解" +
                               "至軍中，如有延誤，軍法論處！\n" NOR, me, ob);

                        set_temp("title", HIY"大宋軍備營統領"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "forage", ob);
                        set_temp("warquest/quest", "押運糧草，補充軍備", ob);
                        ob->command("stock");
                }
                break;
        default:
                tell_object(ob, "你想要領命做什麼事情？！\n");
                return 1;
        }

        message_vision("眾將領大聲應道：末將遵命！！\n", me, ob);
        return 1;
}

int accept_hit(object me)
{
        if (playerp(me))
        {
                command("heng");
                command("say 你要想要找死嗎！");
                return 0;
        }
}

int accept_fight(object me)
{
        if (playerp(me))
        {
                command("heng");
                command("say 你要想要找死嗎！");
                return 0;
        }
}

int accept_kill(object me)
{
        if (playerp(me))
        {
                message_vision(CYN "$N" CYN "大怒道：“看來你是真的想找死！”，説罷一掌把$n" CYN
                               "劈倒在地。\n" NOR, this_object(), me);
                me->unconcious();
                return -1;
        }
}

