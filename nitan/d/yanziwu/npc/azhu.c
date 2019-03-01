// azhu.c

#include <ansi.h>

inherit NPC;

int inquiry_tanqin();
mixed ask_me();

void create()
{
        set_name("阿朱", ({ "azhu", "zhu" }));
        set("long",
                "這是個身穿紅衣的女郎，大約十七八歲，一臉精靈頑皮的神氣。\n"
                "一張鵝蛋臉，眼珠靈動，別有一番動人風韻。\n");

        set("gender", "女性");
        set("age", 17);
        set("shen_type", 1);

        set("neili", 200);
        set("max_neili", 200);
        set("max_qi", 160);
        set("max_jing", 160);

        set_skill("force", 40);
        set_skill("unarmed", 40);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set_skill("sword", 30);
        set_skill("pretending", 200);

        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);
        set_temp("apply/damage", 5);

        set("combat_exp", 10000);
        set("inquiry",([
                "曼陀山莊" : "我才不敢去曼陀山莊，王夫人太霸道了!\n",
                "王語嫣" : "哎，只有她才配得上我們公子，也不知她現在怎麼樣了!\n",
                "阿碧"   : "那小丫頭也不只跑哪兒去了。\n",
                "彈琴"   : (: inquiry_tanqin :),
                "易容"   : (: ask_me :),
                "易容術" : (: ask_me :),
        ]) );
        setup();
        carry_object(__DIR__"obj/goldring")->wear();
        carry_object(__DIR__"obj/necklace")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/pink_cloth")->wear();
        carry_object(__DIR__"obj/flower_shoe")->wear();
        carry_object("/clone/misc/mask");
}

int inquiry_tanqin()
{
        object me = this_player();
        message_vision("阿朱說道：這位" + RANK_D->query_respect(me) +
                       "這麼有雅興，那我就為你彈奏一曲！\n只聽琴"
                       "聲繁復清亮，你不由的痴了。\n", me );
        message_vision("阿朱一曲終了，道個萬福，說道：現醜了。\n", me );
        return 1;
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "慕容世家" )
        {
                message_vision(CYN "$n" CYN "望著$N" CYN +
                               "吃吃的笑，道：“儂說啥子耶？”\n" NOR, me,
                               this_object());
                return 1;
        }

        if( query("age", me)>25 )
        {
                message_vision(CYN "$n" CYN "看了看$N" CYN
                               "，驚呼道：“現在還這麼貪玩？你"
                               "的年紀不要太大了。”\n", me, this_object());
                return 1;
        }

        if( query("age", me)<18 )
        {
                message_vision(CYN "$n" CYN "笑嘻嘻的對$N" CYN
                               "道：“小孩子家胡鬧什麼？找你的小"
                               "碧姐姐要糖吃去吧。”\n",
                               me, this_object());
                return 1;
        }

        if( query("gender", me) != "女性" )
                return "這公子你也想學習易容術...嘻嘻...還是好好練武吧。";

        set_temp("can_learn/azhu/pretending", 1, me);
        return "好吧，你要是想學易容術(pretending)，我可以教給你一點哦。";
}

int recognize_apprentice(object me, string skill)
{
        if( !query_temp("can_learn/azhu/pretending", me) )
                return 0;

        if (skill != "pretending")
                return 0;

        return 1;
}
