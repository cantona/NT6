// huoqian.c
//modefied by sega 1/15/99 改成不能在no_fight的地方catch

#include <ansi.h>;
inherit ITEM;
//inherit F_CLEAN_UP;
void setup()
{}

void init()
{
        add_action("do_watch","guancha");
        add_action("do_watch","watch");
        add_action("do_catch","daibu");
        add_action("do_catch","catch");
        add_action("do_catch","kill");
        add_action("do_catch","hit");
}
int is_container() { return 1; }

void create()
{
        set_name(HIR"火簽"NOR, ({"huo qian","hq" }));
        set_max_encumbrance(10);
        set("unit", "塊");
        set("long", "這是一塊朱紅的火簽，精鋼打造，用來証明官府人士的身份。\n帶著它你就有權搜尋罪犯(guancha/watch)，逮捕嫌疑犯(daibu/catch)。\n");
        set("value", 0);
        set("no_drop", "這樣東西不能離開你。\n");
        set("no_get", "這是官府的東西，平常人拿了會惹麻煩的。\n");
        set("no_get_from", "這是官府的東西，平常人拿了會惹麻煩的。\n");
        set("no_put", "這是官府的東西，別到處亂放。\n");
        set_weight(200);
        set("place","on");

        setup();
}
int do_watch(string arg)
{
        object obj,new_obj;
        object me = this_player();
        object ob = this_object();
        string targ;

        if( !query("officerlvl", me) )
                return notify_fail("你並非朝廷官員，何必操這份閒心？\n");

        if (!ob=present("huo qian",me))
                return notify_fail("什麼？\n");
        if( query_temp("bt/finish", me) )
                return notify_fail("程大人等著回話哪，你還在磨蹭什麼？\n");
        if (!arg||!obj=present(arg,environment(me)))
                return notify_fail("你要觀察誰？\n");
        if (!obj->is_character() || obj->is_corpse() )
                return notify_fail("你只能觀察一個活的物體。\n");
        if (!present("picture",ob))
                return notify_fail("你早已經發現了嫌疑犯，還磨蹭什麼？\n");
        if (me->is_busy() )
                return notify_fail("你正忙著。\n");

        targ=query("name", obj);
        tell_object(me,"你用銳利的眼神盯著"+targ+"。\n\n");
        me->start_busy(1);
        if( query("bt_tufei", obj) == query_temp("bt/npc", me) && 
                random(query("kar", me)+15)>20 && 
                !query("no_fight", environment(me)) )
        {
                switch(random(5))
                {
                        case 0:
tell_object(me,WHT"你發現"+targ+"忽然把頭一低，似乎想避開你的目光。\n\n"NOR);
                                break;
                        case 1:
tell_object(me,WHT"你發現"+targ+"忽然打了個哆嗦，面如土色。\n\n"NOR);
                                break;
                        case 2:
tell_object(me,WHT"你發現"+targ+"太陽穴高高墳起，似乎是個練武的人。\n\n"NOR);
                                break;
                        case 3:
tell_object(me,WHT"你發現"+targ+"腰間鼓鼓囊囊的，樣子象是一件兵刃。\n\n"NOR);
                                break;
                        case 4:
tell_object(me,WHT"你發現"+targ+"的眼中精光一閃，馬上又變的一臉茫然。\n\n"NOR);
                                break;
                }
                set_temp("bt/faxian", 1, me);
                set_temp("bt_faxianed",query("id",  me), obj);
        }
        else
        {
                switch(random(11))
                {
                        case 0:
tell_object(me,"只見"+targ+"正擠眉弄眼，色迷迷的東張西望。\n\n");
                                break;
                        case 1:
tell_object(me,"只見"+targ+"餓得面黃肌瘦，骨瘦如柴。\n\n");
                                break;
                        case 2:
tell_object(me,"只見"+targ+"面頰微紅，一臉嬌羞的模樣。\n\n");
                                break;
                        case 3:
tell_object(me,"只見"+targ+"滿臉橫肉，嘴臉兇頑。\n\n");
                                break;
                        case 4:
tell_object(me,"只見"+targ+"悲痛欲絕，哭的象個淚人似的。\n\n");
                                break;
                        case 5:
tell_object(me,"只見"+targ+"手足僵硬，渾身散發著金屬光澤。\n\n");
                                break;
                        case 6:
tell_object(me,"只見"+targ+"面無表情，呆若木雞。\n\n");
                                break;
                        case 7:
tell_object(me,"只見"+targ+"長得尖嘴猴腮，目光狡詐。\n\n");
                                break;
                        case 8:
tell_object(me,"只見"+targ+"幹笑幾聲，臉上擠出一絲媚笑。\n\n");
                                break;
                        case 9:
tell_object(me,"只見"+targ+"挺胸疊肚，一臉傲慢的神色。\n\n");
                                break;
                        case 10:
tell_object(me,"只見"+targ+"長得明眸皓齒，一臉天真的神色。\n\n");
                                break;
                }
        }
        return 1;
}
int do_catch(string arg)
{
        object obj,new_obj;
        object me = this_player();
        object ob = this_object();                        //100
        if( query("no_fight", environment(me)) )
                return notify_fail("這裡禁止戰鬥。\n");

        if (!ob=present("huo qian",me))
                return notify_fail("什麼？\n");
        if( !query("officerlvl", me) )
                return notify_fail("你並非朝廷官員，何必操這份閒心？\n");
        if( query_temp("bt/finish", me) )
                return notify_fail("程大人等著回話哪，你還在磨蹭什麼？\n");
        if (!arg||!obj=present(arg,environment(me)))
                return notify_fail("你要逮捕誰？\n");
        if( !obj->is_character() || obj->is_corpse() )
                return notify_fail("你只能逮捕一個活人。\n");
        if( !query_temp("bt/faxian", me )
                 || query_temp("bt_faxianed", obj) != query("id", me) )
                return notify_fail("揚州紀律嚴明，沒有証據怎好拿人？\n");
        message_vision ("$N對著$n冷笑一聲道：閣下的案子發了，老老實實跟本官走一趟。\n\n",me,obj);
        message_vision (RED"$n大叫一聲揭開偽裝，露出本來面目。\n$n大喝道：老子和你拼了！\n\n"NOR,me,obj);
        delete_temp("bt_faxianed", obj);
        destruct(obj);
        new_obj = present("picture",ob);
        set_temp("bt_npc",query_temp("bt/npc",  me), new_obj);
        set_temp("bt_ownname",query("id",  me), new_obj);
        new_obj->move(environment(me));
        me->kill_ob(new_obj);
        new_obj->set_leader(me);
        delete("no_see", new_obj);
        new_obj->start_busy(random(1));
        delete_temp("bt/faxian", me);
        return 1;
}
