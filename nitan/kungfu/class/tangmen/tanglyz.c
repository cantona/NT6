// tanglyz

#include <ansi.h>
#include "tangmen.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("唐老爺子", ({ "tanglyz", "tang", "yezi"}));
        set("long",
"唐老爺子是唐門的開山祖師，在唐門地位頗高。\n");
        set("gender", "男性");
        set("age", 91);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 28);
        set("max_qi", 8000);
        set("max_jingli", 1500);
        set("max_douzhi", 500);
        set("douzhi", 500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("yanli",200);
        set("jiali", 100);
        set("combat_exp", 800000);
        set("level", 15);
        set("shen",3000);
        set("score", 7000);

        set_skill("force", 600);
        set_skill("throwing", 600);
        set_skill("dodge", 600);
        set_skill("parry", 600);
        set_skill("literate", 600);
        set_skill("hand", 600);
        set_skill("hand", 600);
        set_skill("sword", 600);
        set_skill("boyun-suowu", 600);
        set_skill("biyun-xinfa", 600);
        set_skill("sanku-shengong", 600);
        set_skill("qiulin-shiye", 600);
        set_skill("wuzhan-mei", 600);
        set_skill("poison", 600);
        set_skill("medical", 600);
        set_skill("tangmen-throwing", 600);
        set_skill("tangmen-poison", 600);
        set_skill("tangmen-medical", 600);

        map_skill("force", "sanku-shengong");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "wuzhan-mei");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        map_skill("poison", "tangmen-poison");
        map_skill("medical", "tangmen-medical");

        prepare_skill("hand", "boyun-suowu");

        create_family("唐門世家", 1, "掌門");

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("family/family_name", ob) == "唐門世家" && query("combat_exp", ob)>1000000 )
        {
                message_vision("唐老爺子微微一笑，對$N説道:“想拜師的話去找老太太吧，我已經不收徒弟了！”\n",ob);
                message_vision("唐老爺子微微一頓，又道:“不過，既然你已經找到我這裏了，我就指點你幾招吧！”\n",ob);
                command("say 好吧，從今天起你就是我的關門弟子了。\n");
                command("recruit "+query("id", ob));
        }
        else
                if( query("family/family_name", ob) != "唐門世家" )
                {
                        message_vision("\n唐老爺子微微一笑，對$N説道:“你不知我唐門乃是世家，不收外姓弟子嘛！”\n",ob);
                        message_vision("唐老爺子微微一頓，又道:“不過，既然你已經找到我這裏了，就喝杯茶再走吧！”\n",ob);
                        tell_object(ob, "唐老爺子見你有些猶豫，説道:“這茶可是極其珍貴，喝了可以固本培元，對習武之人可是大大的有益啊！”\n\n");
                        write(YEL"你要喝嗎？請輸入選擇（y)/n ："NOR);
                        input_to("accept_cha", 1, ob, 1);
                }
                else
                        tell_object(ob, "唐老爺子惋惜的對你説:“可惜你的功夫還不到家，不能使用我的絕技！你以後再來吧！”\n");
        return;
}

void accept_cha(string want, object ob, int forever)
{
        if ( want == "" || want == "y" || want == "Y" )
        {
                message_vision("唐老爺子微一抬手，便有一家丁給$N奉上了一杯香茶！\n",ob);
                tell_object(ob, "只見茶水發出淡淡的綠色，正冒着熱氣，幾片不知名的葉片漂在杯中，聞起來清香撲鼻。\n");
                message_vision("$N將茶杯端起，美美的喝了一口。\n", ob);
                call_out("dead", 120, ob);
        }
        else
        {
                message_vision("\n唐老爺子勃然大怒，對$N喝道:“讓你好死你不要，非要我動手嗎！我這裏是不能被外人知道的！”\n",ob);
                this_object()->kill_ob(ob);
                ob->fight_ob(this_object());
        }
}

int dead(object ob)
{
        tell_object(ob,HIR"你腹中突然如刀絞一般疼痛，原來茶中竟是劇毒......\n你眼前一黑，一頭栽倒在地上......"NOR);
        tell_room(environment(ob),HIR+query("name", ob)+"突然一頭栽倒在地上！"NOR,ob);
        set_temp("die_reason", "中唐門奇毒而死", ob);
        ob->die();
        tell_room( environment(this_object()), "唐老爺子長歎一聲:“唉！外人怎麼會闖進來了呢！”");
}
