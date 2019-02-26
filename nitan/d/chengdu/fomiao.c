#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "佛廟");
        set("long", @LONG
這裏是佛廟正殿，內有佛祖金身。雖然與少林、峨嵋等佛教盛地
相比，這個廟又小又簡陋，但是據傳這裏的釋迦牟尼金身像乃當年鑑
真從天竺所帶來，無比靈異，因此這裏常年香火鼎盛。佛門講究一個
緣字，重視人的先天根骨，不少玩家為了讓自己擁有超常的根骨，經
常來這裏頂禮膜拜(mobai)。 新玩家也可以在這裏抽籤(chouqian)，
明確一下自己的性格，踏上漫漫江湖路。
LONG );

       set("no_fight",1);
        set("no_drift", 1);
        set("valid_startroom","1");
        set("exits", ([
                "north" : __DIR__"shuduroad1",
        ]));

        set("coor/x", -15210);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();
}
/*
void init()
{
        add_action("do_mobai","mobai");
        add_action("do_chouqian","chouqian");
}

int do_mobai(string arg){
        int i;
        int points;
        int tmpstr, tmpint, tmpcon, tmpdex;
        object me;
        mapping my;
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;
        if (me->is_busy()) return notify_fail("你正忙着呢，膜拜還要三心二意？\n");
        if( query("can_not_change", me) )
                return notify_fail("你正對着佛祖金像雙膝跪下，無比虔誠的頂禮膜拜，良久才起身。\n");
        write(HIC "你對着佛祖金像畢恭畢敬的跪了下去，雙手合十開始膜拜。\n" NOR, me);
        tmpstr = tmpint = tmpcon = tmpdex = 13;
        tmpcon = 23;
        points = 80 - (tmpstr + tmpint + tmpcon + tmpdex);
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
        write(HIC "突然一陣慈祥的聲音在你心頭響起：“這是我賜予你的天資！”\n" NOR, me);
        write(sprintf(HIY "\n一道佛光籠罩你全身，你的秉性變化了：\n"
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

        if( time()-query("last_chouqian_time", me)<1800 )
                return notify_fail("這麼頻繁的抽籤幹嘛？心不誠則籤不靈，過半個小時再來吧。\n");

        write(HIC "你虔誠的抽了一根籤，閉目祈禱了一陣，才睜開眼睛看簽上所書文字。\n" NOR, me);
        write(HIC "簽上寫着：" + CHOUQIAN->query_chouqian() + "。\n" NOR, me);
        set("last_chouqian_time", time(), me);
        if( query("can_not_change", me))return 1;
        set("character", character[random(sizeof(character))], me);
        write(sprintf(HIY"\n你隱隱聽到一陣慈祥的聲音：朝『%s』的方向發展吧。\n"NOR,query("character", me)));
        return 1;
}
*/