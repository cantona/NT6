// shechang.c 蛇場
// 白駝弟子用以培養新蛇的地方。
// maco 4/15/2000

#include <ansi.h>
inherit ROOM;

int THE_POISON = 0;
int AMOUNT = 0;
int MANAGE = 0;

int do_count();

void create()
{
        set("short", "蛇場");
        set("long", @LONG
這是歐陽世家所建的蛇場，從蛇谷捕捉來的毒蛇都在此飼養，四
周圍以丈許來高的灰色圓牆，牆腳砌成圓弧形，光滑無縫。場裏建了
許多蛇窩，由歐陽世家中的蛇奴負責管理，許多劇毒的怪蛇就是在此
雜交而得。
LONG );

        set("exits", ([
                "west" : __DIR__"road2",
        ]));
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/shenu" : 1,
         ]) );

        set("coor/x", -49960);
        set("coor/y", 20110);
        set("coor/z", 30);
        setup();
}

void init()
{
        add_action( "do_count", "count" );
        add_action( "do_manage", "manage" );
        add_action( "do_check", "check" );
        add_action( "do_return", "return");
}

int do_manage()
{
        object me = this_player();
        int asp;

        if( query("family/family_name", me) != "歐陽世家" )
                return notify_fail("管別人家的閒事幹嘛？\n");

        if( query("family/master_name", me) != "歐陽鋒" )
                return notify_fail("你還沒有資格養育自己的蛇羣。\n");

        if( (int)me->query_skill("poison", 1) < 100 )
                return notify_fail("你對毒技瞭解不夠透徹，還沒有辦法培養毒蛇。\n");

        if( query("baituo/new_breed_time", me) )
                return notify_fail("先等上回培養怪蛇的成果出來吧。\n");

        MANAGE = 1;
        asp = do_count();
        MANAGE = 0;

        if(! asp || asp == 0 )
                return notify_fail("");

        message_vision("\n$N將蛇羣趕進蛇窩，吩咐蛇奴好好培育。\n", me);
        if( wizardp(me) ) write("這些蛇培育出的蛇種，預期可擁有"+asp+"的毒性。\n");

        set("baituo/new_breed", asp, me);
        set("baituo/new_breed_time", time(), me);
        addn("baituo/manage", 1, me);
        delete("baituo/checked_snake", me);
        return 1;
}

int do_count()
{
        mapping snakes;
        string *names, str;
        int flag, average, i, num, sort, sort2, per;
        object me, obj;
        mixed *inv;

        me = this_player();
        obj = this_object();
        inv = all_inventory(obj);

        if( query("family/family_name", me) != "歐陽世家" )
                return notify_fail("管別人家的閒事幹嘛？\n");

        if( (wizardp(me) && query("env/snake_test", me) == "YES") || query_temp("test", me) )
                flag = 1;

        inv = map_array(inv, "snake_list", this_object() );

        str = sprintf("《蛇場管理》\n%s\n", implode(inv, "") );

        if(flag) write(str);

        str = "";

        if( mapp(snakes=query("snakes", obj))){
                names = keys(snakes);
                for(i=0; i<sizeof(names); i++)
                names -= ({ 0 });

                if( !sizeof(names) || sizeof(names)==0 ) {
                write("現在蛇場裏面就沒有你捕來的蛇呀。\n");
                return notify_fail("");
                }

                else if( sizeof(names)==1 )
                        str += "蛇場裏唯一由你捕捉到的蛇種是" + names[0] + NOR + "。\n";

                else str += sprintf("蛇場裏由你捕捉到的蛇有%s種，分別是%s和%s。\n",
                        chinese_number(sizeof(names)),
                        implode(names[0..sizeof(names)-2], "、"),
                        names[sizeof(names)-1]);

                //計算每種蛇的數量
                for (i = 0; i < sizeof(names); i++) {
                        num = query("snakes/"+names[i]);
                        sort = atoi(query("snakes_poison/"+names[i]));
                        per = 110-num*5;
                        sort2 = sort*per/100;

                        if(flag) printf("%s總共有%s條，蛇毒總值%d，乘以%d%%之後等於%d。\n",
                        names[i], chinese_number(num), sort, per, sort*per/100 );

                        THE_POISON += sort2;
                }

                average = THE_POISON / AMOUNT;

                if(flag)
                str += sprintf("共有%s條蛇，蛇毒總和：%d 蛇毒平均值：%d。\n"NOR,
                chinese_number(AMOUNT), THE_POISON, average);


                if ( MANAGE == 0 ) write(str);
        }
        else {
                write("現在蛇場裏面沒有你捕來的蛇。\n");
                return notify_fail("");
        }

        if(average < 100) {
                write("這些蛇種繁殖出來的蛇，毒性或許薄弱了點。\n");
                return notify_fail("");
        }

        if ( sizeof(names) < 3 ) {
                write("要培育怪蛇，起碼要取三種不同的蛇來繁殖。\n");
                return notify_fail("");
        }
        else if ( MANAGE == 1 ) {  //由manage指令讀取時，一邊計算一邊讓蛇消失
                inv = all_inventory(obj);
                for (i = 0; i < sizeof(inv); i++)
                if( query("race", inv[i]) == "蛇類"
                 && query("caught", inv[i]) == query("id", me))destruct(inv[i]);
        }

        if( MANAGE == 0 && average>query("baituo/breed", me )
         && query("baituo/breed", me)>100 )
                write(HIB"你暗自思量：若是用這些蛇，也許可以培養出毒性更勝以往的怪蛇。\n"NOR);

        THE_POISON = 0;
        AMOUNT = 0;
        delete("snakes");
        delete("snakes_poison");

        return average;

}

string snake_list(object obj, int flag)
{
        string str;
        mixed sp;

        sp=query("sk_poison", obj)*2;

        if( query("race", obj) == "蛇類"
         && query("caught", obj) == query("id", this_player())){
                str = sprintf("%-24s： 經驗：%-10d  蛇毒：%3s  \n" NOR,
                obj->name()+"("+query("id", obj)+")",query("combat_exp", obj),sp);

                AMOUNT += 1;
                addn("snakes/"+obj->name(), 1);
                addn("snakes_poison/"+obj->name(), sp);

                if ( !flag )
                        str = "  " + str;
                else
                        return 0;
        }
        else str = "";

        return str;
}

int do_check()
{
        object me = this_player();

        if( !wizardp(me) )return 0;

        write( sprintf(
        "breed: %d, new_breed: %d, new_breed_time: %d, checked_snake: %d \n"
        "passed time: %d, manage: %d, snake_amount: %d \n" ,
        query("baituo/breed", me),
        query("baituo/new_breed", me),
        query("baituo/new_breed_time", me),
        query("baituo/checked_snake", me),
        time()-query("baituo/new_breed_time", me),
        query("baituo/manage", me),
        query("baituo/snake_amount", me)));
        return 1;
}

int do_return(string arg)
{
        object me, snake;

        me = this_player();

        if( !arg || arg=="" ) return 0;

        if( !objectp(snake = present(arg, me)) && !objectp(snake = present(arg, environment(me))))
                return notify_fail("你要讓哪條蛇回蛇窩？\n" );

        if( query("race", snake) != "蛇類" )
                return notify_fail(snake->name()+"是"+query("race", snake)+"，可不是蛇類！\n");

        if( query("who_breed", snake) != query("id", me) )
                return notify_fail("這條"+snake->name()+"不是你培養出來的。\n" );

        message_vision("$N將$n趕回了蛇窩裏。\n", me, snake);

        if(snake->name() == "小怪蛇")
        addn("baituo/snake_amount", 1, me);

        destruct(snake);
        return 1;
}
