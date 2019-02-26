//Cracked by Kafei
// mihan.c

inherit ITEM;
#include <ansi.h>

void create()
{
        set_name("密函", ({"mihan", "letter", "han"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("material", "paper");
        }
}

void init()
{
        add_action("do_give", "give");
}

int do_give(string arg)
{
        string target, item;
        object obj, who, me=this_player();

        if(!arg) return notify_fail("你要給誰什麼東西？\n");

        if( sscanf(arg, "%s to %s", item, target)==2
        || sscanf(arg, "%s %s", target, item)==2 );
        else return notify_fail("你要給誰什麼東西？\n");

        if ( item != "mihan" ) return 0;

        if ( !objectp(obj = present(item, me)) )
                return notify_fail("你身上沒有這樣東西。\n");

        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");

        if (!objectp(who = present(target, environment(me))) || !living(who))
                return notify_fail("這裏沒有這個人。\n");

        if ( userp(who) )
                return notify_fail("對方不接受這樣東西。\n");

        if( query("race", who) != "人類" )
                return notify_fail("別找碴兒！畜生也能讀信嗎？\n");

        if( who == me) return notify_fail("自己給自己？！\n");

        message_vision("$N給$n一封密函。\n", me, who);
        call_out("response", 1, me, who, obj);
        obj->move(who);

        return 1;
}

int response(object me, object who, object obj)
{
        string boss;

        switch(random(3)) {
                case 0:
                        boss = "大金完顏洪烈六王爺";
                        break;
                case 1:
                        boss = "蒙古鐵木真大汗";
                        break;
                case 2:
                        boss = "大遼耶律洪基聖上";
                        break;
                }

        message_vision("$N抽出密函仔細的看了一遍。\n", who);
        
        if( query("target_id", obj) != query("id", who )
         || query("target_name", obj) != who->name()){
                message_vision("$N抬起頭來，疑惑地説道：這信不是給我的呀？\n", who);

                if( query("shen", who)<0){
                        message_vision("$N奸聲笑道：嘿嘿！人不為己，天誅地滅！天大的富貴送上門來，豈能放過！\n", who);
                        message_vision("$N沉聲説道：我得趕緊向"+boss+"報告丐幫的計劃！\n", who);

                        if( random(query("kar", me))>10){
                                message_vision("$N猙獰地對$n説道：你只好自認倒黴，向閻王訴苦去吧！\n", who, me);

                                who->kill_ob(me);
                                me->kill_ob(who);
                        }
                        else {
                                message_vision("$N沉聲對$n説道：快滾！這密函我留下了！\n", who, me);
                        }

                        destruct(obj);
                }
                else {
                        message_vision("$N將密函還給$n，鄭重的説道：唉！你怎麼如此大意！要讓惡徒將消息走露那可怎麼辦？\n", who, me);

                        obj->move(me);
                }

                return 1;
        }
        else if( query("owner", obj) != query("id", me)){
                message_vision("$N抬起頭來，疑惑地説道：這信不應由你送來，你是怎麼得來的？\n", who);

                if( query("shen", who)<0){
                        message_vision("$N奸聲笑道：嘿嘿！人不為己，天誅地滅！天大的富貴送上門來，豈能放過！\n", who);
                        message_vision("$N沉聲説道：我得趕緊向"+boss+"報告丐幫的計劃！\n", who);

                        if( query("shen", me)>0 && random(query("kar", me))>10){
                                message_vision("$N猙獰地對$n説道：你只好自認倒黴，向閻王訴苦去吧！\n", who, me);

                                who->kill_ob(me);
                                me->kill_ob(who);
                        }
                        else if( query("shen", me)>0){
                                message_vision("$N沉聲對$n説道：快滾！這密函我留下了！\n", who, me);
                        }
                        else {
                                message_vision("$N拍着$n肩膀高聲説道：幹得好！這密函我留下了！你的功勞我記着便是。\n", who, me);
                        }

                        destruct(obj);
                }
                else {
                        message_vision("$N將密函還給$n，鄭重的説道：唉！你怎麼如此大意！要讓惡徒將消息走露那可怎麼辦？\n", who, me);
                        message_vision("$N説道：快將密函交還給丐幫吧！\n", who);

                        obj->move(me);
                }
                
                return 1;
        }
        else if( query("gb/job_pending", me)){
                set("gb/job_status", 2, me);
        }
        
        if( query("shen", who)<0){
                message_vision("$N抬起頭來，目中陰鷲一閃，沉聲説道：嘿！豈有此理，道不同不相為謀。\n", who);
                                
                if( random(query("kar", me))>10){
                        message_vision("$N沉聲對$n説道：嘿！俗話説兩國交鋒，不斬來使，但算你倒黴！\n", who, me);
                        message_vision("$N奸笑道：我正愁不知要送甚麼給"+boss+"以表達我的心意，你自個兒送上門來，可怨不得我！\n", who);

                        set_temp("kill_initiater", 1, who);
                        who->kill_ob(me);
                        me->kill_ob(who);
                        set("target_name", who->name(), obj);

                        remove_call_out("check_fight");
                        call_out("check_fight", 1, me, who, obj);
//                        me->start_call_out( (: call_other, __FILE__, "check_fight", me, obj :), 1);
                }
                else {
                        message_vision("$N沉聲對$n説道：快滾！甚麼狗屁國家民族大義？這世上只有金銀權位才是好東西！\n", who, me);
                        message_vision("$N大聲説道：識時務者為俊傑，你快叫魯老兒向"+boss+"投誠，否則大軍殺到，將你丐幫夷為平地！\n", who);
                        destruct(obj);
                }
        }
        else {
                message_vision("$N抬起頭來，對$n拱手説道：有勞"+RANK_D->query_respect(me)+"一路奔波，請代我問侯貴幫魯長老。\n", who, me);

                switch(random(3)) {
                case 0:
                        message_vision("$N説道：請告知魯長老説他交待的大事，我屆時一定會盡力，以盡俠義道的本分！\n", who);
                        break;
                case 1:
                        message_vision("$N説道：請告知魯長老説我屆時一定出席貴幫的君山大會，和他共襄盛舉。\n", who);
                        break;
                case 2:
                        message_vision("$N説道：請告知魯長老説我到時或有要事在身，未必能夠到來，深感汗顏。\n", who);
                        break;
                }

                destruct(obj);
        }

        return 1;
}

int check_fight(object me, object who, object obj)
{
        object corpse;

        if ( !objectp(obj) ) return 1;

        if ( objectp(corpse = present("corpse", environment(me))) 
         && query("victim_name", corpse) == query("target_name", obj )
         && query("my_killer", corpse) == query("id", me)){
                set("gb/job_kill",query("target_name",  obj), me);
                destruct(obj);
        }
        else if ( objectp(who) && !me->is_fighting(who) ) {
                destruct(obj);
        }
        else {
                call_out("check_fight", 1, me, who, obj);
//                me->start_call_out( (: call_other, __FILE__, "check_fight", me, obj :), 1);
        }

        return 1;
}