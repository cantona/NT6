#include <ansi.h>

inherit NPC;
int ask_weiwang();

void create()
{
        set_name("賈老六", ({ "jia laoliu", "jia" }));
        set("title", HIR "天地會"HIG"青木堂"NOR"會眾");
        set("shen_type", 1);

        set("gender", "男性");
        set("age", 35);
        set("long",
                "\n他是天地會青木堂會眾，當年在揚州之時，曾大罵鹽梟，\n"+
                "罵他們不敢殺官造反，只會走私漏税，做沒膽子的小生意，\n"+
                "結果得罪了青龍幫，遭人追殺，茅十八也因此和青龍幫結仇。\n");
        set("no_get_from", 1);

        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/attack", 30);
        set_temp("apply/damage", 15);

        set("combat_exp", 50000);
        set("attitude", "friendly");
        set("chat_chance", 3);
        set("chat_msg", ({
        "賈老六忽然説：揚州鹽販子真可惡。\n",
        "賈老六説: 江湖威望很重要，威望值高大有好處啊。\n",
        "賈老六突然説道: 忠義堂前兄弟在，城中點將百萬兵。\n",
        }));
        set("inquiry", ([
                "陳近南" :  "\n想見總舵主可不容易啊。\n",
                "天地會" :  "\n只要是英雄好漢，都可以入我天地會(join tiandihui)。\n",
                "加入" :  "\n只要入了我天地會，大家就可以一起反青復明。\n",
                "入會" :  "\n只要入了我天地會，可以向會中各位好手學武藝。\n",
                "威望" :  (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
       ]) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void die()
{
        message_vision("\n$N大叫道：兄弟們會替我報仇的，頭一偏，死了。\n", this_object());
        ::die();
}

int ask_weiwang()
{
        command("tell"+query("id", this_player())+"你現在的江湖威望是"+(query("weiwang", this_player())));
say("\n賈老六説：如果你威望值很高，有些人見了你不但不會殺你，還會教你武功，送你寶貝。\n"
+"而且你還可以加入幫會，率領會眾去攻打目標，就連去錢莊取錢也會有利息 。。。。。\n");
        say("賈老六又説：殺某些壞人或救某些好人可以提高江湖威望。\n");
        return 1;
}
