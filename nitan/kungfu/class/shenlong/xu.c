// This program is a part of NT MudLIB
// xu.c

#include <ansi.h>
inherit NPC;
inherit F_GUARDER;

int ask_gao();

void create()
{
        set_name("許雪亭", ( { "xu xueting", "xu" }) );
        set("title", HIY"神龍教"HIG"青龍使"NOR);
        set("nickname", HIR "熱血神龍" NOR);
        set("gender", "男性" );
        set("age", 55);
        set("long", "這是個五十來歲的高瘦漢子，着一襲青衣，昂然挺立。\n");

        set("str", 25);
        set("int", 32);
        set("con", 24);
        set("dex", 22);

        set("qi", 3900);
        set("max_qi", 3900);
        set("jing", 1900);
        set("max_jing", 1900);
        set("neili", 4400);
        set("max_neili", 4400);
        set("jiali", 100);
        set("level", 22);
        set("combat_exp", 850000);
        set("shen_type", -1);

        set_skill("force", 180);
        set_skill("dodge", 170);
        set_skill("unarmed", 180);
        set_skill("parry", 180);
        set_skill("sword", 180);
        set_skill("taoism", 160);
        set_skill("literate", 60);
        set_skill("tiyunzong", 170);
        set_skill("taiji-quan", 180);
        set_skill("taiji-shengong", 180);
        set_skill("taiji-jian", 180);
        set_skill("shedao-qigong", 180);
        set_skill("shenlong-xinfa", 180);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");

        create_family("神龍教", 0, "長老");

        set("inquiry", ([
                "百花腹蛇膏" : (: ask_gao :),
                "神龍教" : "一般人是入不了我神龍教的(join shenlongjiao).\n",
                "洪安通" : "教主脾氣不好,要討他歡心才好。\n",
                "教主"   : "教主脾氣不好,要討他歡心才好。\n",
                "入教"   : "一般人是入不了我神龍教的(join shenlongjiao).\n",
                "口號"   : "萬年不老！永享仙福！壽與天齊！文武仁聖！\n",
        ]));

        set("chat_chance", 1);
        set("chat_msg", ({
                "許雪亭忽然一拍腦袋，説：對了，可以用百花腹蛇膏！\n",
                "許雪亭怒道：唉，偌大一個神龍教，都毀在一個娘們手裏了！\n",
                "許雪亭歎口氣，説道：唉，不殺了洪安通，誰也活不了。\n",
        }) );
        set("coagents", ({
                ([ "startroom" : "/d/shenlong/dating",
                   "id"        : "hong antong", ]),
        }));
        set("master_ob", 4);
        setup();
        carry_object("/d/city/obj/duanjian")->wield();
}

int ask_gao()
{
        say(
        "\n許雪亭悄聲對你説：這可是本教禁物啊。它一遇鮮血，便生濃香，\n"
        "我們住在這靈蛇島上，人人都服慣了雄黃酒，以避毒蛇，這股香氣\n"
        "一碰到雄黃酒，便使人筋骨酥軟，不能動彈。對了，你怎麼也知道？\n"
                );
        return 1;
}

int accept_object(object who, object ob)
{
        object obn;

        if( !who || environment(who) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, who) ) return notify_fail("你沒有這件東西。\n");

        if (is_busy())
        {
                command("say 慢慢來，急什麼！");
                return 0;
        }

        if( query("id", ob) != "fushedan"
                 && query("id", ob) != "baixianghua" )
                    return notify_fail("許雪亭搖頭道：如果殺不了洪安通，給我什麼也沒用啊。。。\n");

        if( query("id", ob) == "fushedan" )
                {
                  if(query_temp("baixianghua"))
                  {
                  message_vision("\n許雪亭見是腹蛇膽，大喜道：腹蛇膽百香花都有了，百花腹蛇膏練成了！\n",who);
                  obn=new("/d/shenlong/obj/baihua");
                  obn->move(who);
                  delete_temp("fushedan");
                  delete_temp("baixianghua");
                  destruct(ob);
                  return 1;
                  }
                  else
                  {
                  if(query_temp("fushedan"))
                  {
                               message_vision("\n許雪亭見是腹蛇膽，對$N搖頭道：腹蛇膽我有了，就差百香花了。\n",who);
                           return 0;
                  }
                  else
                  {
                  message("vision","許雪亭看見腹蛇膽，大喜道：有了腹蛇膽，只差百香花了。\n",environment(who));
                  set_temp("fushedan",1);
                  destruct(ob);
                  return 1;
                  }
                }
        }
        if( query("id", ob) == "baixianghua" )
                {
                  if(query_temp("fushedan"))
                  {
                  message_vision("\n許雪亭見是百香花，大喜道：腹蛇膽百香花都有了，百花腹蛇膏練成了！\n",who);
                  obn=new("/d/shenlong/obj/baihua");
                  obn->move(who);
                  delete_temp("fushedan");
                  delete_temp("baixianghua");
                  destruct(ob);
                  return 1;
                  }
                  else
                  {
                  if(query_temp("baixianghua"))
                  {
                           message_vision("\n許雪亭見是百香花，對$N搖頭道：百香花我有了，就差腹蛇膽了。\n",who);
                           return 0;
                  }
                  else
                  {
                  message("vision","許雪亭看見百香花，大喜道：有了百香花，只差腹蛇膽了。\n",environment(who));
                  set_temp("baixianghua",1);
                  destruct(ob);
                  return 1;
                  }
                 }
        }
}

void attempt_apprentice(object ob)
{
        command("say 我不收徒，你找教主去吧！ ");
        return;
}
