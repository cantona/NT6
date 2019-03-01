// Room: /d/gumu/jitan.c
// Last Modifyed by Winder on Jan. 14 2002

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIC"石室"NOR);
        set("long",@long
一間空盪盪的石室，正前方放著一個祭壇，上面呈放著一些瓜果，
兩邊香燭散發出搖曳的火光，一些古墓弟子正將侵犯古墓的叛逆的首級
呈放在祭壇兩側用來告慰先祖的英靈。
long);

        set("exits",([
                "west" : __DIR__"mudao21",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3180);
        set("coor/y", 0);
        set("coor/z", 90);
        setup();
}

void init()
{
//        add_action("do_jibai","jibai");
//        add_action("do_ketou","ketou"); 
}

int do_jibai(string arg)
{
        object ob, me=this_player();
        int exp, pot, score;
        
        ob = present("head", me);
        if ( arg == "head")
        {
                if ( ! ob )
                        return notify_fail("你沒有人頭，祭拜什麼？\n");        
                if( !query_temp("gm/job", me) )
                        return notify_fail("你還沒去巡邏呢，哪裡撿來的首級？\n");
                if( query("name", ob) != "蒙面女子的首級" )
                        return notify_fail("你哪裡弄來的人頭，這人好象不是古墓叛逆啊？\n");        
                if( query("victim_user", ob) )
                        return notify_fail("你哪裡弄來的首級，殺錯人了吧？\n");
//                if( ob->query("kill_by") != me)
//                        return notify_fail("這好象不是你殺的吧？你是怎麼得到這個人頭的？\n");
                message_vision(HIY"$N恭恭敬敬地磕了幾個響頭，然後慢慢將$n呈放在祭壇兩側。\n"NOR,me,ob);
                exp =30+random(20);
                addn("combat_exp", exp, me);
                pot= 20+random(10);
                addn("potential", pot, me);
                score= 5+random(5);
                addn("score", score, me);
                delete_temp("gm/job", me);
                delete_temp("meet_nuzi", me);
                call_out("destroying", 1, ob);
                tell_object(me,HIW"你被獎勵了：\n" + 
                chinese_number(exp) + "點實戰經驗\n" +
                chinese_number(pot) + "點潛能\n" +
                chinese_number(score) + "點師門忠誠度\n"NOR);        
                return 1;
        }
        return notify_fail("你拿什麼祭拜啊？\n");
}

void destroying(object ob)
{
        destruct(ob);
        return;
}

int do_ketou(string arg)
{
        mapping fam;
        object me=this_player();
        if( !(fam=query("family", me)) || fam["family_name"] != "古墓派" )
                return notify_fail("你不是古墓傳人，在此磕頭作甚？\n");
        if ( arg == "jitan")
        {
                if( query("combat_exp", me)<30000 )
                        return notify_fail("你看著祭壇，心感武藝太差，不由惶恐不安，又慢慢站起了身。\n");
                if( query("combat_exp", me)>180000 )
                        return notify_fail("你還是去江湖上多幹些事來告慰祖師吧！\n");
                if( query_temp("bishou", me)<2 )
                {
                        if(objectp(present("bi shou", me)))        
                                return notify_fail("你發現盒子裡已經空盪盪的，什麼也沒有了。\n");
                        addn_temp("bishou", 1, me);
                        message_vision(HIY"$N恭恭敬敬地對著祭壇磕起頭來。\n"NOR, me);
                        return 1;
                }
                message_vision(YEL "祭壇緩緩轉動，$N從裡面的小盒子裡拿出一把匕首。\n"NOR, me);
                delete_temp("bishou", me);
                new(__DIR__"obj/bishou")->move(me);
                return 1;
        }
        return notify_fail("你對著什麼磕頭啊？\n");
}
