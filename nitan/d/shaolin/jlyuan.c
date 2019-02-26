// Room: /d/shaolin/jlyuan.c
// Date: YZC 96/01/19

#include <ansi.h>
#include <login.h>

inherit ROOM;

void create()
{
        set("short", "戒律院");
        set("long", @LONG
整個大殿門户緊閉，密不透風。即便是在白晝，也猶如黑夜一般，
每隔幾步的牆上，點燃着幾枝牛油巨燭。下方擺着一排排烙鐵、水牛
皮鞭、穿孔竹板及狼牙棒等刑具。四周站滿了手持兵刃的執法僧兵。
他們正用冷酷的眼神打量着你，令你不禁渾身哆嗦起來。
LONG );
        set("no_fight", "1");
        set("exits", ([
                "southdown" : __DIR__"guangchang3",
        ]));
        set("valid_startroom",1);
        set("objects",([
                CLASS_D("shaolin") + "/xuan-tong" : 1,
                __DIR__"npc/seng-bing2" : 3,
                __DIR__"npc/xiao-tong" : 1
        ]));
        setup();
}

void init()
{       
        mapping fam;
        object ob;

        if (interactive(ob = this_player()))
        {
                if( mapp(fam=query("family", ob) )
                &&  fam["family_name"] == "少林派" 
                &&  fam["generation"] == 37
                 && query("guilty", ob) == 0 )
                        return;
                else 
                {
                        message_vision(HIY "$N" HIY "一進戒律院，...只聽幾聲"
                                       "大喝，如同炸雷般在大殿裏迴響。"
                                       "$N" HIY "不禁渾身發抖，再也站立不住，"
                                       "腿一軟，撲通一聲跪了下來。\n\n" NOR,
                                       ob);

                        set("startroom", "/d/shaolin/jlyuan", ob);

                        call_out("processing", 3, ob);
                }
        }
}

void processing(object ob)
{
        mapping fam;

        if (! objectp(ob))
                return;
        write(HIW "\n你定了定神，抬頭細看，只見數十名持刀僧人將你團團圍起來，\n"
                "一片雪亮的刀光逼得你眼都睜不開。正前方的高台上放着一把\n"
                "太師椅，居中高坐着位白鬚白眉的老僧，臉色鐵青，目射精光，\n"
                "狠狠地瞪着你。\n\n\n" NOR);

        if( !(fam=query("family", ob)) || fam["family_name"] != "少林派" )
                message_vision(HIY "玄痛一聲大喝：爾等大膽狂徒，擅闖本寺"
                               "護法松林，意在不軌，該當何罪！"
                               "堂堂少林寺，豈能容你等宵小如此胡作非為！執法僧"
                               "兵何在！\n\n" NOR, ob);

        if( (fam=query("family", ob)) && fam["family_name"] == "少林派" )
        {
                if( query("guilty", ob) == 1 )
                        message_vision(HIY "玄痛一聲大喝：$N" HIY "！你離寺僅有"
                                       "數日，卻在外殺人越貨，胡作非為，"
                                       "累犯大戒，敗壞本寺千載清譽！你該當"
                                       "何罪？！執法僧兵何在！\n\n" NOR, ob);

                if( query("guilty", ob) == 3 )
                        message_vision(HIY "玄痛一聲大喝：$N" HIY "！本寺護法鬆"
                                       "林歷代向來不許門人弟子擅入，"
                                       "你擅闖此地，意在不軌，該當何罪！執法"
                                       "僧兵何在！\n\n" NOR, ob); 

                if( query("guilty", ob) == 2 )
                {
                        message_vision(HIY "玄痛盯着$N" HIY "看了半餉，説"
                                       "道：$N" HIY "，你懲惡揚善，鋤暴安"
                                       "良，當得表彰，但出家人首戒殺生，你"
                                       "傷害人命，乃是僧家的重罪！ "
                                       "你去罷，下次定不輕饒！\n\n" NOR, ob);

                        set("guilty", 0, ob);
                        set("startroom", START_ROOM, ob);
                        ob->move("/d/shaolin/guangchang3");
                        return;
                }
        
        }

        call_out("responsing", 3, ob, 3);
}

void responsing(object ob, int i)
{
        int j;

        if (! objectp(ob))
                return;
        message_vision(HIR "僧兵大聲應道：弟子在！\n" NOR, ob);

        i--;
        j = random(3);

        if (i == 0) 
        {       
                call_out("beating", 3, ob);
                return;
        }

        call_out("responsing", j, ob, i);
}

void beating(object ob)
{
        if (! objectp(ob))
                return;

        message_vision(HIY "\n\n玄痛喝道：杖責三百，將$N" HIY
                       "打入僧監拘押三月，非洗心悔改，"
                       "不得釋放！意圖越獄者罪加一等！\n\n" NOR, ob);

        message_vision(HIR "僧兵們一湧而上，亂棒齊下，$N" HIR "痛得昏了"
                       "過去......\n" NOR, ob);

        if( query("guilty", ob)>0)set("guilty", 0, ob);
        
        ob->move("/d/shaolin/jianyu");
        ob->unconcious();

}

int valid_leave(object me, string dir)
{
        mapping fam;

        if (userp(me) && dir == "southdown")
        {
                if( mapp(fam=query("family", me) )
                &&  fam["family_name"] == "少林派" 
                &&  fam["generation"] == 37  ) 
                        return ::valid_leave(me, dir);
                else
                        return notify_fail("玄痛説道: 大膽，你還敢逃跑！執法僧兵何在！\n");
        }

        return ::valid_leave(me, dir);
}
