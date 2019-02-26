//Cracked by Kafei
#include <ansi.h>
#define TRAVERSER "/clone/obj/traverser"

//int playing(object me);
//int halt_play(object me);
//void sound_float(object me, int range);

void init()
{
        add_action("do_play", "play");
        add_action("do_lianxi", "lianxi");
        add_action("halt_play", "halt");
        add_action("halt_play", "end");

}

string *play_msg = ({
        HIM"但聽得簫聲連綿不斷，越來越是明徹，忽高忽低，愈變愈奇，實在美妙之極，柔媚之音縈繞耳際。",
        HIG"那簫聲忽高忽低，忽前忽後，忽焉在西，倏爾在南，似乎有十多人伏在四周，此起彼伏的吹簫戲弄一般。",
        MAG"簫聲調子陡變，似淺笑，似低訴，柔靡萬端。",
        HIG"只聽得簫聲由柔媚宛轉而漸漸急促，似是催人起舞。",
        HIM"這時那$w"+HIM"之聲情致飄忽，纏綿宛轉，便似一個女子一會兒歎息，一會兒呻吟，一會兒又軟語温存、柔聲叫喚。",
        HIM"$w"+HIM"曲調比適才更加勾魂引魄，柔媚宛轉，輕輕細細的耍了兩個花腔。",
        HIG"$N吹到清羽之音，只聽得簫聲越拔越高，愈吹愈是迴腸蕩氣。",
        HIM"$N曲調突轉，緩緩的變得柔靡萬端，恰如昆崗鳳鳴，深閨私語。",
});

string *bihai_play_msg = ({
        HIB"此時簫聲猶如潮水中魚躍鯨浮，海面上風嘯鷗飛，再加上水妖海怪，羣魔弄潮，忽而冰山飄至，忽而熱海如沸，極盡變幻之能事。",
        BLU"此時曲調如潮退後水平如鏡，海底卻又是暗流湍急，於無聲處隱伏兇險，更令聆曲者不知不覺而入伏，尤為防不勝防。",
        HIB"洞簫本以柔和宛轉見長，這時的音調卻極具峻峭肅殺之致。",
        BLU"$N又吹得半晌，$w"+BLU"聲愈來愈細，幾乎難以聽聞。這正是《碧海潮生曲》的厲害之處，簫聲愈輕，誘力愈大。",
});

string *succeed_msg = ({
        HIM"$n心頭一蕩，臉上不自禁的露出微笑，只感全身熱血沸騰，就只想手舞足蹈的亂動一番，方才舒服。",
        HIM"$n聽到簫聲，登時心神盪漾，情慾激動，心煩意亂之極，更覺心頭滾熱，喉乾舌燥。",
        HIM"$n心中一蕩，呆了一呆，又聽得一陣，只感面紅耳赤，血脈賁張，便想手舞足蹈一番。",
        HIM"那簫聲具有極大魔力，$n抵擋不住，凝神傾聽之下，心中的韻律節拍漸漸與簫聲相合。",
});

string *bihai_succeed_msg = ({
        HIB"$n只感心旌搖動，身不由主的一震一跳。",
        HIB"$n再支持了一陣，忽聽得簫聲中飛出陣陣寒意，霎時間便似玄冰裹身，不禁簌簌發抖。",
        HIB"$n被蕭聲所侵，漸感冷氣侵骨，身子凜有寒意。",
});

string *fail_msg = ({
        "$n剛想隨着簫聲伸手踢足，立時驚覺，潛運$f，竭力鎮攝心神。",
        "總算$n功力精湛，心頭尚有一念清明，硬生生把伸出去揮袖舞蹈的手縮了回來。",
        "$n寧定心神，心中一片空明，不着片塵，任$N簫聲再蕩，聽來只與海中波濤、樹梢風響一般無異。",
        "$n只感心中一蕩，臉上發熱，連忙鎮懾心神。",
});

string *bihai_fail_msg = ({
        "但是$n防護周密，抱元守一，靜心凝志，$N連變數調，卻也不能將$p降服。",
        "$n暗暗凝神守一，專守不攻，對這簫聲雖是應付裕如，卻也不敢有絲毫怠忽。",
});

string *dazuo_fail_msg = ({
        "$n盤膝坐在地下，低頭行功，奮力抵禦簫聲的引誘。",
        "$n左手撫胸，右手放在背後，潛運$f，收斂心神，對$N的吹奏全然不聞不見。",
        "$n盤膝而坐，數次身子已伸起尺許，終於還是以極大的定力坐了下來。",
        "$n盤膝坐在地上，一面運起$f，摒慮寧神，抵禦簫聲的引誘。",
});

string *faint_msg = ({
        HIM"但聽得簫聲流轉，$n再也忍耐不住，跟著簫聲翩翩起舞......",
        HIM"$n聽了片刻簫聲，自制之力漸失，不由自主的婆娑起舞......",
        HIM"$n覺得全身飄飄欲仙，臉上露出迷惘而滿足的神情，情不自禁的手舞足蹈起來......\n",
});

int do_play()
{
        int i, count, range;
        object me, ob, weapon;
        string msg, play_type, *shape;

        ob = this_object();
        me = this_player();
        shape=query("shape", ob);

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("你現在正忙着呢。\n");
                
        if( me->query_skill_mapped("force") != "bitao-xuangong" )
                return notify_fail("你所用的並非碧濤玄功，無法施展碧海潮生曲！\n");
        
        if( me->query_skill("force") < 120 )
                return notify_fail("你的碧濤玄功火候未到，無法施展碧海潮生曲！\n");

        if( (int)me->query_skill("music", 1) < 100 )
                return notify_fail("憑你的音律造詣，還無法吹奏得出碧海潮生曲。\n");

        if( query("neili", me)<800 )
                return notify_fail("你的內力不夠。\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你手中並沒有拿簫。\n");

        if( query("name", weapon) != query("name", ob) )
                return notify_fail("你手中並沒有拿簫。\n");

        for( i=0; i < sizeof(shape); i++ )
                if( shape[i] == "flute" )
                {
                        count++;
                        break;
                }

//        if( !count ) return notify_fail("你手中並沒有拿簫。\n");
        
        
        if( query_temp("wuzhuan", me) && !query_temp("playing_bihai", me) )
        msg = "但見$N神色鄭重，手按$n，邊走邊吹，腳下踏着八卦方位。";
        else msg = "$N$n就脣，幽幽咽咽的吹了起來。";
        if( query("no_fight", environment(me)) )
                msg += "這吹奏不含絲毫內力，便與常人吹簫無異。\n";
        else
        {
                msg += "\n";
                addn("neili", -200, me);
                me->receive_damage("qi", 10);
                play_type = "martial";
        }

        message_vision(msg, me, ob);
        set_temp("apply/short", ({me->name()+"正吹奏著"+ob->name()+"。"}), me);
        set_temp("play_type", play_type, me);

        message_vision(HIC"突然之間，半空中如鳴琴，如擊玉，發了幾聲，接着悠悠揚揚，飄下一陣清亮柔和的洞簫聲來。\n"NOR, me);
//        me->start_busy((: playing :), (: halt_play :));
        me->start_busy(2);
        call_out("playing", 1, me);
//                range = 1+(me->query_skill("bitao-xuangong", 1)-100)/4;
//                sound_float(me, range);
                set_temp("exercise/playing", 1, me);

        return 1;
}

void playing(object me)
{
        string play, succeed, fail, faint, map_force;
        int range, i, k=0, flag, music, music2, force, force2, tag, attacker, defender,damage,times;
        object *target, ob, env;
        
        env = environment(me);
        ob=query_temp("weapon", me);
        force = me->query_skill("force");
        music = (int)me->query_skill("music",1);
        times=query_temp("played_times", me);

        if( !query_temp("exercise/playing", me) )
        {
                message_vision(CYN"簫聲忽停，四下闃無聲息，一音裊裊，曲終音歇。\n"NOR, me);
                delete_temp("apply/short", me);
                me->set_temp("delete/playing");
                delete_temp("played_times", me);
                delete_temp("playing_bihai", me);
                delete_temp("exercise/playing", me);
                return 0;
        }


        me->start_busy(2);

        if( !objectp(ob) )
        {
                message_vision(CYN"$N手中無簫，簫聲頓停。\n"NOR, me);
                delete_temp("apply/short", me);
                me->set_temp("delete/playing");
                delete_temp("played_times", me);
                delete_temp("playing_bihai", me);
                delete_temp("exercise/playing", me);
                return 0;
        }
        if( query("jing", me)<200 || query("neili", me)<200
        || !living(me) || me->is_ghost())
        {
                if( query("jing", me)<200 )
                        tell_object(me,"你的精神不足以繼續吹奏碧海潮生曲了。\n");
                if( query("neili", me)<200 )
                        tell_object(me,"你的內力不足以繼續吹奏碧海潮生曲了。\n");
                message_vision(CYN"簫聲忽停，四下闃無聲息，一音裊裊，曲終音歇。\n"NOR, me);
                delete_temp("apply/short", me);
                me->set_temp("delete/playing");
                delete_temp("played_times", me);
                delete_temp("playing_bihai", me);
                delete_temp("exercise/playing", me);
                return 0;
        }

        target = all_inventory(environment(me));

                for(i=0; i<sizeof(target); i++) {
                if( !living(target[i]) || target[i]==me ) continue;
                k++;
                }

        if( k<1 && !query("no_fight", environment(me))){
                tell_object(me,CYN"四下並無敵人，無需再吹奏碧海潮生曲了。\n"NOR);
                delete_temp("apply/short", me);
                me->set_temp("delete/playing");
                delete_temp("played_times", me);
                delete_temp("playing_bihai", me);
                delete_temp("exercise/playing", me);
                return 0;
        }
        else {
                if( query_temp("wuzhuan", me) && !query_temp("playing_bihai", me)){

                        set_temp("apply/short", ({me->name()+"手按"+ob->name()+"，腳下踏着八卦方位，邊行邊吹。"}), me);
                        addn_temp("playing_bihai", 1, me);//改為碧海msg
                }

                //決定play訊息類別
                if( query_temp("playing_bihai", me) == 1 )
                play = HIC"這套曲子模擬大海浩淼，萬里無波，遠處潮水緩緩推近，漸近漸快，其後洪濤洶湧，白浪連山。";
                else if( !query_temp("playing_bihai", me) )
                play = play_msg[random(sizeof(play_msg))];
                else 
                play = bihai_play_msg[random(sizeof(bihai_play_msg))] ;
                //end
                
                if( query("neili", me)<random(600))message_vision(CYN"簫聲忽地微有窒滯，但隨即迴歸原來的曲調。\n"NOR,me);//警告play者


                if(times != 0 && times/2 * 2 == times)
                        message_vision("", me);
                else message_vision("\n"+replace_string( play, "$w", ob->name() ) +"\n"NOR, me, ob);

                me->receive_damage("jing", 20+random(20), "精力透支過度死了");

                if( query("no_fight", environment(me))){//nofight-roomnouse
                call_out("playing", 1, me);
                return;
                }

                //play效果計算
                addn_temp("played_times", 1, me);

                if( query("id", this_object()) == "yuxiao" )
                flag = 2;
                else flag = 1;

                attacker=query("neili", me)/20+random(force)/2+random(music*flag);

                if( query_temp("wuzhuan", me) )
                attacker=query("neili", me)/20+random(force)/2+random(music*flag)+times*10;
                if( attacker <= 0 ) attacker = 0;
                //開始重複計算所有敵人
                for(i=0; i<sizeof(target); i++) {
                
                if( !living(target[i]) || target[i]==me ) continue;
                                        //決定訊息類別 2

                if( !query_temp("playing_bihai", me)){
                play = play_msg[random(sizeof(play_msg))];
                succeed = succeed_msg[random(sizeof(succeed_msg))];
                fail = fail_msg[random(sizeof(fail_msg))];
                }
                else {
                play = bihai_play_msg[random(sizeof(bihai_play_msg))] ;
                succeed = bihai_succeed_msg[random(sizeof(bihai_succeed_msg))];
                fail = bihai_fail_msg[random(sizeof(bihai_fail_msg))];
                }
                faint = faint_msg[random(sizeof(faint_msg))];
                
                if( query_temp("pending/exercise", target[i]) || query_temp("pending/respirate", target[i]) )
                fail = dazuo_fail_msg[random(sizeof(dazuo_fail_msg))];
                
                        //end

                tag=query("married_times", target[i]);
                if(tag > 20) tag = 20;
                music2 = (int)target[i]->query_skill("music",1);
                force2 = target[i]->query_skill("force");
                defender=query("neili", target[i])/25-tag*5+random(force2)+music2;
                //打坐、吐納時防禦提高
                if( query_temp("pending/exercise", target[i]) || query_temp("pending/respirate", target[i]) )
                defender=query("neili", target[i])/10-tag*10+random(force2)+music2;

                if(defender < 1) defender = 1;

                if( times/2*2 != times && query("family/family_name", target[i]) == "桃花島" && music2>music/2){
                        message_vision("$n盡知曲中諸般變化，與$N心神如一，自是不受危害。\n"NOR, me, target[i]);
                        }
                else if( attacker < defender ) {
                
                map_force = target[i]->query_skill_mapped("force");
                if (!target[i]->query_skill_mapped("force")) map_force = "force";
                        if( query("race", target[i]) != "人類" || times/2*2 == times )
                        message_vision("", me, target[i]);
                        else message_vision( replace_string( fail, "$f", to_chinese(map_force)) +"\n"NOR, me, target[i]);
                        if( wizardp(me) && query("env/check_play", me) )
                        tell_object(me,sprintf("attacker：%d ,defender：%d \n"
                        ,attacker,defender));
                }
                else {
                        damage=force+music/3+random(music/2)*flag+random(tag*10)+(-query("max_neili", target[i])/30)+-random(force2/2)+-force2/3;
                        if( damage > 600+flag*200 ) damage = 600+flag*200; // most ppl have at most 1k+ jing
                        if( damage < 100 ) damage = 100;

                        damage=damage+query_temp("playing_bihai", me)*8;
                        
                        if( wizardp(me) && query("env/check_play", me) )
                        tell_object(me,sprintf("attacker：%d ,defender：%d ,damage：%d \n"
                        ,attacker,defender,damage));

                        if( damage > 0 ) {
                        target[i]->receive_damage("jing", damage, me);

                        addn("jingli", -damage, target[i]);
                        addn("neili", -damage, target[i]);
                        addn_temp("be_played/"+query("id", me), 1, target[i]);
                        target[i]->start_busy(random(2));

                        if( !target[i]->is_killing(query("id", me)) || !target[i]->is_fighting(me) || !me->is_fighting(target[i]) )
                        target[i]->kill_ob(me);

                        //target[i]->set_temp("last_damage_from",me);
                        //不同曲調傷害不同
                        if( !query_temp("playing_bihai", me) )
                        target[i]->receive_damage("jing", random(damage/3 + tag*5), me);
                        else addn("neili", -random(damage/2), target[i]);
                        //
                        if( query("neili", target[i])<0 )
                                set("neili", 0, target[i]);

                        if( (query("jing", target[i])<0 || query("jingli", target[i])<0 )
                         && query("race", target[i]) == "人類" )
                        message_vision( faint+"\n"NOR, me, target[i]);
                        else if( (query("jing", target[i])<0 || query("jingli", target[i])<0) && query("race", target[i]) != "人類" )
                        message_vision("只見$n昂起了頭，隨着簫聲搖頭擺腦的舞動。\n"NOR, me, target[i]);
                        else if(times/2 * 2 == times)
                        message_vision("", me, target[i]);
                        else if( query("race", target[i]) != "人類" )
                        message_vision("只見$n昂起了頭，隨着簫聲搖頭擺腦的舞動。\n"NOR, me, target[i]);
                        else message_vision( succeed +"\n"NOR, me, target[i]);
                        }
                        }
                }
                //play效果計算到這

                if( wizardp(me) && query("env/check_play", me) )
                        tell_object(me,sprintf("times：%d\n" ,times));

                if( query_temp("playing_bihai", me))addn_temp("playing_bihai", 1, me);
                addn("neili", -100, me);
                set("playing", me, env);
                call_out("playing", 1, me);
                return;
        }
}

int halt_play()
{
        object me;
        me = this_player();
        if( query_temp("exercise/playing", me)){
        message_vision(CYN"簫聲忽停，四下闃無聲息，一音裊裊，曲終音歇。\n"NOR, me);
        delete_temp("apply/short", me);
        me->set_temp("delete/playing");
        delete_temp("played_times", me);
        delete_temp("playing_bihai", me);
        delete_temp("exercise/playing", me);
        remove_call_out("playing");
        return 1;
        }
        else return 0;
}
