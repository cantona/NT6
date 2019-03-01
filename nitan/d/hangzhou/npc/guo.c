//Cracked by Roath
// /d/hangzhou/npc/guo.c   郭嘯天
// by aln 2 / 98

inherit NPC;

void create()
{
        set_name("郭嘯天", ({ "guo xiaotian", "guo" }) );
        set("gender", "男性");
        set("age", 25);
        set("long",
"他身材魁梧，濃眉大眼。\n"
"他是樑山泊好漢地佑星賽仁貴郭盛的後代。\n");
        set("combat_exp", 160000);
        set("shen_type",  1);
        set("attitude", "friendly");

        set("str", 28);
        set("con", 30);
        set("int", 20);
        set("dex", 27);

        set("max_qi", 800);
        set("max_jing", 300);
        set("max_neili", 1000);
        set("neili", 1000);
        set("jiali", 30);

        set_temp("apply/armor", 40);

        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
/*
        set_skill("liuhe-qiang", 100);
        set_skill("pike", 100);
        set_skill("unarmed", 100);

        map_skill("pike", "liuhe-qiang");
        map_skill("parry", "liuhe-qiang");
*/

        set("inquiry", ([
                "楊鐵心" : "他是我義弟。",
                "李萍" : "她是我渾家。",
                "郭靖" : "這是一個道人給我未出世的兒女取的名字。",
                "楊康" : "這是我義弟楊鐵心的骨肉。",
                "包惜弱" : "她是我弟媳。",
        ]));

        setup();

        carry_object("/d/city/obj/cloth")->wear();
}
