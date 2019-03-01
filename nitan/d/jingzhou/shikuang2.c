#include <ansi.h>
#include <room.h>
inherit ROOM;

void init()
{
        add_action("do_zha", "zha");
}

void create()
{
        set("short", "石礦");
        set("long", @LONG
這裡郊外一座荒山，怪石嶙峋，在山的另一邊不斷傳來一陣陣的
爆炸聲，原來已經有很多人在那邊炸(zha)山開採礦石。
LONG );
        set("outdoors","city");
        set("exits", ([
                "northup"  : "/d/jingzhou/shikuang1",
        ]));
        set("no_fight", 1);
        set("no_sleep_room",1);
        set("no_clean_up", 0);
        setup();
}

int do_zha(string arg)
{
        object me;
        me = this_player();

        if( !present("lei guan", me))
                return notify_fail(HIY"你要做什麼？\n"NOR);

        if( (!arg) || !((arg == "山") ))
                return notify_fail(CYN"你拿著雷管沒事幹呀！\n"NOR);

        if( query_temp("caiend", me) == 1 )
                return notify_fail(HIR"這裡已經被你炸平了，還想來破壞環境呀？\n"NOR);

        if( query("zha/山", me) == 1 )
                return notify_fail(HIM"雷管已經點燃了，你還要幹什麼？\n"NOR);

        if( me->is_busy()) 
                return notify_fail("你正忙著呢！！\n");

        if( (query("qi", me)<25) || (query("jing", me)<25) )
                return notify_fail(MAG"你太累了，賺錢也不急在一時。\n"NOR);
        
        if( query_temp("caistone", me) == 1){
        message_vision(HIW"$N笨手笨腳地找了個縫隙把雷管插進去，手忙腳亂地點燃了就溜！\n"NOR, me);
        remove_call_out("zha/山");
        set("zha/山", 1, me);
        call_out("bao", random(5) +5, me );
        return 1;
        }
        else {
                return notify_fail(HIY"沒事來搗亂呀！快滾！\n"NOR);
        }
}

int valid_leave(object me, string dir)
{
        if( dir == "northup" && query_temp("zha/山", me) == 1 )
                return notify_fail(HIW"你的雷管還插在那裡，想留下來害人嗎？\n"NOR);
        return 1;
}

void bao()
{
        object ob, me, obj, cor, cps, dex, guan;
        me = this_player();
        guan = present("lei guan", me);
        cor=query("cor", me);
        cps=query("cps", me);
        dex=query("dex", me);
        
        delete("zha/山", me);
        
        if( query("dex", me)<random(25)+5){
        message_vision(HIR"只聽到“轟”的一聲巨響，$N整個人飛了出去，原來爆炸力太強了，把自己都炸傷了。\n"NOR,me);
        me->receive_damage("qi", random(40)); 
        me->receive_damage("jing", random(40)); 
        me->start_busy(random(10) +5);
        return;
}       
        if( query("cor", me)<random(25)+5){
        message_vision(HIY"只聽到“轟”的一聲巨響，卻只有一些碎石滾下來，原來爆炸力太小了。\n"NOR,me);
        me->receive_damage("qi", random(10)); 
        me->receive_damage("jing", random(20)); 
        me->start_busy(random(5) +3);
        return;
}       
        if( query("cps", me)<random(25)+5){
        message_vision(BLU"$N閉著眼睛、捂著耳朵等了老半天，卻什麼都沒發生，原來雷管受潮死火了。\n"NOR,me);
        me->receive_damage("qi", random(10)); 
        me->receive_damage("jing", random(10)); 
        me->start_busy(random(8) +3);
        return;
}

else {
        message_vision(HIC"只聽到“轟”的一聲巨響，一塊大石從山上滾了下來。\n"NOR,me);
        delete_temp("caistone", me);
        set_temp("caiend", 1, me);
        destruct(guan);
        obj = new("/clone/misc/bigstone");
        obj->move(this_player());
        message_vision(MAG"$N連忙抬起那塊大石，生怕別人搶了他的勞動成果！！！\n"NOR, me);
        me->receive_damage("qi", random(10)); 
        me->receive_damage("jing", random(10));
        me->start_busy(random(3) +3);
     }
}