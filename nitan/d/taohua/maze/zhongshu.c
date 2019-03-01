// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM;

void create()
{
        object ob;

        set("short", "石陣中樞");
        set("long", @LONG
這是桃花島石陣中樞所在地，四壁(wall)上繪著二十八星宿圖，地上
密密麻麻刻著諸般卦象。地上一個太極圖(tu)，周圍分別環繞先天八卦與
後天八卦，外圈則是推演而出的六十四卦。一縷天光悄然注下，映得室中
忽明忽暗，似乎萬籟俱寂，又似乎諸聲雜陳，動靜之間，不可琢磨。
LONG );

        set("exits", ([
                "up" : "/d/taohua/neidong",
        ]));
        set("objects", ([
                "/d/taohua/obj/guwen" : 1,
        ]));
        set("no_fight", 1);
        set("item_desc", ([
                "tu" : "太極圖上陰(yin)魚與陽(yang)魚分列左右。\n",
                "wall" :
"青龍七宿：角木蛟、亢金龍、氐土貉、房月狐、心日兔、尾火虎、箕水豹\n"
"白虎七宿：奎木狼、婁金狗、胃土雉、昂日雞、畢月鳥、觜火猴、參水猿\n"
"朱雀七宿：井木犴、鬼金羊、柳土獐、星日馬、張月鹿、翼水蛇、軫火蚓\n"
"玄武七宿：鬥木獬、牛金羊、女土蝠、虛日鼠、危月燕、室火豬、壁水＜□俞＞\n",
        ]));


        setup();
}

void init()
{
        add_action("do_sit", "sit");
        add_action("do_stand", "stand");
        add_action("do_leave", "leave");
        add_action("do_understand", "understand");
        add_action("do_understand", "lingwu");
        add_action("do_thinking", "think");
        add_action("do_thinking", "mingxiang");

}

int do_thinking()
{
        object me = this_player();
        int qmdj = me->query_skill("qimen-wuxing", 1);

        if (me->query_skill("qimen-wuxing", 1) < 170 &&
            ! present("he tu", me) && ! present("luo shu", me))
        {
                tell_object(me, MAG "你只覺氣血翻湧，無數異像怪聲向你襲來！\n" NOR);
                me->unconcious();
                return 1;
        }

        if( !query("taohua_maze", me) )
        {
                tell_object(me, MAG "你只覺氣血翻湧，無數異像怪聲向你襲來！\n" NOR);
                me->unconcious();
                return 1;
        }

        if( query("jing", me)<100 )
                return notify_fail("你現在精神不佳，無法定下心來思考！\n");

        if( query("potential", me) <= query("learned_points", me)+2 )
                return notify_fail("你的潛能不足，無法領悟基本武功！\n");

        me->receive_damage("jing", random(qmdj));

        if(random(20) == 0)
        {
                addn("potential", -2, me);
                me->improve_skill("qimen-wuxing", qmdj / 2 + random(qmdj * 2));
                tell_object(me, "只覺腦中豁然開朗，你對奇門遁甲的領悟又進了一層！\n");
        } else
        if (random(10) == 0)
        {
                addn("potential", -1, me);
                me->improve_skill("qimen-wuxing", qmdj / 5 + random(qmdj * 2));
                tell_object(me, "你冥思苦想，對奇門遁甲漸漸加深一層體會！\n");
        } else
        if (random(2) == 0)
        {
                me->improve_skill("qimen-wuxing", qmdj / 10 + random(qmdj / 2));
                tell_object(me, "你坐立不安，潛心苦思奇門遁甲上的難解之處。\n");
        } else
        {
                tell_object(me, "你坐立不安，潛心苦思奇門遁甲上的難解之處。\n");
        }

        return 1;
}

int do_sit(string arg)
{
        mapping skl;
        object me = this_player();
        string *sname;
        int i, j;

        if (! arg || arg != "yin") return 0;

        if( query_temp("sitted", me) )
                return notify_fail("你已經坐在上面了！\n");

        if( query_temp("standed", me) )
                return notify_fail("你已經站在上面了！\n");

        if (query("yin"))
        {
                write(query("yin")->name() + "已經坐在上面了！\n");
                tell_object(query("yin"),"看起來"+query("name", me)+"也想坐上來。\n");
                return 1;
        }

        if (arg == "yin")
        {
                message_vision("$N盤膝坐上左面陰魚圖。\n", me);

                if (me->query_skill("qimen-wuxing", 1) < 150 &&
                    ! present("he tu", me) && ! present("luo shu", me))
                {
                        tell_object(me, MAG "你只覺氣血翻湧，無數異像怪聲向你襲來！\n"NOR);
                        me->unconcious();
                        return 1;
                }
                message_vision(HIG "$N眼觀鼻，鼻觀心，由制心止自體真止，頃刻之間已神遊物外。\n" NOR, me);
                set_temp("sitted", 1, me);
                set("yin", me);
                return 1;
        }
        return 1;
}

int do_stand(string arg)
{
        mapping skl;
        object me = this_player();
        string *sname;
        int i, j;

        if( !arg || arg!="yang" ) return 0;

        if( query_temp("standed", me) )
                return notify_fail("你已經站在上面了！\n");

        if( query_temp("sitted", me) )
                return notify_fail("你已經坐在上面了！\n");

        if( query("yang" )){
                write(query("yang")->name()+"已經站在上面了！\n");
                tell_object(query("yang"),"看起來"+query("name", me)+"也想站上來。\n");
                return 1;
        }

        if( arg == "yang" )
        {
                message_vision("$N緩步站上右面的陽魚圖。\n", me);

                if ( me->query_skill("qimen-wuxing", 1) < 150 &&
                        ! present("he tu", me) && !present("luo shu", me) )
                {
                        tell_object(me, MAG "你只覺氣血翻湧，無數異像怪聲向你襲來！\n" NOR);
                        me->unconcious();
                        return 1;
                }
                message_vision(HIY "$N足下虛步先後天八卦方位，自先天而後天，片刻間已萬物不縈于懷。\n" NOR,me);
                set_temp("standed", 1, me);
                set("yang", me);
                return 1;
        }
        return 1;
}

int do_leave()
{
        object me;

        me = this_player();
        if( query_temp("sitted", me) )
        {
                delete_temp("sitted", me);
                delete("yin");
                message_vision("$N長吁一口氣，收攝心神，站起身來。\n",me);
        }

        if( query_temp("standed", me) )
        {
                delete_temp("standed", me);
                delete("yang");
                message_vision("$N調息片刻，停住步伐，看上去有點疲倦。\n",me);
        }

        return 1;
}

int valid_leave(object me, string dir)
{
        if( query_temp("sitted", me) || query_temp("standed", me) )
                return notify_fail("你周天搬運未畢，起身恐受內傷！\n");
        return ::valid_leave(me, dir);
}

int do_understand(string arg)
{
        object me;
        string skillname;
        int skill_special, skill_basic;

        me = this_player();

        if( !query_temp("sitted", me) && !query_temp("standed", me) )
                return 0;

        if (! query("yin") || ! query("yang"))
                return notify_fail("你還需要一位同伴協助運功。\n");

        if (! arg)
                return notify_fail("你要研究何種基本武技？");

        if (arg == "force")
                return notify_fail("你不能自行修煉基本內功！\n");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n");

        if (me->is_fighting())
                return notify_fail("你已經在戰鬥中了，學一點實戰經驗吧。\n");

        if (! stringp(skillname = me->query_skill_mapped(arg)))
                return notify_fail("你必須有特殊武功方能與基本武技參照領悟！\n");

        skill_basic = me->query_skill(arg, 1);
        skill_special = me->query_skill(skillname, 1);

        if( skill_special < 1 )
                return notify_fail("你對這方面的技能還是一竅不通，最好從先從基本學起。\n");

        if( skill_basic > skill_special )
                return notify_fail("你" + to_chinese(skillname) + "功力不夠，無法繼續領悟" + to_chinese(arg) + "！\n");

        if( skill_basic < 1 )
                return notify_fail("你好像還沒有學過這項基本技能吧？ 最好先去請教別人。\n");

        if( query("jing", me)<100 )
                return notify_fail("你現在精神不佳，無法定下心來思考！\n");

        if( query("potential", me) <= query("learned_points", me)+2 )
                return notify_fail("你的潛能不足，無法領悟基本武功！\n");

        me->receive_damage("jing", random(skill_basic));

        if( random(20) == 0 )
        {
                addn("potential", -2, me);
                me->improve_skill(arg, skill_special + random(skill_special * 2));
                tell_object(me, "只覺腦中豁然開朗，你對" + to_chinese(arg) + "的領悟又進了一層！\n" );
        }
        else if(random(10) == 0) {
                addn("potential", -1, me);
                me->improve_skill(arg, skill_special/2 + random(skill_special/1));
                tell_object(me, "你冥思苦想，對" + to_chinese(arg) + "漸漸加深一層體會！\n" );
        }
        else if(random(5) == 0) {
                me->improve_skill(arg, skill_special/4 + random(skill_special/2));
                tell_object(me, "你拿手比劃著，似乎對" + to_chinese(arg) + "中的幾個招數有所體會。\n" );
        }
        else if(random(2) == 0) {
                me->improve_skill(arg, skill_special/8 + random(skill_special/4));
                tell_object(me, "你坐立不安，潛心苦思" + to_chinese(arg) + "上的難解之處。\n" );
        }
        else if(random(5) == 0) {
                tell_object(me, "你心中說不出的煩燥，對" + to_chinese(arg) + "始終不得一解。\n" );
        }
        else if(random(10) == 0) {
                me->improve_skill(arg, - (skill_special/10 + random(skill_special/5)));
                tell_object(me, "你只覺得體內真氣亂竄，" + to_chinese(arg) + "中的招式象走馬燈一般在面前顯現！\n" );
        }
        else if(random(20) == 0) {
                me->improve_skill(arg, - (skill_special/6 + random(skill_special/3)));
                tell_object(me, "你的大腦中一片空白。對" + to_chinese(arg) + "是越想越糊塗。\n" );
        }
        else
        {
                tell_object(me, "你坐立不安，潛心苦思" + to_chinese(arg) + "上的難解之處。\n" );
        }

        return 1;

}