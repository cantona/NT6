#include <ansi.h>
#define RIDE_CMD        "/cmds/std/ride" 
inherit NPC;

int give_quest(string arg);

void create()
{
        set_name("大宋監軍", ({"jian jun", "jian", "jun"}));
        set("title", HIR "大內太監" NOR);
        set("gender", "無性");
        set("age", random(20) + 20);

        set("long", "這是一個京城皇宮中的一名太監，負責抗擊蒙古軍隊入侵大宋的監軍。\n");
        set("combat_exp", 800000);
        set("attitude", "peaceful");
        set("max_qi", 3000);
        set("max_jing", 2000);
        set("max_neili", 2000);
        set("neili", 1000);
        set("no_get", 1);
        set("inquiry", ([ 
                "領取任務" : "格式：lingming houqin-baozhang",
        ]));

        setup();
        carry_object("clone/cloth/cloth")->wear();
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
                               "近來軍中幾無能戰之師，\n命你加緊訓練一支精銳步兵，以備不時之需，" +
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
                               "近來軍中幾無能戰之師，\n命你加緊訓練一支精銳騎兵，以備不時之需，" +
                               "不得有誤！\n" NOR, me, ob);

                set_temp("title", HIR"大宋車騎營統領"NOR, ob);
                if (! present("zhan ma", ob))
                {
                        horse = new("/d/city2/song/horse");
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
                               "近來軍中幾無能戰之師，\n命你加緊訓練一支精銳弓箭手，以備不時之需，" +
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
                if( WAR_D->query_moneys() < 15000000 )
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
                else if( WAR_D->query_soilders(me) < 40000 )
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
                else if( WAR_D->query_weapons(me) < 80000 )
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
                else if( WAR_D->query_arrows(me) < 80000 )
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
                else if( WAR_D->query_horses(me) < 20000 )
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
                else if( WAR_D->query_stones(me) < 40000 )
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
                else if( WAR_D->query_economy(me) < 1000000 )
                {
                        message_vision(HIR "$N略一沉思，從案前抽出一枚令箭道：“$n聽令，" +
                               "近來蒙古騎兵常騷擾我大宋襄陽城，\n命你火速率部，趕去襄陽駐守城池" +
                               "，如有延誤，軍法論處！\n" NOR, me, ob);
                        set_temp("title", HIY"大宋後防營統領"NOR, ob);

                        set_temp("warquest/guard", 1, ob);
                        set_temp("warquest/quest", "守衛襄陽，穩固後方", ob);
                        // ob->command("guard");
                        ob->move("/d/wuguan/guofu_dating");
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
                message_vision(CYN "$N" CYN "大怒道：“看來你是真的想找死！”，說罷一掌把$n" CYN
                               "劈倒在地。\n" NOR, this_object(), me);
                me->unconcious();
                return -1;
        }
}
