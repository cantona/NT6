#include <ansi.h>
#include <command.h>
#include <login.h>

inherit NPC;

string ask_diyudao();

string *death_msg = ({
        HIW "白無常説道：喂！新來的，你叫什麼名字？\n\n" NOR,
        HIW "白無常用奇異的眼光盯著你，好像要看穿你的一切似的。\n\n" NOR,
        HIW "白無常「哼」的一聲，從袖中掏出一本像帳冊的東西翻看著。\n\n" NOR,
        HIW "白無常合上冊子，説道：咦？陽壽未盡？怎麼可能？\n\n" NOR,
        HIW "白無常搔了搔頭，歎道：罷了罷了，你走吧。\n\n"
                "一股陰冷的濃霧突然出現，很快地包圍了你。\n\n" NOR,
});

void create()
{
        set_name("白無常", ({ "bai wuchang", "bai", "wuchang" }));
        set("title", HIR "冥府地藏王殿前" NOR);
        set("long", "\n白無常瞪著你，焦黃的臉上看不出任何喜怒哀樂。\n");
        set("attitude", "peaceful");
        set("chat_chance", 15);
        set("chat_msg", ({
                CYN "白無常狠狠的敲了敲你的腦袋，你覺得頭暈暈的。\n", NOR,
                CYN "白無常嘿嘿奸笑兩聲。\n" NOR,
        }) );
        set("age", 217);

        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 250);

        set("combat_exp", 50000000);

        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("blade", 500);
        set_skill("staff", 500);
        set_skill("hammer", 500);
        set_skill("club", 500);
        set_skill("whip", 500);
        set_skill("dagger", 500);
        set_skill("throwing", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("never-defeated", 1000);
        set_skill("magic", 1000);

        map_skill("sword", "never-defeated");
        map_skill("blade", "never-defeated");
        map_skill("staff", "never-defeated");
        map_skill("hammer", "never-defeated");
        map_skill("club", "never-defeated");
        map_skill("whip", "never-defeated");
        map_skill("dagger", "never-defeated");
        map_skill("parry", "never-defeated");
        map_skill("dodge", "never-defeated");
        map_skill("force", "never-defeated");

        set("inquiry", ([
                "地獄道" : (: ask_diyudao :),
                "錦鑭袈裟" : "此乃袈裟中的上品，穿戴者可不墜地獄，不入輪迴！\n",                
        ]));
        setup();

        carry_object(__DIR__"obj/cloth1")->wear();
        carry_object(__DIR__"obj/suolian")->wield();
        set_temp("handing", carry_object(__DIR__"obj/book"));
}

void init()
{
        ::init();
        if (! previous_object() ||
            ! userp(previous_object()) ||
            ! previous_object()->is_ghost() ||
            wizardp(previous_object())) return;
        call_out("death_stage", 5, previous_object(), 0);
}

void death_stage(object ob, int stage)
{
        int i;
        object *inv, mailbox;
        if (! ob || ! present(ob)) return;

        tell_object(ob, death_msg[stage]);
        if (++stage < sizeof(death_msg))
        {
                call_out( "death_stage", 5, ob, stage );
                return;
        } else
                ob->reincarnate();

        if( query("reborn_offer", ob) && query("reborn_offer", ob) == "finish" )
        {
               ob->move("/d/death/youmingjie");
               return;
        }

        /*
        if (! wizardp(ob))
        {
                    inv = all_inventory(ob);
                    for (i = 0; i < sizeof(inv); i++)
                            DROP_CMD->do_drop(ob, inv[i]);
        }
        */
        
        ob->move(REVIVE_ROOM);
        set("startroom", REVIVE_ROOM, ob);
        message("vision", HIW "你忽然發現前面多了一個人影，不過那人影又好像已經在那裏\n"
                          "很久了，只是你一直沒發覺。\n" NOR, environment(ob), ob);
}

string ask_diyudao()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "你的先天屬性還不足以修煉地獄道，我看你還是先回去吧。\n";

        if( query("reborn/times", me)<3 )
                return "走開，走開，沒看我正忙嗎？\n";
                
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                return "哼，凡夫俗子，竟然如此貪心！\n";

        if (me->query_skill("lunhui-sword",1))
                return "哼，凡夫俗子，竟然如此貪心！\n";        
                
        if (me->query_skill("diyu-dao", 1))
                return "怎麼樣，這招你練熟了嗎？\n";
                
        command("nod");
        command("say 閻王爺吩咐過了，叫我在此等候有緣者，既然如此，這「地獄道」就傳你吧！");
        
        message_sort(HIC "\n$N" HIC "掏出一根哭喪棒，揮舞了幾下，然後猛然點向$n" HIC "周身大穴，招式"
                     "$n" HIC "平凡簡單之極，但卻藴藏着任何人難以招架的力量，$n" HIC "倒退幾步，雙手"
                     "捂住胸口，一口鮮血吐出 ……。\n" NOR, this_object(), me);
                        
        command("heng");
        command("say 這些凡人還真是不中用，就這麼幾下就抵受不住了，哎~。");
        command("say 好了，這「地獄道」的功力已經傳授給你了，此地不是你等長留之地，你還是速速離開吧！");
        
        tell_object(me, HIG "恭喜你領悟了「地獄道」劍法，目前等級為10級。\n" NOR);
        me->set_skill("diyu-dao", 10);
        
        return "好自為知！";
        
                
}
