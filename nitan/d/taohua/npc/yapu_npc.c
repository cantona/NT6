//Cracked by Kafei
// yapu_npc.c 啞僕候選
#include <ansi.h>
#include <room.h>

inherit NPC;
int auto_perform();

void create()
{
        switch( random(7) )
        {
        case 0:
        set_name("小販", ({ "xiao fan", "seller", "fan" }) );
        set("long","這是個小販，別看他長的老老實實，可你別想從他那兒掏便宜。\n");
        set("gender", "男性");
        set("age", 32);
        set("real_name","大盜");
        set("real_long", "這是一個殺人不眨眼的盜匪，憑著一身武藝四處橫行擄掠，殺人放火，無所不為。\n");
        set("real_title", "山寨頭目");
        set("real_menpai", "huashan");
                break;
        case 1:
        set_name("書生", ({ "shu sheng", "sheng" }) );
        set("long","這是個飽讀詩書，卻手無搏雞之力的年輕書生。\n");
        set("gender", "男性");
        set("age", 18 + random(4));
        set("int", 30);
        set("real_name","殺手");
        set("real_long", "他原本是當朝一名宮廷護衞，後來貪圖重賄，變節投靠金國，\n金國朝廷派他暗殺中原官員，手段陰狠歹毒，已有數名將官死在他的手上。\n");
        set("real_title", "金國奸細");
        set("real_menpai", "dajin");
                break;
        case 2:
        set_name("趟子手", ({ "tangzi shou","shou" }) );
        set("gender", "男性");
        set("age", 30);
        set("real_name","惡霸");
        set("long","這是個鏢局趟子手，長得虎背熊腰，一身橫練功夫。\n");
        set("real_long", "他本來是鐵掌幫中的一個無名小卒，乘著門中長輩卧病在牀時殺師叛門，\n搶走本門武功祕訣，練就了一身功夫，恃著武藝精熟，四處為非作歹。\n");
        set("real_title", "鐵掌幫");
        set("real_menpai", "tiezhang");
                break;
        case 3:
        set_name("僧人", ({ "seng ren", "seng"}));
        set("long","這是一位僧人。\n");
        set("gender", "男性");
        set("age", 35);
        set("class", "bonze");
        set("real_name","破戒僧");
        set("real_long", "他曾經拜在一名少林高僧門下，由於不守清規，時常被師父呵斥。\n他武功有成後，因為懷恨在心，居然下手殺死受業恩師，逃出少林寺，投入了西域金剛門。\n");
        set("real_title", "金剛門弟子");
        set("real_menpai", "shaolin");
                break;
        case 4:
        set_name("胡人", ({ "hu ren", "ren", "foreigner" }));
        set("long", "一個金髮碧眼的胡人，正趾高氣揚的吆喝着。\n");
        set("gender", "男性");
        set("age", 30 + random(10));
        set("real_name","蒙古武將");
        set("real_long", "這是一個來自西域番邦的武士，他因為曾在西域偷學得幾樣厲害功夫，\n投身蒙古軍中之後頗受重用，職權也不小。\n他雖然驍勇，個性卻十分殘忍，時常帶兵出外殘殺百姓為樂，令人髮指。\n");
        set("real_menpai", "xiyu");
                break;
        case 5:
        set_name("窮漢", ({ "poor man", "man" }));
        set("gender", "男性");
        set("age", 53);
        set("long", "一個骨瘦如柴，滿臉菜色的窮漢。\n");
        set("real_name","護法喇嘛");
        set("real_long", "他是密宗教中旁支的一名護法喇嘛，由於沉溺武學，向佛之心日淡，\n一日裏暗中竊取寺中武學典籍，殺了看管的同門師兄弟，逃到中原潛心修煉，\n因為好勇鬥狠，經常濫殺無辜，在武林中也是聲名狼藉。\n");
        set("real_title", "密宗旁支");
        set("real_menpai", "mizong");
                break;
        case 6:
        set_name("女孩",({ "girl" }) );
        set("gender", "女性" );
        set("age", 16+random(3));
        set("long", "這是個農家少女，雖然只有十來歲，身材已經開始發育。\n");
        set("real_name","苗疆巫女");
        set("real_long", "她是苗族中一個小部落的巫女，幼時因為好奇而鑽研蠱毒，後來因故投入星宿派，\n將毒技融匯於武功之中，年紀輕輕，造詣竟也不凡。她久與星宿弟子相處，耳濡目染之下，\n行事也變得陰險狡猾，為了煉毒，已平白害死了不少族中同胞。\n");
        set("real_menpai", "miaojiang");
                break;
        }
        set("str", 20);
        set("con", 20);
        set("int", 20);
        set("dex", 20);

        set("attitude", "peaceful");
        set("combat_exp", 10000);
        set("yapu_target",1);
        
        set("chat_chance", 6);
        set("chat_msg", ({ (: random_move :) }));

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: auto_perform :),
        }) ); 

        setup();
        carry_object("/clone/misc/cloth")->wear();
}


int checking(object me, object victim)
{
        victim = this_player();
        if ( !victim ) return 1;
        if (!query("real_face")) return 1;
/*
        if( !victim=find_player(query("th_victim", me) )
         && query("combat_exp", victim)>query("combat_exp", me)){
             message_vision("$N晃了個虛招，狼狽不堪地逃了開去。\n", me);
             destruct(me);
             return 1;
        }
*/
        if ( victim->is_ghost() && living(me)) {
             command("grin");
             command("say 想抓"+RANK_D->query_self_rude(me)+"，那有這麼容易！");
             message_vision("$N冷笑幾聲，揚長而去。\n", me);
             destruct(me);
             return 1; 
        }

        else if( !me->is_fighting() && query("real_face", me) && living(me)){
             command("unarmed corpse");
             command("say 想抓"+RANK_D->query_self_rude(me)+"，那有這麼容易！");
             message_vision("$N冷笑幾聲，揚長而去。\n", me);
             destruct(me);
             return 1;
        }

        remove_call_out("checking");
        call_out("checking", 1, me, victim);
        return 1;
}

int accept_fight(object victim)
{
        object me = this_object();

        if (!query("real_face")) return 1;
        if (!living(me)) return 1;

        if( is_fighting() && query("th_victim", me )
         && query("th_victim", me) != query("id", victim )
         && query("combat_exp", victim)>query("combat_exp", me)){
              command( "say 滾一邊去！" );
              return 0;
        }
        else {
             command("say 哼哼，"+RANK_D->query_self_rude(me)+"就送你上西天去！" );
             me->kill_ob(victim);
             remove_call_out("checking");
             call_out("checking", 1, me, victim);
             return 1;
        }
}

int accept_kill(object victim)
{
        object me = this_object();

        if (!query("real_face")) return 1;
        if (!living(me)) return 1;

        if( is_fighting() && query("th_victim", me )
         && query("th_victim", me) != query("id", victim )
         && query("combat_exp", victim)*3/2>query("combat_exp", me) )
        {
                    command("say 想倚多為勝？"+RANK_D->query_self_rude(me)+"可不奉陪了！");
             message_vision("\n$N突然賣一破綻，跳出戰圈，逃了！\n", me);
             remove_call_out("checking");
             me->remove_all_enemy();
             destruct(me);
                return 1;
        }
        else {
             command( "say 你這"+RANK_D->query_rude(victim)+"也來跟"+RANK_D->query_self_rude(me)+"過不去？連你一起宰了！" );
             me->kill_ob(victim);
             remove_call_out("checking");
             call_out("checking", 1, me, victim);
        return 1;
        }

}

void unconcious()
{
        object me = this_object();
        remove_call_out("checking");
        me->disable_player(" <昏迷不醒>");
        set("jing", 0, me);
        set("qi", 0, me);
        COMBAT_D->announce(me, "unconcious");
        call_out("revive", random(100 - query("con")) + 30);
}

void die()
{
        object corpse;
        mixed killer;

        remove_call_out("checking");
        
        if( !living(this_object()) ) revive(1);
        COMBAT_D->announce(this_object(), "dead");

        if( objectp(killer = query_temp("last_damage_from"))){
             set_temp("my_killer",query("id", killer));
             COMBAT_D->killer_reward(killer, this_object());
        }

        if( objectp(corpse = CHAR_D->make_corpse(this_object(), killer)) )
             corpse->move(environment());
             delete("combat_exp", corpse);
                set("th_victim", query("th_victim"), corpse);
                set("yapu_fail", query("th_victim"), corpse);

        this_object()->remove_all_killer();
        all_inventory(environment())->remove_killer(this_object());
        
        destruct(this_object());

}

int random_move()
{
        mapping exits, doors;
        string *dirs, dir;
        object me=this_object();

        if (is_fighting() || is_busy() || !living(me))
             return 0;

        if( !query("steps", me)){
             remove_call_out("destroying");
             call_out("destroying",1200,me);
        }

        if( query("steps", me) >= 25){
             remove_call_out("destroying");
             call_out("destroying",1,me);
             return 0;
        }

        addn("steps", 1, me);

        if (!objectp(environment()) 
              || !mapp(exits=query("exits", environment()) )
        || query("jingli") < query("max_jingli") / 2 )
             return 0;

        dirs = keys(exits);

        if( query("race", this_object()) == "人類"
             && mapp(doors = environment()->query_doors()))
             dirs += keys(doors);

        if (sizeof(dirs) == 0) return 0;
        dir = dirs[random(sizeof(dirs))];

        if (mapp(doors) && !undefinedp(doors[dir])
             && (doors[dir]["status"] & DOOR_CLOSED) )
             command("open " + dir);

        command("go " + dir);
        return 1;
}

void destroying(object me)
{
        message_vision("$N看了看周遭，若無其事地離開了。\n",me);
        destruct(me);
        return;
}

#include "yapu_auto_perform.h"