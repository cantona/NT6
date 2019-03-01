// Npc: /d/shaolin/npc/saodi-seng.c
// Date: YZC 96/01/19

inherit NPC;

void my_move();


void create()
{
        set_name("掃地僧", ({
                "saodi seng",
                "saodi",
                "seng",
        }));
        set("long",
                "這是一位專職負責塔樓清埽工作的寺內雜役僧人。\n"
        );


        set("gender", "男性");
        set("attitude", "peaceful");
        set("class", "bonze");

        set("chat_msg",({

        (: this_object(), "my_move" :),
        "掃地僧喃喃自語：這幾天也真怪，乾乾淨淨的，不知道打哪冒出許多老鼠來！\n",

        }));

        set("age", 35);
        set("shen_type", 1);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 300);
        set("max_jing", 150);
        set("neili", 100);
        set("max_neili", 100);
        set("combat_exp", 5000);
        set("score", 100);
        set("chat_chance", 5);

        set_skill("force", 25);
        set_skill("dodge", 25);
        set_skill("unarmed", 25);
        set_skill("parry", 25);


        setup();

}


void my_move()
{
        int value;
        
        value = random(10);
        
        if (value > 6)
        {
                command("say 還一大堆活沒幹完呢，我得趕緊了。\n");
                command("sigh");
                command("up");
        }
        else if (value < 4)
        {
                command("say 還一大堆活沒幹完呢，我得趕緊了。\n");
                command("sigh");
                command("down");
        }
}
