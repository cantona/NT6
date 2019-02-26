// /d/shenlong/ship.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

string long_desc();
void do_ready();
void do_drop();
void reset();

void create()
{
        set("short", "海船");
        set("long", (: long_desc :));
        set("invalid_startroom", 1);

        set("exits", ([
                "down" : __DIR__"cabin",
        ]));
        set("cost", 5);
        set("outdoors", "shenlong");

        setup();
}

string long_desc()
{
        string desc;

        desc = "這是一艘很普通的漁船，幾名漁夫擺弄着帆篷，篙槳，繩索，和船尾木舵。\n";
        desc += "以下指令有助於你的航行：(1)start, (2)stop, (3)go, (4)lookout, (5)locate。\n\n";

        if( !query("exits/out") )
                switch((int)query_temp("navigate/weather"))
                {
                        case 1: desc += BLU"天空中彤雲密佈，只有幾隻海鷗還在奮力展翅，海船左右搖晃不已，你感到有\n點立足不穩。\n"NOR; break;
                        case 2: desc += BLU"海面洶湧澎湃，幾丈高的巨浪排山倒海似得壓來，隨時都有可能將船掀翻，你\n時而不得不緊緊抱住船杆，以免落海。\n"NOR; break;
                        default: desc += BLU"四周是遼闊的海面，海風在你耳邊輕輕吹過，海浪一個接一個向船潑打過來。\n"NOR;  break;
                }
        return desc;
}

void init()
{
        add_action("do_start", "start");
        add_action("do_go", "go");
        add_action("do_stop", "stop");
        add_action("do_lookout", "lookout");
        add_action("do_locate", "locate");
        add_action("do_fast", "wind");
}

int do_fast(string arg)
{
        object me = this_player();
        
        if( !wizardp(me) )
                return notify_fail("你鼓起腮幫子，拼命向船帆上吹氣！\n");
        
        if( !arg ) return notify_fail("指令錯誤！\n");

        message_vision(HIW"$N仰天長嘯：ＷＩＮＤ　ＥＬＥＭＥＮＴ！！！\n"NOR,me);
        tell_room(this_object(), HIG
        "只見天空中烏雲密佈，一個巨神的身影在天際出現，化做一股龍捲風！\n"+
        "龍捲風帶起數百丈高的海浪向船襲來，你嚇得動也不敢動！！！\n"NOR);

        switch(arg) {
                case "east":
                        addn_temp("navigate/locx", 100);
                        break;
                case "south":
                        addn_temp("navigate/locy", -100);
                        break;
                case "west":
                        addn_temp("navigate/locx", -100);
                        break;
                case "north":
                        addn_temp("navigate/locy", 100);
                        break;
                default:
                        return 1;
        }        
        return 1;
}

int do_start()
{
        mixed inv;
        object shipside, me = this_player();

        inv = filter_array(all_inventory(this_object()), "is_owner", this_object(), me);
        if( sizeof(inv) > 0 )
                return notify_fail("長這麼大連一點江湖規矩都不懂？\n");

        if( !query("exits/out") )
                return notify_fail("船已經出海了。\n");

        if( !(shipside = find_object(query("exits/out"))) )
                shipside = load_object(query("exits/out"));

        switch(query("short", shipside)){
                case "塘沽口":
                        set_temp("navigate/locx", 0);
                        set_temp("navigate/locy", 0);
                        break;
                case "海岸":
                        set_temp("navigate/locx", 20);
                        set_temp("navigate/locy", 20);
                        break;

                case "冰火島":
                        set_temp("navigate/locx", 90);
                        set_temp("navigate/locy", 590);
                        break;

        }

        message("vision", "漁船離了岸，駛向茫茫的大海。\n", shipside);
        delete("exits/enter", shipside);

        message_vision("$N大喝一聲“開船”，於是船便離了岸。\n", me);
        delete("exits/out");

        call_out("shipweather", 1);
        call_out("navigate", 1);
        set_temp("navigate/control", 1);

        return 1;
}

int navigate()
{
        object dest, *inv, *invofusr;
        string dir;
        int i, m, locx, locy;

        if( !random(100) && !query("exist/out")
        &&  query_temp("navigate/weather") == 2 ) {
                tell_room(this_object(), HIR"\n突然間狂風大作，不一會兒船就翻了！\n\n"NOR);
                do_drop();
                return 1;
        }

        if( !random(40) && !query("exist/out") ) {
                switch(random(10)) {
                case 0 : /* monster 海怪*/
                        break;
                case 1 : /* treasure 財寶*/
                        break;
                case 2 : /* corsair 海盜*/
                        break;
                case 3 :
                        tell_room(this_object(), HIC
                        "你看見桅杆上閃着青白色的光，哇！神蹟！！！\n"NOR);
                        break;
                case 4 :
                        tell_room(this_object(), HIW
                        "大霧迷漫，一艘破舊的大船開了過來，一會兒又消失了，船上傳來隱隱的歎息聲，\n"+
                        "你依稀記得船上有幾個怪字＂Titanic＂！！！\n"NOR);
                        break;
                case 5 :
                        tell_room(this_object(), HIR
                        "你看見一隻燃燒着的大鳥向船衝過來，糟糕，要撞上了！！！\n"NOR);
                        break;
                case 6 :
                        tell_room(this_object(), HIM
                        "海面上傳來一陣美妙的歌聲，你頓時有一種按捺不住跳下海的衝動！！！\n"NOR);
                        break;
                case 7 :
                        tell_room(this_object(), HIG
                        "你突然發現海中有一隻青色大眼睛正瞪着你，過一會兒就不見了，你嚇得魂不附體！！！\n"NOR);
                        break;
                case 8 :
                        tell_room(this_object(), HIY
                        "你看見遠處一個人身魚尾的美麗少女躍出海面，哇噻！美人魚咧！！！\n"NOR);
                        break;
                case 9 :
                        tell_room(this_object(), HIG
                        "你眼前一亮，北方映出一片奇異莫可名狀的光彩，"+HIM"無數奇麗絕倫的光色，在黑暗中\n"+
                        "忽伸忽縮，"+YEL"大片橙黃之中"+MAG"夾着絲絲淡紫，忽而紫色愈深愈長，紫色之中，迸射出一\n"+
                        "條條"+HIY"金光、"+HIB"藍光、"+HIG"綠光、"+HIR"紅光。\n"NOR);
                        break;
                }
        }

        if( !(dir = (string)query_temp("navigate/dir")) ) {
                if( !random(100) ) {
                        addn_temp("navigate/wait", 1);
                        if( query_temp("navigate/wait") > 5 ) {
                                tell_room(this_object(), "船伕們把大家都扔進了海里。\n");
                                do_drop();
                                return 1;
                        }
                        tell_room(this_object(), "船伕們不耐煩地説：你到底走不走啊？\n");
                }                        
                call_out("navigate", 1);
                return 1;
        }       

        switch(dir) {
                case "東":
                        addn_temp("navigate/locx", 1);
                        break;
                case "南":
                        addn_temp("navigate/locy", -1);
                        break;
                case "西":
                        addn_temp("navigate/locx", -1);
                        break;
                case "北":
                        addn_temp("navigate/locy", 1);
                        break;
                default:
                        call_out("navigate", 1);
                        return 1;
        }

        locx = query_temp("navigate/locx");
        if( locx < 0 ) {
                tell_room(this_object(), "船伕説：“大陸到啦，上岸吧”。\n");
                set("exits/out", "/d/beijing/haigang");

                delete_temp("navigate");
                call_out("do_ready", 20 + random(10));

                dest = find_object("/d/beijing/haigang");
                set("exits/enter", "/d/shenlong/ship", dest);
                message("vision", "一條漁船駛了過來。\n", dest);
                return 1;
        }

        locy = query_temp("navigate/locy");
        if( locx == 20 &&  locy == 20 ) {
                tell_room(this_object(), "船伕説：“神龍島到啦，上岸吧”。\n");
                set("exits/out", "/d/shenlong/beach");

                delete_temp("navigate");
                call_out("do_ready", 20 + random(10));

                dest = find_object("/d/shenlong/beach");
                set("exits/enter", "/d/shenlong/ship", dest);
                message("vision", "一條漁船駛了過來。\n", dest);
                return 1;
        }

        if( locx <= 110 &&  locy <= 610 
        && locx >= 95 && locy >= 590 ) {
                tell_room(this_object(),"船伕説：“到了一個怪島，要上去看看嗎？”。\n");
                set("exits/out", "/d/changbai/icefire1");

                delete_temp("navigate");
                call_out("do_ready", 30 + random(20));

                dest = find_object("/d/changbai/icefire1");
                set("exits/enter", "/d/shenlong/ship", dest);
                message("vision", "一條漁船駛了過來。\n", dest);
                return 1;
        }

        if( !random(3) )
                tell_room(this_object(), "船正往" + dir + "方向前進。\n");
        call_out("navigate", 1);

        return 1;
}

int do_go(string arg)
{
        string dir;
        object me = this_player();
        mixed inv;

        if( query("exits/out") )
                return notify_fail("船還沒開呢。\n");

        if( !query_temp("navigate/control") ) {
                call_out("shipweather", 1);
                call_out("navigate", 1);
                set_temp("navigate/control", 1);
        }

        inv = filter_array(all_inventory(this_object()), "is_owner", this_object(), me);
        if( sizeof(inv) > 0 )
                return notify_fail("長這麼大連一點江湖規矩都不懂？\n");

        switch(arg) {
                case "e":
                case "east": 
                        dir = "東";
                        break;
                case "s": 
                case "south": 
                        dir = "南";
                        break;
                case "w": 
                case "west": 
                        dir = "西";
                        break;
                case "n": 
                case "north": 
                        dir = "北";
                        break;
                default:
                        return notify_fail("你要船往哪個方向開？\n");
        }

        set_temp("navigate/dir", dir);
        message_vision("$N對船伕説：船老大，請朝" + dir + "開。\n", me);
        return 1;
}

int do_stop()
{
        object me = this_player();
        mixed inv;

        inv = filter_array(all_inventory(this_object()), "is_owner", this_object(), me);
        if( sizeof(inv) > 0 )
                return notify_fail("長這麼大連一點江湖規矩都不懂？\n");

        if( !query_temp("navigate/dir") )
                return notify_fail("船已經停了。\n");

        message_vision("$N叫船伕們把船停一停。\n", me);
        delete_temp("navigate/dir");

        return 1;
}

int do_lookout()
{
        string dir;
        int locx, locy;

        if( query("exits/out") ) {
                tell_object(this_player(), "船還沒開呢。\n");
                return 1;
        }

        locx = (int)query_temp("navigate/locx");

        if( locx < 0 ) {
                tell_object(this_player(), "你已經在大陸岸邊了。\n");
                return 1;
        }

        if( locx < 6 ) {
                tell_object(this_player(), "你極目遠眺，發現西面不遠處就是大陸。\n");
                return 1;
        }

        locy = (int)query_temp("navigate/locy");

        if( locx == 20 &&  locy == 20 ) {
                tell_object(this_player(), "你已經在神龍島岸邊了。\n");
                return 1;
        }

        if( (locy > 16 && locy < 20) && (locx > 16 && locx < 20) )
                dir = "東北";
        else if( (locy > 16 && locy < 20) && locx == 20 )
                dir = "北";
        else if( (locy > 16 && locy < 20) && (locx > 20 && locx < 24) )
                dir = "西北";
        else if( locy == 20 && (locx > 16 && locx < 20) )
                dir = "東";
        else if( locy == 20 && (locx > 20 && locx < 24) )
                dir = "西";
        else if( (locy > 20 && locy < 24) && (locx > 16 && locx < 20) )
                dir = "東南";
        else if( (locy > 20 && locy < 24) && locx == 20 )
                dir = "南";
        else if( (locy > 20 && locy < 24) && (locx > 20 && locx < 24) )
                dir = "西南";

        if( dir )
                tell_object(this_player(), "你極目遠眺，發現神龍島就在" + dir + "方向。\n");
        else if( (locy > 350 && locy < 400) && (locx > 90 && locx < 110) )
                tell_object(this_player(),"你極目遠眺，發現北邊似乎有一條煙柱！\n");
        else tell_object(this_player(), "你極目遠眺，只覺大海茫茫。\n");

        return 1;
}

int do_locate()
{
        string dir;
        int locx, locy;

        if( query("exits/out") ) {
                tell_object(this_player(), "船還沒開呢。\n");
                return 1;
        }

        locx = (int)query_temp("navigate/locx");

        if( locx < 0 ) {
                tell_object(this_player(), "你已經在大陸岸邊了。\n");
                return 1;
        }

        locy = (int)query_temp("navigate/locy");

        if( locx == 20 &&  locy == 20 ) {
                tell_object(this_player(), "你已經在神龍島岸邊了。\n");
                return 1;
        }
        
        if (!wizardp(this_player())) {
        locx = (locx * 9 + random(locx))/10;
        locy = (locy * 9 + random(locy))/10;
        }

        if( locy > 0 ) 
                dir = "東" + chinese_number(locx) + "海哩" + "北約" + chinese_number(locy) + "海哩";
        else if( locy < 0 )
                dir = "東約" + chinese_number(locx) + "海哩" + "南約" + chinese_number(-locy) + "海哩";
        else    dir = "正東約" + chinese_number(locx) + "海哩";

        tell_object(this_player(), "你現在在塘沽口" + dir + "處。\n");

        return 1;
}

private is_owner(object ob, object me)
{
        if( living(ob) && userp(ob) && ob != me
         && query("combat_exp", ob)>query("combat_exp", me) )
                return 1;

        return 0;
}

void shipweather()
{
        if( !filter_array(all_inventory(this_object()), (:userp:)) )
                return;

        if( query("exits/out") ) return;
//        if( !mapp(query_temp("navigate")) ) return;

        if( !query_temp("navigate/weather") ) {
                if( !random(6) ) {
                        set_temp("navigate/weather", 1);
                        remove_call_out("niceweather");
                        call_out("niceweather", 5 + random(10));
                } else  if( !random(24) ) {
                        set_temp("navigate/weather", 2);
                        remove_call_out("niceweather");
                        call_out("niceweather", 5 + random(10));
                }
        }

        if( !query_temp("navigate/weather") )
                call_out("shipweather", 1);
}

void niceweather()
{
        set_temp("navigate/weather", 0);
        call_out("shipweather", 1);
}

void do_drop()
{
        object *inv, *invofusr;
        int i, m, factor;
        
        if( query_temp("navigate/locy") > 600 )
                factor = (query_temp("navigate/locy") - 600)/10;
        else factor = (600 - query_temp("navigate/locy"))/10;

        inv = all_inventory(this_object());
        for( i = 0; i < sizeof(inv); i++ ) {
                if( userp(inv[i]) ) {
                        inv[i]->unconcious();
                        invofusr = all_inventory(inv[i]);
                        for(m = 0; m < sizeof(invofusr); m++)
                                destruct(invofusr[m]);
                        if( random(8) == 1 )
                                inv[i]->move("/d/shenlong/beach");
                        else    if( !random(factor) )
                                inv[i]->move("/d/changbai/icefire1");
                        else        inv[i]->move("/d/beijing/haigang");
                        message("vision",
                        "你發現一個渾身水淋淋的傢伙被海水衝上岸來，不由得走近一看，原來是"+query("name", inv[i])+"。\n",environment(inv[i]),({inv[i]}));
                } else  destruct(inv[i]);
        }

        delete_temp("navigate");
        delete_temp("trigger");
}

void do_ready()
{
        object shipside;

        if( !query_temp("trigger") || !query("exits/out") )
                return;

        if( !(shipside = find_object(query("exits/out"))) )
                shipside = load_object(query("exits/out"));

        switch(query("short", shipside)){
                case "塘沽口":
                        set_temp("navigate/locx", 0);
                        set_temp("navigate/locy", 0);
                        break;
                case "海岸":
                        set_temp("navigate/locx", 20);
                        set_temp("navigate/locy", 20);
                        break;
                case "冰火島":
                        set_temp("navigate/locx", 90);
                        set_temp("navigate/locy", 590);
                        break;
        }

        message("vision", "漁船離了岸，駛向茫茫的大海。\n", shipside);
        delete("exits/enter", shipside);

        delete_temp("trigger");
        delete("exits/out");
        message("vision", "船伕們大喝一聲“開船”，於是船便離了岸。\n", this_object());
}

void reset()
{
        object shipside;

        ::reset();

        if( !(shipside = find_object("/d/beijing/haigang")) )
                shipside = load_object("/d/beijing/haigang");

        if( query("exits/enter", shipside) )
                delete("exits/enter", shipside);

        if( !(shipside = find_object("/d/shenlong/beach")) )
                shipside = load_object("/d/shenlong/beach");

        if( query("exits/enter", shipside) )
                delete("exits/enter", shipside);
}


