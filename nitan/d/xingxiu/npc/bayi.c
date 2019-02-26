// npc: /d/xingxiu/npc/bayi.c
// Jay 3/25/96

inherit NPC;
void create()
{
        set_name("巴依", ({ "bayi"}));
        set("gender", "男性");
        set("age", 55);

        set_skill("unarmed", 30);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 10);
        set("attitude","heroism");
        set("inquiry", ([
                "金子"   : "我照着阿凡提的辦法種了好多金子，可什麼也沒長出來，連種子也沒了。",
                "阿凡提" : "我把他關到我的客廳裏了。",
        ]) );

        set("combat_exp", 25000);
        set("shen_type", -1);
        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
                "巴依嘟嘟囔囔：沙子一筐子金子一屋子，金子一筐子沙子一屋子。\n",
                "巴依衝着你大喊：你站在我的樹蔭裏得付我錢！\n",
                "巴依歎了口氣：我們對着沙漠喊：金子，你在哪裏？\n",
        }) );
        carry_object(__DIR__"obj/wcloth")->wear();
}