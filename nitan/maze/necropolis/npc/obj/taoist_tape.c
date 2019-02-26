#include <ansi.h> 
inherit ITEM;

void create()
{
        set_name("錄音帶", ({ "tape" }) );
        set_weight(2);
        set("no_get", 1);
        set("no_put", 1);
        set("value",10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "錄音帶。\n");
                set("value", 1);
        }
        setup();
} 

void play_sound_0(object speaker,int index) {
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一説道：我乃當今三清宮掌門丁乘風的師叔......\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一説道：近來此處墓園發生異變，我帶領門下弟子來察看，不想遭遇不測......\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一説道：這個墓園深處裏有一處聚靈法陣，其下鎮壓了一個上古血魔。\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),CYN"丁一説道：我等發現，無數死靈已經從法陣中逃逸，血魔亦有脱困的跡象。\n"NOR);
                        break;
                case(4):
                        tell_room(environment(),CYN"丁一説道：就在我們重新佈置法陣的時候，一羣少林和尚殺了過來。\n"NOR);
                        break;
                case(5):
                        tell_room(environment(),CYN"丁一説道：這些和尚一定是受到了血魔的詛咒，喪心病狂了。\n"NOR);
                        break;
                case(6):
                        tell_room(environment(),CYN"丁一説道：我們兩方鬥了個兩敗俱傷，弟子們拚死保護我，如今只剩我一個重傷逃離至此......\n"NOR);
                        break;
                case(7):
                        tell_room(environment(),YEL"丁一嗚嗚的哭起來......\n"NOR);
                        break;
                case(8):
                        tell_room(environment(),CYN"丁一説道：你可願意幫我們對付血魔？(accept yes/no)\n"NOR);
                        set_temp("開場白結束", 1, speaker);
                        break;
                default: 
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;

        }
        call_out("play_sound_0",1,speaker,++index);
}

void play_sound_1(object speaker,int index) {
        object mazeobj;
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一説道：嗯......多謝......\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一説道：血魔實在是法力無邊......他最擅長誘惑......我已經分不清敵我！\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一説道：就請你證明尚未被血魔誘惑: 殺八個骷髏，八個幽靈，八個殭屍。\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),CYN"丁一説道：完成後再來找我(report)。\n"NOR);
                        set_temp("任務", 1, speaker);
                        break;
                default: 
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 1, mazeobj);
                                set("quest/quest_name", "證明忠誠", mazeobj);
                                set("quest/quest_desc", "殺八個骷髏，八個幽靈，八個殭屍", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                set("quest/to_kill/骷髏", 8, mazeobj);
                                set("quest/to_kill/幽靈", 8, mazeobj);
                                set("quest/to_kill/殭屍", 8, mazeobj);
                        }
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
        }
        call_out("play_sound_1",1,speaker,++index);
}

void play_sound_2(object speaker,int index) {
        object mazeobj;
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一説道：好...做得不錯!\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一説道：想要挑戰血魔, 先要了解血魔的能力......\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一説道：這個墓園有很多血魔的手下......他的每個手下代表了他的一種能力！\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),CYN"丁一説道：去嘗試着殺掉三個骷髏武士，三個骷髏法師，三個幽靈之眼，三個幽靈之火，三個血殭屍，和三個屍煞。\n"NOR);
                        break;
                case(4):
                        tell_room(environment(),CYN"丁一説道：完成後再來找我(report)。\n"NOR);
                        set_temp("任務", 2, speaker);
                        break;
                default: 
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                delete("quest/to_kill", mazeobj);
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 2, mazeobj);
                                set("quest/quest_name", "證明實力", mazeobj);
                                set("quest/quest_desc", "殺三個骷髏武士，三個骷髏法師，三個幽冥之眼，三個幽冥之火，三個血殭屍，三個屍煞", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                set("quest/to_kill/骷髏武士", 3, mazeobj);
                                set("quest/to_kill/骷髏法師", 3, mazeobj);
                                set("quest/to_kill/幽冥之眼", 3, mazeobj);
                                set("quest/to_kill/幽冥之火", 3, mazeobj);
                                set("quest/to_kill/血殭屍", 3, mazeobj);
                                set("quest/to_kill/屍煞", 3, mazeobj);
                        }
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
        }
        call_out("play_sound_2",1,speaker,++index);
}

void play_sound_3(object speaker,int index) {
        object mazeobj;
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一説道：做得很好!\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一説道：你有這樣的實力我就放心了！\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一説道：去找到那些墮落的少林和尚，殺了他們。他們手中有個法器，可以對付血魔。\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),CYN"丁一説道：完成後再來找我(report)。\n"NOR);
                        set_temp("任務", 3, speaker);
                        break;
                default: 
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                delete("quest/to_kill", mazeobj);
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 3, mazeobj);
                                set("quest/quest_name", "排除異己", mazeobj);
                                set("quest/quest_desc", "殺少林和尚，取得法器", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                set("quest/to_kill/心武", 1, mazeobj);
                                set("quest/to_find/聚靈塔", 1, mazeobj);
                        }
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
        }
        call_out("play_sound_3",1,speaker,++index);
}

void play_sound_4(object speaker,int index) {
        object mazeobj;
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一説道：太好了!可惡的和尚，跟我爭......哈哈.....哦...那個...咳咳...\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一説道：啟動聚靈法陣需要一些陰氣較盛的東西為引，\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一説道：巫妖的骨杖，幽冥魔的幽冥之火，殭屍王的殭屍血，各取一樣來！\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),CYN"丁一説道：完成後再來找我(report)。\n"NOR);
                        set_temp("任務", 4, speaker);
                        break;
                default: 
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                delete("quest/to_kill", mazeobj);
                                delete("quest/to_find", mazeobj);
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 4, mazeobj);
                                set("quest/quest_name", "尋找法引", mazeobj);
                                set("quest/quest_desc", "找到巫妖的骨杖，幽冥魔的幽冥之火，殭屍王的殭屍血各一樣", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                set("quest/to_find/骨杖", 1, mazeobj);
                                set("quest/to_find/幽冥之火", 1, mazeobj);
                                set("quest/to_find/殭屍血", 1, mazeobj);
                        }
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
        }
        call_out("play_sound_4",1,speaker,++index);
}

void play_sound_5(object speaker,object leader,int index) {
        object mazeobj;
        if(!environment())
                return;
        if(!speaker)
                return;
        if(!leader) {
                delete_temp("in_speech", speaker);
                destruct(this_object());
                return;
        }
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一説道：這樣所有需要的法器就全了！\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一説道：我們到聚靈法陣那裏，我來作法，重新召喚...哦不，重新封印血魔！\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一説道：法陣那裏可能還有些血魔的手下......你從前面帶路吧！\n"NOR);
                        set_temp("任務", 5, speaker);
                        break;
                default: 
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                delete("quest/to_find", mazeobj);
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 5, mazeobj);
                                set("quest/quest_name", "清理法陣", mazeobj);
                                set("quest/quest_desc", "把丁一帶到聚靈法陣，並清理那裏的血魔手下", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                speaker->set_leader(leader);
                        }
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
        }
        call_out("play_sound_5",1,speaker,leader,++index);
}

void play_sound_6(object speaker,int index) {
        object mazeobj;
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"丁一説道：好，我可以開始作法了！\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"丁一説道：聚靈塔需要吸收十個亡靈才能發揮作用。！\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"丁一説道：在我施法期間，會有很多亡靈被吸引來，幫我殺夠十個！\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),HIW"丁一將骨杖、幽冥之火和殭屍血投入到聚靈法陣中...法陣頓時亮了起來！\n"NOR);
                        break;
                case(4):
                        tell_room(environment(),HIY"丁一拿出聚靈塔，大聲的念着咒語......\n"NOR);
                        set_temp("任務", 6, speaker);
                        break;
                default: 
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 6, mazeobj);
                                set("quest/quest_name", "超度亡靈", mazeobj);
                                set("quest/quest_desc", "護衞丁一，同時在聚靈法陣處殺死十個亡靈", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                set("quest/to_kill/亡靈", 10, mazeobj);
                                speaker->summon_undead(environment(),mazeobj);
                                //speaker->start_call_out( (:call_other,speaker, "summon_undead",environment(),mazeobj :),5);
                                //mazeobj->delete("quest/killed/亡靈",20);
                        }
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
        }
        call_out("play_sound_6",1,speaker,++index);
}

void play_sound_7(object speaker,int index) {
        object mazeobj,*objs,obj,moon;
        if(!environment())
                return;
        if(!speaker)
                return;
        switch (index)  {
                case(0):
                        tell_room(environment(),HIC"\n丁一説道：成敗在此一舉！\n\n"NOR);
                        tell_room(environment(),BLINK HIC"\n聚靈塔升上天空，聚靈法陣發出耀眼的五彩光芒。\n\n"NOR);
                        objs = all_inventory(environment());
                        foreach(obj in objs) {
                                if(obj && obj->is_undead())
                                        obj->die();
                        }
                        break;
                case(1):
                        tell_room(environment(),HIR"一道血色的人影從聚靈法陣中漂出，投入到聚靈塔中！\n\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),HIR"丁一收回了聚靈塔，只見血色人影和丁一合而為一！\n\n"NOR);
                        break;
                case(3):
                        tell_room(environment(),HIR"丁一滿目赤紅，瘋狂的大笑道：哈哈哈！我成功了！我成功了！\n\n"NOR);
                        break;
                case(4):
                        tell_room(environment(),HIR"丁一狂笑道：我丁一，現在就是血魔！血魔就是我！\n\n"NOR);
                        break;
                case(5):
                        tell_room(environment(),BLINK HIR"\n丁一將聚靈塔擲向天空，只見天際竟然升起一輪血紅色的月亮！\n\n");
                        moon = new("/maze/necropolis/obj/bloodmoon");
                        set("owner", speaker, moon);
                        moon->move(environment());
                        set("short", "聚靈法陣", environment());
                        objs = all_inventory(environment());
                        foreach(obj in objs) 
                                        if(obj && userp(obj))
                                                        obj->ccommand("look");
                        set("short", HIY"聚靈法陣"NOR, environment());
                        moon->hurt();
                        break;
                case(6):
                        tell_room(environment(),HIR"\n\n丁一説道：朋友們，現在是我報答你們的時候了！就是把你們變成血魔的一部分！哈哈！\n\n"NOR);
                        set_temp("任務", 7, speaker);
                        mazeobj = FUBEN_D->query_maze_mainobj(speaker);
                        if(mazeobj) {
                                set("quest/maze_code", "necropolis", mazeobj);
                                set("quest/quest_index", 7, mazeobj);
                                set("quest/quest_name", "終結血魔", mazeobj);
                                set("quest/quest_desc", "殺死成為血魔的丁一", mazeobj);
                                set("quest/quest_branch", "taoist", mazeobj);
                                set("quest/to_kill/丁一", 1, mazeobj);
                        }
                        set("attitude", "aggressive", speaker);
                        set("bellicosity", 50000, speaker);
/*
                        set("qi",query("max_qi",  speaker)/2, speaker);
                        set("eff_qi",query("max_qi",  speaker)/2, speaker);
                        set("jing",query("max_jing",  speaker)/2, speaker);
                        set("eff_jing",query("max_jing",  speaker)/2, speaker);
                        set("sen",query("max_sen",  speaker), speaker);
                        set("eff_sen",query("max_sen",  speaker), speaker);
*/
                        objs = all_inventory(environment());
                        foreach(obj in objs) 
                                        if(obj && obj->is_character() && !obj->is_corpse() && obj!=speaker && !obj->is_undead()) {
                                                        speaker->kill_ob(obj);
                                                        obj->kill_ob(speaker);
                                        }
                        
                        delete_temp("in_speech", speaker);
                        destruct(this_object());
                        return;
                        break;

        }
        call_out("play_sound_7",1,speaker,++index);
}

void play_sound_8(string dir,int index) {
        if(!environment())
                return;

        switch (index)  {
                case(0):
                        tell_room(environment(),HIM"\n丁一喊到：這不可能！血魔！我是血魔！\n\n"NOR);
                        tell_room(environment(),HIM"\n丁一慢慢變成了一灘污血！\n\n"NOR, this_object());
                        call_out("play_sound_8",1,dir,++index);
                        break;
                /*
                case(1):
                        tell_room(environment(),HIY"副本將在一分鐘後消失！\n"NOR);
                        call_out("play_sound_8",60,dir,++index);
                        break;
                case(2):
                        FUBEN_D->remove_virtual_maze(killer, "necropolis") 
                        destruct(this_object());
                        return;
                        break;
                */
        }
}