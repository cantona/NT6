#include <ansi.h>
inherit NPC;

string inquiry_hua();

void create()
{
        set_name("張媽", ({ "zhang ma", "zhang", "ma" }));
        set("gender", "女性" );
        set("age", 50);
        set("long", "一個歷經滄桑的老婆婆。\n");
        set("shen_type", 1);
        set("combat_exp", 500);
        set("str", 16);
        set("dex", 17);
        set("con", 17);
        set("int", 18);
        set("attitude", "friendly");
        set("chat_chance", 2);
        set("chat_msg", ({
                CYN "張媽唸叨着：我苦命的金花喲，你現在在那裏喲！\n" NOR,
                CYN "張媽暗暗抹了把眼淚。\n" NOR,
                CYN "張媽獨自説道：我的金花呀，你怎能撇下我自個兒走了…\n" NOR
        }));

        set("inquiry", ([
                "金花" : (: inquiry_hua :),
        ]));

        set_temp("shoe", 1);
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

string inquiry_hua()
{
        object me = this_player();
        object obn;

        message_vision(CYN "張媽説道：這位" + RANK_D->query_respect(me) +
                       CYN "，金花是我的親閨女，去年上山割草就一去不會，也"
                       "不知是死是活。\n" NOR, me );

        if(query_temp("shoe") == 0)
        {
                message_vision(CYN "張媽又道：今日我已經託人去尋找了，也不"
                               "知道怎麼樣了。\n" NOR, me);
                return "唉…也不知道現在她到底怎麼樣了。";
        }

        message_vision(CYN "張媽又説道：我這裏有她落在草叢裏的一隻繡花鞋，"
                       "你要是找到她，就把鞋交給她，她會明白的。\n" HIC "張"
                       "媽從懷裏""摸出一隻繡花鞋交給你。\n" NOR, me);

        obn = new("/d/baituo/obj/shoe");
        obn->move(me, 1);
        set_temp("shoe", 0);
        return "請你無論如何要交到她手裏。";
}
