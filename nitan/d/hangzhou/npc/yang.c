//Cracked by Roath
// /d/hangzhou/npc/yang.c   楊鐵心
// by aln 2 / 98

inherit NPC;

void create()
{
        set_name("楊鐵心", ({ "yang tiexin", "yang" }) );
        set("gender", "男性");
        set("age", 25);
        set("long",
"一個白淨面皮的漢子。\n"
"他是岳飛麾下名將楊再興的後代。\n");
        set("combat_exp", 180000);
        set("shen_type",  1);
        set("attitude", "friendly");

        set("str", 28);
        set("con", 30);
        set("int", 20);
        set("dex", 27);

        set("max_qi", 3000000);
        set("max_jing", 1500000);
        set("max_neili", 1000);
        set("neili", 1000);
        set("jiali", 30);

        set_temp("apply/armor", 40);

        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
/*
        set_skill("liuhe-qiang", 120);
        set_skill("pike", 120);
        set_skill("unarmed", 100);

        map_skill("pike", "liuhe-qiang");
        map_skill("parry", "liuhe-qiang");
*/

        set("inquiry", ([
                "郭嘯天" : "他是我義兄。",
                "包惜弱" : "她是我渾家。",
                "楊康" : "這是一個道人給我未出世的兒女取的名字。",
                "郭靖" : "這是我義兄郭嘯天的骨肉。",
                "李萍" : "她是我嫂子",
        ]));

        setup();

        carry_object("/d/city/obj/cloth")->wear();
}
