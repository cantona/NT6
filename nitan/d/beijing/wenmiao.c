#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "文廟");
        set("long", @LONG
這裏是文廟正殿，內有孔夫子像。歷代皇帝都懂得利用儒教思想
來鞏固自己的江山社稷，當朝皇帝自然也不例外。不論何人到此，都
畢恭畢敬地上香禮拜。孔夫子講究的是人的悟性，要成為一位揚名天
下的大俠，光靠武力往往不能做到，還需要有足夠的智慧。不少江湖
中流名千古的神話人物，在初入江湖時，都曾經在這裏發下誓言，虔
誠的膜拜(mobai)。 而新玩家也可以在這裏許願(xuyuan)，明確一下
自己的性格，踏上漫漫江湖路。
LONG );

        set("no_fight",1);
        set("no_drift", 1);
        set("valid_startroom","1");
        set("exits", ([
                "south" : "/d/beijing/dong_3",
        ]));

	set("coor/x", -2780);
	set("coor/y", 7740);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_mobai","mobai");
        add_action("do_chouqian","chouqian");
        add_action("do_xuyuan","xuyuan");
}

int do_mobai(string arg){
        int i;
        int gift;
        int points;
        int tmpstr, tmpint, tmpcon, tmpdex;
        object me;
        mapping my;

        return notify_fail("你還是去揚州戚長髮那裏購買天賦丹洗點吧，這裏再膜拜也沒有用了。\n");
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;
        if (me->is_busy()) return notify_fail("你正忙着呢，膜拜還要三心二意？\n");
        if( query("can_not_change", me) )
                return notify_fail("你正對着孔子像雙膝跪下，無比虔誠的膜拜這位華夏聖人，良久才起身。\n");
        write(HIC "你對着孔子像畢恭畢敬的跪了下去，雙手合十開始膜拜。\n" NOR, me);
        gift = query("int", me) + query("con", me) + query("str", me) + query("dex", me);
        tmpstr = tmpint = tmpcon = tmpdex = 13;
        tmpint = 23;
        points = gift - (tmpstr + tmpint + tmpcon + tmpdex);
        for (i = 0; i < points; i++) {
                switch (random(4)) {
                case 0: 
                        if (tmpstr < 30) tmpstr++;
                        else i--; 
                        break;
                case 1: 
                        if (tmpint < 30) tmpint++;
                        else i--;
                        break;
                case 2: 
                        if (tmpcon < 30) tmpcon++;
                        else i--;
                        break;
                case 3:
                        if (tmpdex < 30) tmpdex++;
                        else i--;
                        break;
                }
        }
        my = me->query_entire_dbase();
        my["str"] = tmpstr;
        my["int"] = tmpint;
        my["con"] = tmpcon;
        my["dex"] = tmpdex;
        my["kar"] = 10 + random(21);
        my["per"] = 10 + random(21);
        write(HIC "突然一陣深沉的聲音在你心頭響起：“這是我給你的天資！”\n" NOR, me);
        write(sprintf(HIY "\n你只感覺身體裏一道聖氣緩緩流轉，你的秉性變化了：\n"
                          "膂力：【 " HIG "%d" HIY " 】 "
                          "悟性：【 " HIG "%d" HIY " 】 "
                          "根骨：【 " HIG "%d" HIY " 】 "
                          "身法：【 " HIG "%d" HIY " 】\n" NOR,
                      tmpstr, tmpint, tmpcon, tmpdex));
        me->start_busy(1);
        return 1;
}

int do_chouqian(string arg)
{
        object me;
        string *character = ({
                "心狠手辣",
                "光明磊落",
                "狡黠多變",
                "陰險奸詐",
         });
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( time()-query_temp("last_chouqian_time", me)<1800 )
                return notify_fail("這麼頻繁的抽籤幹嘛？心不誠則籤不靈，過半個小時再來吧。\n");

        write(HIC "你虔誠的抽了一根籤，閉目祈禱了一陣，才睜開眼睛看簽上所書文字。\n" NOR, me);
        write(HIC "簽上寫着：" + CHOUQIAN->query_chouqian() + "。\n" NOR, me);
        set_temp("last_chouqian_time", time(), me);
        if( query("can_not_change", me))return 1;
        set("character", character[random(sizeof(character))], me);
        write(sprintf(HIY"\n你隱隱聽到一陣深沉的聲音：朝『%s』的方向發展吧。\n"NOR,query("character", me)));
        return 1;
}

int do_xuyuan(string arg)
{
        object me;
        string *character = ({
                "心狠手辣",
                "光明磊落",
                "狡黠多變",
                "陰險奸詐",
         });
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( time()-query_temp("last_chouqian_time", me)<1800 )
                return notify_fail("這麼頻繁的抽籤幹嘛？心不誠則籤不靈，過半個小時再來吧。\n");

        write(HIC "你虔誠的抽了一根籤，閉目祈禱了一陣，才睜開眼睛看簽上所書文字。\n" NOR, me);
        write(HIC "簽上寫着：" + CHOUQIAN->query_chouqian() + "。\n" NOR, me);
        set_temp("last_chouqian_time", time(), me);
        if( query("can_not_change", me))return 1;
        if( member_array(arg, character) == -1 )
                arg = character[random(sizeof(character))];
        set("character", arg, me);
        write(sprintf(HIY"\n你隱隱聽到一陣深沉的聲音：朝『%s』的方向發展吧。\n"NOR,query("character", me)));
        return 1;
}
