// Room: /city/leitai.c
// Date: Feb.27 1998 by Java
// Update by Doing
// Modified by Haiyan

#include <ansi.h>

inherit ROOM;
string look_tiaofu();

void create()
{
        set("short", "擂台");
        set("long", @LONG
這是一個四丈見方的擂台。粗壯結實的木柱撐起一片平台，四角
的支柱上高掛著四副對聯，四面的觀眾都能清楚地看到台上的手起腳
落。樑上貼著一長條幅(tiaofu)，上面寫了一些東西。
LONG );
        set("outdoors", "city");
        set("item_desc", ([
                "tiaofu" : (: look_tiaofu :),
        ]));

        set("exits", ([
                "down" : "/d/city/wudao1",
        ]));
        set("objects", ([
                "/adm/npc/referee": 1,
        ]));
	set("coor/x", 1);
	set("coor/y", -9);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_lclose", "lclose");
        add_action("do_lopen", "lopen");
        add_action("do_invite", "invite");
        add_action("do_jiangli", "jiangli");
}

string look_tiaofu()
{
        object ob;

        ob = query("close_by");
        if (! objectp(ob))
                return "本擂台現在自由開放，如有興趣自行比"
                       "武，失手傷人致命，概不負責。\n\n"
                       "注：巫師請用" HIY "lopen" NOR "/"
                       HIY "lclose" NOR "命令開放關閉擂台。\n";

        return "本擂台現在被" + ob->name(1) + "暫時關閉，"
               "組織比武，閒雜人等勿要喧嘩。\n"
               "巫師請用" HIY "invite" NOR "命令邀請他人上台，"
               "或在台下使用" HIY "pass" NOR "命令\n"
               "指定某人上台比武，用" HIY "kickout" NOR
               "踢某人下台。\n";
}

int refuse(object ob)
{
        return 1;
        if (! wizardp(ob) && query("close_by"))
                return 1;

        return 0;
}

int do_lclose(string arg)
{
        object me,ob;

        me = this_player();
        if (wiz_level(me) < 3)
                return notify_fail("你沒有資格關閉擂台。\n");

        if (arg != "here")
                return notify_fail("如果你要關閉擂台，請輸入(lclose here)。\n");

        if (objectp(query("close_by")))
                return notify_fail("這個擂台已經被" +
                                   query("close_by")->name(1) +
                                   "關閉用于比武了。\n");

        set("close_by", me);
        message("vision", HIW "【武林盛會】" + me->name(1) +
                "關閉了擂台，開始舉行比武盛會。\n" NOR,
                all_interactive());

        foreach (ob in all_inventory(this_object())) 
        {
                if (userp(ob) && !wizardp(ob))
                {
                        ob->move("/d/city/wudao1");
                        if (living(ob))
                                tell_object(ob,"公平子對你說：擂台給關閉了，您先請下台等待吧！\n");
                }
        }

        set("biwu_room",1);
        return 1;
}

int do_lopen(string arg)
{
        object me;

        me = this_player();
        if (wiz_level(me) < 3)
                return notify_fail("你沒有資格打開擂台。\n");

        if (! objectp(query("close_by")))
                return notify_fail("這個擂台目前並沒有被關閉。\n");

        if (query("close_by")->name(1) != me->name())
                return notify_fail("只能由主持比武大會的巫師才能打開擂台。\n");

        if (arg != "here")
                return notify_fail("如果你要打開擂台，請輸入(lopen here)。\n");

        delete("close_by");
        message("vision", HIW "【武林盛會】" + me->name(1) +
                "結束了比武，重新開放了擂台。\n" NOR, all_interactive());

        delete("biwu_room");
        return 1;
}

object *broadcast_to()
{
        if (! objectp(query("close_by")))
                return 0;

        return ({ find_object("/d/city/wudao1"),
                  find_object("/d/city/wudao2"),
                  find_object("/d/city/wudao3"),
                  find_object("/d/city/wudao4"), });
}

int do_invite(string arg)
{
        int i;
        object *inv;
        object me;
        object ob;

        me = this_player();
        if (! wizardp(me))
                return notify_fail("你不是巫師，沒有資格邀請人家上來。\n");

        if (! query("close_by"))
                return notify_fail("現在擂台並沒有關閉，無需特地邀請別人。\n");

        if (query("close_by")->name(1) != me->name())
                return notify_fail("只能由主持比武大會的巫師才能邀請選手上台。\n");

        if (! arg ||
            ! objectp(ob = find_player(arg)))
                return notify_fail("你想讓誰上來？\n");

        if (environment(ob) == this_object())
                return notify_fail("嗯？現在不是已經在這裡了麼？\n");

        if (wizardp(ob))
                return notify_fail("人家自己想上來自己會上來，不勞你費心。\n");

        if (! living(ob))
                return notify_fail("好歹你得弄醒人家吧？\n");

        if (mapp(ob->query_condition()))
                return notify_fail("對不起，對方的身體狀況不好，不能上台！\n");

        if( query("eff_qi", ob)<query("max_qi", ob) )
               return notify_fail("對不起，對方的氣血受傷了，不能上台！\n");

        if( query("eff_jing", ob)<query("max_jing", ob) )
               return notify_fail("對不起，對方的精氣受傷了，不能上台！\n");

        inv = deep_inventory(ob);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! userp(inv[i])) continue;
                return notify_fail("對方身上背著個大活人呢，不能上台！\n");
        }

        message("vision", HIW + me->name() + "一聲長嘯：" + ob->name() +
                          "，你還不快快上來？\n" NOR, all_interactive());
        message_vision("只見$N急急忙忙的走了開去。\n", ob);
        message("vision", "只見一聲呼哨，" + ob->name() + "應聲躍上台來，矯健之極。\n",
                this_object());

        ob->move(this_object());
        tell_object(ob, HIY "你一陣目眩，定神一看，這才發現自己已經到了" +
                    environment(ob)->short() + HIY "。\n");
        return 1;
}

int do_jiangli(string arg)
{
        object me = this_player();
        object ob, obv;
        string player, msg;
        string *par;
        int *mc;
        mapping winner;
        int place, gift;

        if (wiz_level(me) < 3)
                return notify_fail("你沒有資格給別人獎勵。\n");

        if (! objectp(query("close_by")))
                return notify_fail("現在擂台並沒有用于召開比武大會，你" +
                                   "不能給別人獎勵。\n");

        if (query("close_by")->name(1) != me->name())
                return notify_fail("你並不是主持比武大會的巫師，" +
                                   "不能給別人獎勵。\n");

        if (! arg || sscanf(arg, "%s %d %d", player, place, gift) != 3)
        {
                msg = "指令格式：jiangli <ID> <名次> <獎品>。\n\n";
                msg += "Example: jiangli haiyan 2 5\n\n";
                msg += "獎品代號如下：\n";
                msg += "0 - 玄黃紫清丹\n";
                msg += "1 - 九轉金丹\n";
                msg += "2 - 天香玉露\n";
                msg += "3 - 菩提子\n";
                msg += "4 - 仙丹\n";
                msg += "5 - 洗髓丹\n";
                msg += "6 - 神力丸\n";
                msg += "7 - 火紅仙丹\n";
                msg += "8 - 補天石\n";
                msg += "9 - 冰蠶絲\n\n";
                me->start_more(msg);
                return 1;
        }

        if ( place < 1 || place > 5)
                return notify_fail("你只能獎勵前五名。\n");

        if (! objectp(ob = present(player, this_object())))
                return notify_fail("你要獎勵誰？\n");

        if( !query("winner", me))winner=([]);
        else
        {
                winner=query("winner", me);
                mc = keys(winner);
                par = values(winner);

                if (member_array(place, mc) != -1)
                       return notify_fail("第" + chinese_number(place) +
                                          "名已經產生了。\n");

                if (member_array(player, par) != -1)
                       return notify_fail(player + "已經取得名次了。\n");
        }

        switch(gift)
        {
             case 0:
                obv = new("/clone/gift/xuanhuang");
                break;
             case 1:
                obv = new("/clone/gift/jiuzhuan");
                break;
             case 2:
                obv = new("/clone/misc/tianxiang");
                break;
             case 3:
                obv = new("/d/shaolin/obj/puti-zi");
                break;
             case 4:
                obv = new("/clone/gift/xiandan");
                break;
             case 5:
                obv = new("/clone/gift/xisuidan");
                break;
             case 6:
                obv = new("/clone/gift/shenliwan");
                break;
             case 7:
                obv = new("/clone/gift/unknowdan");
                break;
             case 8:
                obv = new("/d/item/obj/butian");
                break;
             case 9:
                obv = new("/d/item/obj/tiancs");
                break;
        }

        message("vision",HIW"【武林盛會】恭喜"+query("name", ob)+"("+
                query("id", ob)+")獲得本屆比武大會第"+
                chinese_number(place) + "名。\n" NOR,
                all_interactive());
        message_vision("$N在懷裡掏了半天，摸出一"+query("unit", obv)+
                       obv->name() + "交給了$n！\n", me, ob);

        winner+=([place:query("id", ob)]);
        set("winner", winner, me);
        obv->move(ob);
        return 1;
}