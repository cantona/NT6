// walker.c
// Date: YZC 96/01/19
// Date: Cleansword 96/02/05

inherit NPC;

void create()
{
        set_name("行者", ({"xingzhe","walker",}));
        set("title", "少林刀僧");
        set("long",
                "他是一位雲遊四方的行者，風霜滿面，行色匆匆，似乎正在辦一件急事。\n"
        );

        set("gender", "男性");
        set("attitude", "heroism");
        set("class", "bonze");

        set("chat_chance", 3);

        set("chat_msg", ({
                "行者說道：據說本寺後山山頂上有一個蘊含無上降魔大法的金剛伏魔圈，內有佛家法寶。\n",
                "行者說道：易筋經分為修行篇，攻防篇，身法篇與拳術篇四部，百年前便都已散失各處。\n",
                "行者說道：大金剛拳剛猛狠辣，最厲害的一招名稱叫做如來笑，最合佛家超渡世人的本意。\n",
                "行者說道：本寺十八羅漢大陣威力無比，能破陣出關者可說是鳳毛麟角，萬裡挑一的人才。\n",
                "行者說道：本寺弟子自上而下，依次是五聖僧，十八羅漢，九尊者，九禪師，九比丘等。\n",
                "行者說道：戒律院主持是玄痛大師，全寺上下眾僧見了他，真是大氣也不敢吭一聲。\n",
                "行者說道：少林寺藏經樓藏經之富，天下罕有。佛法經典，武功秘籍，可以說是無所不包。\n",
                "行者說道：本寺弟子如要習武防身，可到後殿武器庫和防具庫領取器械，用後歸還所司。\n",
                "行者說道：少林歷代有許多高僧在寺內鐘樓頂上勤修佛法，七層窗外平台上更是禪定妙處。\n",
                "行者說道：少林絕藝七十二，專精一門，固是大有好處，但如能融貫數藝，則威力更強。\n",
                "行者說道：本寺弟子如能較技戰勝師尊輩，便可名列與彼同班，拜師學習更高深的武藝。\n",
                (: random_move :)
        }) );

        set("age", 35);
        set("shen_type", 1);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 25);
        set("max_qi", 500);
        set("max_jing", 100);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 30);
        set("combat_exp", 20000);
        set("score", 100);
        set("apply/attack",  30);
        set("apply/defense", 30);

        set_skill("force", 50);
        set_skill("unarmed", 50);
        set_skill("blade", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_skill("shaolin-shenfa", 50);
        set_skill("cibei-dao", 50);
        set_skill("shaolin-xinfa", 50);

        map_skill("force", "shaolin-xinfa");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("blade", "cibei-dao");
        map_skill("parry", "cibei-dao");

        setup();
        carry_object("/d/city/obj/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 50);
}
